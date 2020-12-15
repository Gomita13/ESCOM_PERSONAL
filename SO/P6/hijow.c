#include <windows.h>    /*Programa hijo*/ 
#include <stdio.h> 
int main() {     

	HANDLE shMem;
	char *apD, *apT;
	char *frase = "HolaComoHolaComoHolaEstas";

	//Parte de la memoria compartida
	if((shMem = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,"Memoria")) == NULL){
		printf("(hijow) No se abrio archivo de mapeo de la memoria compartida (ERROR %i)\n", GetLastError());
		exit(-1);
	}

	if((apD= (char *)MapViewOfFile(shMem,FILE_MAP_ALL_ACCESS,0,0,25)) == NULL){
 		printf("(hijow) No se accedio a la memoria compartida (ERROR %i)\n", GetLastError());// 
 		CloseHandle(shMem);
 		exit(-1);
 	}

 	apT = apD;

	HANDLE hSemaforo;     
	int i=1;     // Apertura del semáforo          
	if((hSemaforo = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Semaforo")) == NULL)               {
		printf("Falla al invocar OpenSemaphore: %d\n", GetLastError());         
		return -1;     
	}    

	char j = 0;
	while(i<4)    {   
		// Prueba del semáforo     
		WaitForSingleObject(hSemaforo, INFINITE);     //Sección crítica     
		printf("Soy el hijo, bloqueo el semaforo y hago esto:\n");
		//Modificamos el contenido de la memoria
		for(j=0;j<25;j++){
			*apT=frase[j];
			*apT++;
		}

		printf("%s\n",apT);


		if (!ReleaseSemaphore(hSemaforo, 1, NULL) )     {        
			printf("Falla al invocar ReleaseSemaphore: %d\n", GetLastError());     
		}     
		printf("Soy el hijo liberando al semaforo\n");     
		
		i++;    
	} 
	CloseHandle(shMem);
	UnmapViewOfFile(apD);
}