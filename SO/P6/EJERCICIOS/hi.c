/*
	FECHA: 15/12/2020
	AUTORA: S Gamaliel
	DESCRIPCION: Este programa muestra el funcionamiento de los semaforos.
		Tenemos dos procesos, un padre y un hijo. El padre crea un segmento de memoria 
		compartida e inicializa el valor a 'p', posteriormente libera el semaforo para
		que el hijo cambie el valor a 'h', luego libera el semaforo para que nuevamente
		el padre escriba 'p' y asi sucesivamente. Finaliza el programa.
*/
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void main(){
	//Variables a utilizar
	HANDLE mem, sem;
	char *apD, *apT;
	
	printf("Aqui entro\n");

	//Abro el segmento de memoria
	if((mem = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,"Memo")) == NULL){
		printf("(hi.c) ERROR: No se ha podido mapear el segmento de memoria compartida %d\n",GetLastError());
		exit(-1);
	}
	
	//Se pudo crear, abrimos el segmento
	if((apD = (char *) MapViewOfFile(mem,FILE_MAP_ALL_ACCESS,0,0,sizeof(char))) == NULL){
		printf("(hi.c) ERROR: No se ha podido abrir el semgento de memoria compartida %d\n",GetLastError());
		CloseHandle(mem);
		exit(-1);
	}

	//Creamos un semaforo con todos los recursos disponibles, es decir, nuestro hijo puede escribir inmediatemente
	if((sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Sem")) == NULL){
		printf("(hi.c) ERROR: No se ha podido abrir el semaforo %d\n",GetLastError());
		CloseHandle(mem);
		exit(-1);
	}

	apT = apD; //Accedemos a los datos de la memoria compartida

	char i = 1; //Vamos a repetir el proceso 3 veces
	DWORD waitResult; //Aqui vamos a ver que nos regresa WaitForSingleObject

	while((i<3)&&(i>0)){

		//Bloqueamos el semaforo
		waitResult = WaitForSingleObject(sem,INFINITE);

		switch(waitResult){
			case WAIT_OBJECT_0: //Ha sido bloqueado con exito
				printf("(hi) Bloqueo, semaforo ahora en 0\n");
				printf("Esto es lo que me envia mi papa: %c\n",*apT);
				//Enviamos un mensaje al padre ahora
				*apT = '*';
				printf("Hijo enviando mensaje al padre\n");
				if(!ReleaseSemaphore(sem,1,NULL)){
					printf("(hi.c) ERROR: No se ha podido liberar el semaforo\n");
					i--;
				}
				printf("(hi) Semaforo liberado, semaforo ahora en 1\n");
				Sleep(2000);
			break;
			case WAIT_TIMEOUT: //El semaforo esta bloqueado por el padre
				printf("(hi) Semaforo en 0 por el padre, espero...\n");
				Sleep(1000);
				i--;
			break;
		}
	
		i++;
	}

	
	UnmapViewOfFile(apD);
	CloseHandle(sem);
	CloseHandle(mem);
	exit(0);

}