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
	
	//Le doy tiempo de bloquear el semaforo
	Sleep(2000);
	
	//Si nos concede esto es porque el hijo ya termino
	WaitForSingleObject(sem,INFINITE);

	printf("(pa) Bloqueo, semaforo ahora en 0 \n");
	printf("Esto es lo que me envia mi hijo: %c\n",*apT);
	
	if(!ReleaseSemaphore(sem,1,NULL)){
		printf("(hi.c) ERROR: No se ha podido liberar el semaforo\n");
	}

	printf("(pa) Semaforo liberado\n");
	
	UnmapViewOfFile(apD);
	CloseHandle(pi.hProcess);   
	CloseHandle(pi.hThread);
	CloseHandle(sem);
	CloseHandle(mem);
	exit(0);
}