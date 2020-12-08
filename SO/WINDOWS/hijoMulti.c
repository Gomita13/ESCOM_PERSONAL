/*
	FECHA: 09-12-2020
	AUTORA: S GAMALIEL
	DESCRIPCION: Este programa realiza la multiplicacion de dos matrices
		que son dadas por un espacio de memoria compartida.
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
//Si modificas NO_MAT, agrega o elimina IDs en el arreglo keys[] 
#define NO_MAT 3
//Modifica el tamaño de la matriz
#define N 5 
//Modifica el tipo de dato si deseas
#define TAM_MEM  N*N*sizeof(char)

void main(){
	HANDLE hArch[NO_MAT] = {NULL,NULL,NULL}; //Arreglo de handlers para las matrices
	char *ids[NO_MAT] = {"MatrizA","MatrizB","MatrizC"};
	unsigned char (*apDA)[N], (*apDB)[N], (*apDC)[N]; //Apuntadores para datos
	unsigned char (*apTA)[N], (*apTB)[N], (*apTC)[N]; //Apuntadores para manipulacion
	char i = 0, j = 0, k = 0; 

	//Obtenemos la memoria para las matrices
	for(i=0;i<NO_MAT;i++){
		//Obtenemos la memoria compartida
		if((hArch[i]=OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,ids[i])) == NULL){
			printf("No se abrio archivo de mapeo de la memoria compartida para la matriz %i: (ERROR %i)\n", i, GetLastError());
			exit(-1);
		}
	}

	if((apDA=(unsigned char(*)[N])MapViewOfFile(hArch[0],FILE_MAP_ALL_ACCESS,0,0,TAM_MEM)) == NULL){
 		printf("No se accedio a la memoria compartida de la matriz A: (%i)\n", GetLastError());// 
 		CloseHandle(hArch[0]);
 		exit(-1);
 	}

 	if((apDB=(unsigned char(*)[N])MapViewOfFile(hArch[1],FILE_MAP_ALL_ACCESS,0,0,TAM_MEM)) == NULL){
 		printf("No se accedio a la memoria compartida de la matriz B: (%i)\n", GetLastError());// 
 		CloseHandle(hArch[1]);
 		exit(-1);
 	}

 	if((apDC=(unsigned char(*)[N])MapViewOfFile(hArch[2],FILE_MAP_ALL_ACCESS,0,0,TAM_MEM)) == NULL){
 		printf("No se accedio a la memoria compartida de la matriz B: (%i)\n", GetLastError());// 
 		CloseHandle(hArch[2]);
 		exit(-1);
 	}

 	apTA = apDA;
 	apTB = apDB;
 	apTC = apDC;

 	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			apTC[j][i]=0;
			for(k=0;k<N;k++){
				apTC[j][i] += apTA[j][k]*apTB[k][i];
			}
		}
	}

 	UnmapViewOfFile(apDA);
 	UnmapViewOfFile(apDB);
 	UnmapViewOfFile(apDC);   
 	CloseHandle(hArch[0]);   
 	CloseHandle(hArch[1]);   
 	CloseHandle(hArch[2]);   
 	exit(0); 
}