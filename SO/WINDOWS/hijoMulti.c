#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define TAM_MEM 25

void main(){
	HANDLE hArchA = NULL, hArchB = NULL, hArchD = NULL;
	char *idA = "MatrizA";
	char *idB = "MatrizB";
	char *idD = "MatrizD";
	char (*apDA)[5], (*apTA)[5], (*apDB)[5], (*apTB)[5], (*apDD)[5], (*apTD)[5], i = 0, j = 0, k = 0;

	//Obten la memoria compartida
	if((hArchA=OpenFileMapping(
			FILE_MAP_ALL_ACCESS,// acceso lectura/escritura de la memoria compartida
			FALSE,// no se hereda el nombre                  
			idA))// identificador de la memoria compartida
			 == NULL){
		 printf("No se abrio archivo de mapeo de la memoria compartida para la matriz A: (%i)\n", GetLastError());
		 exit(-1);
	}

	if((hArchB=OpenFileMapping(
			FILE_MAP_ALL_ACCESS,// acceso lectura/escritura de la memoria compartida
			FALSE,// no se hereda el nombre                  
			idB))// identificador de la memoria compartida
			 == NULL){
		 printf("No se abrio archivo de mapeo de la memoria compartida para la matriz B: (%i)\n", GetLastError());
		 exit(-1);
	}

	if((hArchD=OpenFileMapping(
			FILE_MAP_ALL_ACCESS,// acceso lectura/escritura de la memoria compartida
			FALSE,// no se hereda el nombre                  
			idD))// identificador de la memoria compartida
			 == NULL){
		 printf("No se abrio archivo de mapeo de la memoria compartida para la matriz B: (%i)\n", GetLastError());
		 exit(-1);
	}

	if((apDA=(char(*)[5])MapViewOfFile(hArchA, // Manejador del mapeo 
	                         FILE_MAP_ALL_ACCESS, // Permiso de lectura/escritura en la memoria
	                         0,0,TAM_MEM)) == NULL){
 		printf("No se accedio a la memoria compartida de la matriz A: (%i)\n", GetLastError());// 
 		CloseHandle(hArchA);
 		exit(-1);
 	}

 	if((apDB=(char(*)[5])MapViewOfFile(hArchB, // Manejador del mapeo 
	                         FILE_MAP_ALL_ACCESS, // Permiso de lectura/escritura en la memoria
	                         0,0,TAM_MEM)) == NULL){
 		printf("No se accedio a la memoria compartida de la matriz B: (%i)\n", GetLastError());// 
 		CloseHandle(hArchB);
 		exit(-1);
 	}

 	if((apDD=(char(*)[5])MapViewOfFile(hArchD, // Manejador del mapeo 
	                         FILE_MAP_ALL_ACCESS, // Permiso de lectura/escritura en la memoria
	                         0,0,TAM_MEM)) == NULL){
 		printf("No se accedio a la memoria compartida de la matriz B: (%i)\n", GetLastError());// 
 		CloseHandle(hArchB);
 		exit(-1);
 	}

 	apTA = apDA;
 	apTB = apDB;
 	apTD = apDD;

 	printf("Primeramente, esto es lo que obtengo de matriz D:\n");
 	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			printf("%i,",apTD[j][i]);
			apTD[j][i]=0;
			for(k=0;k<5;k++){
				apTD[j][i] += apTA[j][k]*apTB[k][i];
			}
		}
		printf("\n");
	}

 	UnmapViewOfFile(apDA);
 	UnmapViewOfFile(apDB);
 	UnmapViewOfFile(apDD);   
 	CloseHandle(hArchA);   
 	CloseHandle(hArchB);   
 	CloseHandle(hArchD);   
 	exit(0); 
}