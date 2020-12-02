#include <windows.h>/* Servidor de la memoria compartida */ 
#include <stdio.h> /* (ejecutar el servidor antes de ejecutar el cliente)*/ 
#include <stdlib.h>
#define TAM_MEM 512 /*Tamaño de la memoria compartida en bytes */ 
int main(void) {    
	HANDLE hArchMapeo = NULL;    
	char *idMemCompartida = "MemoriaCompatida";    
	char *apDatos, *apTrabajo, c;    
	if((hArchMapeo=CreateFileMapping(INVALID_HANDLE_VALUE,// usa memoria compartida
	                  NULL,// seguridad por default
	                  PAGE_READWRITE,// acceso lectura/escritura a la memoria  
	                  0,// tamaño maxixmo parte alta de un DWORD
	                  TAM_MEM,// tamaño maxixmo parte baja de un DWORD
	                  idMemCompartida)// identificador de la memoria compartida
	                  ) == NULL){
		printf("No se mapeo la memoria compartida: (%i)\n", GetLastError());
		exit(-1);
	}
	if((apDatos=(char *)MapViewOfFile(hArchMapeo,// Manejador del mapeo 
	                        FILE_MAP_ALL_ACCESS,// Permiso de lectura/escritura en la memoria 
	                        0,0,TAM_MEM)) == NULL){
		printf("No se creo la memoria compartida: (%i)\n", GetLastError());
		CloseHandle(hArchMapeo);
		exit(-1);
	}
	apTrabajo = apDatos;
	for (c = 0; c < TAM_MEM; c++)
		*apTrabajo++ = 69;
	*apTrabajo = '\0';
	while (*apDatos != '*')
		sleep(1);
	UnmapViewOfFile(apDatos);
	CloseHandle(hArchMapeo);
	exit(0);
}