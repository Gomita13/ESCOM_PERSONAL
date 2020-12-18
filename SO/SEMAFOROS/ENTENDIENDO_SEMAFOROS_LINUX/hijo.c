/*
	FECHA: 17/12/2020
	AUTORA: S GAMALIEL
	DESCRIPCION: Este programa tiene como finalidad entender
	el funcionamiento de los semaforos en linux. Se va a crear 
	un proceso padre y un hijo. El padre crea el semaforo y lo 
	libera, el hijo lo bloquea, ejecuta unas cuantas impresiones
	y libera el semaforo para que el padre pueda imprimir.
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

void main(int argc, char *argv[]){
	
	key_t keySem;
	int idChild = -1;
	int idSem = -1;
	struct sembuf bf = {0,-1,0};

	//Obtenemos llave para crear el semaforo
	if((keySem = ftok("padre.c",'J')) == -1){
		printf("(hijo.c) ERROR: NO se ha podido crear la llave\n");
		exit(-1);
	}

	//Creamos el semaforo 
	if((idSem = semget(keySem,1,0)) == -1){
		printf("(hijo.c) ERROR: NO se ha podido crear el semaforo\n");
		exit(-1);	
	}

	//Espero a que libere el semaforo
	if(semop(idSem,&bf,1) == -1){
		printf("(hijo.c) ERROR: No se ha podido bloquear el semaforo\n");
		exit(-1);
	}
	//Se bloqueo con exito
	printf("Ya estoy harta de la escuela\n");

	//Libero el semaforo
	bf.sem_op = 1;

	if(semop(idSem,&bf,1) == -1){
		printf("(hijo.c) ERROR: No se ha podido bloquear el semaforo\n");
		exit(-1);
	}

	exit(0);

}