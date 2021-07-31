/*
	FECHA: 15/12/2020
	AUTORA: S GAMALIEL
	DESCRIPCION: El proposito de este programa hijo es mostrar el funcionamiento de los semaforos
		con otra aplicacion, en este caso el programa hijo se ejecuta y bloquea el semaforo, realiza
		todas las tareas necesarias para las cuales fue diseñado y posteriormente libera el semaforo.
		Una vez liberado el semaforo por el hijo, el padre puede realizar las tareas para las que fue
		programado. Finaliza el programa.
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
	
	//Bloqueamos el semaforo
	WaitForSingleObject(sem,INFINITE);

	printf("(hi) Bloqueo, semaforo ahora en 0\n");
	printf("Esto es lo que me envia mi papa: %c\n",*apT);
	
	char i = 0; 

	for(i=0;i<27;i++){
		printf("Sorry!\n");
	}

	//Le mandamos un mensaje a mi papa
	*apT = '*';

	if(!ReleaseSemaphore(sem,1,NULL)){
		printf("(hi.c) ERROR: No se ha podido liberar el semaforo\n");
	}

	printf("(hi) Semaforo liberado, semaforo ahora en 1\n");
	
	
	UnmapViewOfFile(apD);
	CloseHandle(sem);
	CloseHandle(mem);
	exit(0);

}