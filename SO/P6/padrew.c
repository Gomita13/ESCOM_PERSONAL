#include <windows.h>    /*Programa padre*/ 
#include <stdio.h> 
int main(int argc, char *argv[]) {    
	STARTUPINFO si;            /* Estructura de información inicial para Windows */    
	PROCESS_INFORMATION pi;        /* Estructura de información del adm. de procesos */    
	HANDLE hSemaforo,shMem;
	char *apD, *apT;     
	char *frase = "Jijijijijijijijijijijijij";
	int i=1;     
	ZeroMemory(&si, sizeof(si));     
	si.cb = sizeof(si);     
	ZeroMemory(&pi, sizeof(pi));     
	if(argc!=2)     {         
		printf("Usar: %s   Nombre_programa_hijo\n", argv[0]);         
		return;     
	}    

	//Memoria compartida
	if ((shMem = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,25,"Memoria")) == NULL){
		printf("(padre) No se pudo crear el archivo de maapeo de la memoria: (ERROR %i)\n",GetLastError());
		exit(-1);
	}

	if((apD=(char *)MapViewOfFile(shMem,FILE_MAP_ALL_ACCESS,0,0,25)) == NULL){
 		printf("(padre) No se accedio a la memoria compartida (ERROR %i)\n", GetLastError());// 
 		CloseHandle(shMem);
 		exit(-1);
 	}

 	apT = apD;

	// Creación del semáforo          
	if((hSemaforo = CreateSemaphore(NULL, 1, 4, "Semaforo")) == NULL)               {
		printf("Falla al invocar CreateSemaphore: %d\n", GetLastError());         
		return -1;     
	}
	     // Creación proceso hijo      
	if(!CreateProcess(NULL, argv[1], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))     {         
		printf("Falla al invocar CreateProcess: %d\n", GetLastError() );         
		return -1;     
	}

	char j = 0;

	while(i<4)    {     // Prueba del semáforo     
		WaitForSingleObject(hSemaforo, INFINITE);     //Sección crítica     
		printf("Padre bloquea el semaforo, hago esto:\n");

		for(j=0;j<25;j++){
			*apT=frase[j];
			*apT++;
		}

		printf("%s\n",apT);

		if (!ReleaseSemaphore(hSemaforo, 1, NULL) )     {         
			printf("Falla al invocar ReleaseSemaphore: %d\n", GetLastError());     
		}    
		Sleep(2000); 
		printf("Libero el semaforo\n");
		i++;  
		apT = apD;  
	}   // Terminación controlada del proceso e hilo asociado de ejecución   
	CloseHandle(pi.hProcess);   
	CloseHandle(pi.hThread); 
	CloseHandle(shMem);
	UnmapViewOfFile(apD);
}