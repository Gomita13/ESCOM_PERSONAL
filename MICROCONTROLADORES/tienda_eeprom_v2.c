#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/eeprom.h>

int step;
int cta;
int aux;
int cta_aux;
int cta_eepr;

/*
	EL SIGUIENTE PROGRAMA LLEVA LA CUENTA REGRESIVA DE CLIENTES DE UNA TIENDA.
	CADA 6 CLIENTES EL SISTEMA HACE SONAR UNA ALARMA CONECTADA EL PUERTO A DEL MICROCONTROLADOR
	Y SE INCREMENTA UN CONTADOR DE GANADORES QUE SE REGISTRA EN LA EEPROM.
*/

void config_io(void){
   
    // ESTABLECEMOS EL PUERTO A,C y D COMO SALIDA
   DDRA = 0x01;
   DDRC = 0X0F;
   DDRD = 0XFF;
   
   // HABILITAMOS EL PULL-UP DEL PUERTO B EN SU BIT 0 y 2
   DDRB = 0b11111010;
   PORTB = _BV(PB0) | _BV(PB2);
   
	// HABILITAMOS LA INTERRUPCIÓN POR DESBORDAMIENTO DEL TC0, TC1 y TC2
   TIMSK = _BV(TOIE0) | _BV(TOIE1) | _BV(TOIE2);

	//HABILITAMOS LA DETECTION DEL FLANCO DE BAJADA EN EL INT2
	MCUCSR = _BV(ISC2);
	GICR = _BV(INT2);
   
   //HABILITAMOS GLOBALMENTE LAS INTERRUPCIONES
    sei();
   
   // CARGAREMOS LA PREESCALA 6 AL TCCR0
   TCCR0 = _BV(CS02) | _BV(CS01); 
   
   // INICIALIZAMOS AL TCNT0
	TCNT0 = 250;
	cta_aux = 251;
	cta = 6;

	//LEEMOS LO QUE HAY EN LA EEPROM
	cta_eepr = eeprom_read_byte(0x00);
	PORTD = cta_eepr;
}

void escribir_eeprom(int dato){
	while(!eeprom_is_ready()){
		_delay_ms(10);
	}
	eeprom_write_byte(0x00,dato);
}

ISR(TIMER0_OVF_vect){
	cta--;
	PORTC = cta ;
	cta_eepr = eeprom_read_byte(0x00);
	cta_eepr++;

	escribir_eeprom(cta_eepr);

	//Mostramos lo guardado en la EEPROM
	PORTD =  cta_eepr;

	//CARGAREMOS LA PREESCALA AL TCCR2
	TCCR2 = _BV(CS21) | _BV(CS22);

	//INICIALIZAMOS EL TCNT1
	TCNT1H = 0xB3;
	TCNT1L = 0xB5;

	// CARGAMOS LA PREESCALA AL TCCR1
	TCCR1B = _BV(CS12);
}

ISR(TIMER1_OVF_vect){
	//REESTABLECEMOS EL TCNT1
	TCNT1H = 0xB3;
	TCNT1L = 0xB5;
	TCCR2 = 0x00;
	TCCR1B = 0x00;

	// REESTABLECEMOS AL TCNT0
	TCNT0 = 250;

	//REESTABLECEMOS CUENTAS
	cta_aux = 251;
	cta = 6;
}

ISR(TIMER2_OVF_vect){
	TCNT2 = 113; //256-143
	aux = PINA^0x01;
	PORTA = aux;//0x01;
	
}

ISR(INT2_vect){
	//RESETEAMOS LA EEPROM, SU VALOR
	cta_eepr = 0;
	escribir_eeprom(cta_eepr);
	//Mostramos lo guardado en la EEPROM
	PORTD = cta_eepr;
}

int main(void){ 
	config_io();
	cta_eepr = 0;
   
	while (1){
		aux = TCNT0;
		if(aux == cta_aux){
			cta--; 
			cta_aux++;
		}
		PORTC = cta;
		PORTD = eeprom_read_byte(0x00);

		_delay_ms(200);
     }
 }
