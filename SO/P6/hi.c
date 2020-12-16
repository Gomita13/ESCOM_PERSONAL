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

	char espera = 1;
	DWORD waitResult; 
	LPLONG count;
	while(espera){
		waitResult = WaitForSingleObject(sem,0L);
		printf("Hijo...\n");
		switch(waitResult){
			case WAIT_OBJECT_0:
				//Bloqueado con exito
				printf("Mi papa me envia esto: %c\n",*apT);
				//Modifico el valor 
				*apT = 'h';
				ReleaseSemaphore(sem, 0, count)         ;
					
				printf("%i\n",count);   
				printf("Hijo: He liberado el semaforo\n");
				//Salgo del while
				espera = 0;
			break;
			case WAIT_TIMEOUT:
				printf("(hi.c) No he bloquear el semaforo, esperando 100ms\n");
				Sleep(100);
			break;
		}
	}
	
	UnmapViewOfFile(apD);
	CloseHandle(sem);
	CloseHandle(mem);
	exit(0);

}