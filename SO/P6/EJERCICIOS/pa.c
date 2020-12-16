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
void main(int argc, char *argv[]){
	//Variables a utilizar
	HANDLE mem, sem;
	char *apD, *apT;
	STARTUPINFO si;            /* Estructura de información inicial para Windows */    
	PROCESS_INFORMATION pi;        /* Estructura de información del adm. de procesos */    
	
	//Creo el segmento de memoria 
	if((mem = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(char),"Memo")) == NULL){
		printf("(pa.c) ERROR: No se ha podido crear el segmento de memoria compartida %d\n",GetLastError());
		exit(-1);
	}
	
	//Se pudo crear, abrimos el segmento
	if((apD = (char *) MapViewOfFile(mem,FILE_MAP_ALL_ACCESS,0,0,sizeof(char))) == NULL){
		printf("(pa.c) ERROR: No se ha podido abrir el semgento de memoria compartida %d\n",GetLastError());
		CloseHandle(mem);
		exit(-1);
	}

	//Inicializamos el valor a p
	apT = apD;
	*apT = 'p';

	//Creamos un semaforo con todos los recursos disponibles, es decir, nuestro hijo puede escribir inmediatemente
	if((sem = CreateSemaphore(NULL,1,1,"Sem")) == NULL){
		printf("(pa.c) ERROR: No se ha podido crear el semaforo %d\n",GetLastError());
		CloseHandle(mem);
		exit(-1);
	}

	//Creamos el proceso hijo
	ZeroMemory(&si,sizeof(si));
	si.cb = sizeof(si);

	ZeroMemory(&pi,sizeof(pi));

	//Creamos el hijo con el nombre especificado por la consolas
	if(!CreateProcess(NULL, argv[1], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))     {         
		printf("(pa.c) ERROR: Falla al crear el proceso: %d\n", GetLastError() );         
		CloseHandle(sem);
		CloseHandle(mem);
		UnmapViewOfFile(apD);
		exit(-1);
	}

	
	/*A partir de aqui ya soy padre. Me toca esperar a mi hijo.
	Espero a que bloquee el semaforo. Como solo hay 1 recurso y lo marque como disponible,
	mi hijo obtendra un 0 al llamar a WaitForSingleObject. Si yo la llamo debe regresarme
	otro valor distinto
	*/
	
	Sleep(2000);

	char i = 1; //Vamos a repetir el proceso 3 veces
	DWORD waitResult; //Aqui vamos a ver que nos regresa WaitForSingleObject
	
	while((i<4)&&(i>0)){

		//Bloqueamos el semaforo
		waitResult = WaitForSingleObject(sem,INFINITE);

		switch(waitResult){
			case WAIT_OBJECT_0: //Ha sido bloqueado con exito
				printf("(pa) Bloqueo, semaforo ahora en 0 \n");
				printf("Esto es lo que me envia mi hijo: %c\n",*apT);
				//Enviamos un mensaje al padre ahora
				*apT = 'p';
				printf("Padre enviando mensaje al hijo\n");
				if(!ReleaseSemaphore(sem,1,NULL)){
					printf("(hi.c) ERROR: No se ha podido liberar el semaforo\n");
					i--;
				}
				printf("(pa) Semaforo liberado, semaforo ahora en 1\n");
				Sleep(2000);
			break;
			case WAIT_TIMEOUT: //El semaforo esta bloqueado por el padre
				printf("(pa) Semaforo en 0 por el hijo, espero...\n");
				Sleep(1000);
				i--;
			break;
		}
	
		i++;
	}
	UnmapViewOfFile(apD);
	CloseHandle(pi.hProcess);   
	CloseHandle(pi.hThread);
	CloseHandle(sem);
	CloseHandle(mem);
	exit(0);
}