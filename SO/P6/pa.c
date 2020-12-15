/*
	FECHA: 15/12/2020
	AUTORA: S Gamaliel
	DESCRIPCION: Este programa muestra el funcionamiento de los semaforos.
		Tenemos dos procesos, un padre y un hijo. El padre crea un segmento de memoria 
		compartida e inicializa el valor a 'p', posteriormente libera el semaforo para
		que el hijo cambie el valor a 'h', luego libera el semaforo para que nuevamente
		el padre escriba 'p'. Finaliza el programa.
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
	Sleep(2000); //Le doy dos segundos para bloquear el semaforo
	char espera = 1;
	while(espera){
		switch(WaitForSingleObject(sem,0L)){
			case WAIT_OBJECT_0:
				//Esto quiere decir que mi hijo ya ha liberado el semaforo
				printf("Mi hijo esta enviando esto: %c\n",*apT);
				//Me toca modificarlo
				*apT = 'p';
				//Ahora libero el semaforo
				if (!ReleaseSemaphore(sem, 1, NULL)){         
					printf("Falla al invocar ReleaseSemaphore: %d\n", GetLastError());     
				}    
				//Salgo del while
				espera = 0;
			break;
			case WAIT_TIMEOUT:
				//Mi hijo sigue bloqueando el semaforo, lo espero
				Sleep(1000);
			break;
		}
	}

	Sleep(2000); //Nuevamente le doy dos segundos para bloquear el semaforo
	espera = 1;
	while(espera){
		switch(WaitForSingleObject(sem,0L)){
			case WAIT_OBJECT_0:
				//Esto quiere decir que mi hijo ya ha liberado el semaforo
				printf("Mi hijo esta enviando esto: %c\n",*apT);
				//Me toca modificarlo
				*apT = 'p';
				//Ahora libero el semaforo
				if (!ReleaseSemaphore(sem, 1, NULL)){         
					printf("Falla al invocar ReleaseSemaphore: %d\n", GetLastError());     
				}    
				//Termino mi ejecucion
				espera = 0;
			break;
			case WAIT_TIMEOUT:
				//Mi hijo sigue bloqueando el semaforo, lo espero
				Sleep(1000);
			break;
		}
	}

	UnmapViewOfFile(apD);
	CloseHandle(pi.hProcess);   
	CloseHandle(pi.hThread);
	CloseHandle(sem);
	CloseHandle(mem);
	exit(0);
}