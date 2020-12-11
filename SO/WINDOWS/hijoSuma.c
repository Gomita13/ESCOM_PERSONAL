/*
	FECHA: 09-12-2020
	AUTORA: S GAMALIEL
	DESCRIPCION: Este programa realiza la suma de dos matrices
		que son dadas por un espacio de memoria compartida.
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
//Si modificas NO_MAT, agrega o elimina IDs en el arreglo keys[] 
#define NO_MAT 2
//Modifica el tamaño de la matriz
#define N 5 
//Modifica el tipo de dato si deseas
#define TAM_MEM  N*N*sizeof(char)

void main(){
	//Estructuras para la creacion de procesos hijos
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE hArch[NO_MAT+1] = {NULL,NULL,NULL}; //Arreglo de handlers para las matrices y semaforo
	char *ids[NO_MAT+1] = {"MatrizA","MatrizB","Semaforo"};
	//Direccion al programa que ejecutara el proceso hijo
	char path[] = "C:/Users//gamma//Documents//Programas//ESCOM_PERSONAL//SO//WINDOWS//hijoMulti.exe";
	unsigned char (*apDA)[N], (*apDB)[N]; //Apuntadores para datos
	unsigned char (*apTA)[N], (*apTB)[N]; //Apuntadores para manipulacion
	char *apTS, *apDS;
	char i = 0, j = 0; 

	//Obtenemos la memoria para las matrices
	for(i=0;i<NO_MAT;i++){
		//Obtenemos la memoria compartida
		if((hArch[i]=OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,ids[i])) == NULL){
			printf("No se abrio archivo de mapeo de la memoria compartida para la matriz %i: (ERROR %i)\n", i, GetLastError());
			exit(-1);
		}
	}

	//Obtenemos memoria para el semaforo
	if((hArch[NO_MAT] = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,ids[NO_MAT])) == NULL){
		printf("No se abrio el archivo de mapero de la memoria compartida para el semaforo: (ERROR %i)\n",GetLastError());
		exit(-1);
	}	

	//Abrimos la memoria compartida
	if((apDA=(unsigned char(*)[N])MapViewOfFile(hArch[0],FILE_MAP_ALL_ACCESS,0,0,TAM_MEM)) == NULL){
 		printf("No se accedio a la memoria compartida de la matriz A: (ERROR %i)\n", GetLastError());// 
 		CloseHandle(hArch[0]);
 		exit(-1);
	}

	if((apDB=(unsigned char(*)[N])MapViewOfFile(hArch[1],FILE_MAP_ALL_ACCESS,0,0,TAM_MEM)) == NULL){
 		printf("No se accedio a la memoria compartida de la matriz A: (ERROR %i)\n", GetLastError());// 
 		CloseHandle(hArch[1]);
 		exit(-1);
	}

	if((apDS = (char *) MapViewOfFile(hArch[NO_MAT],FILE_MAP_ALL_ACCESS,0,0,sizeof(char))) == NULL){
 		printf("No se accedio a la memoria compartida del semaforo: (ERROR %i) \n", GetLastError());// 
 		CloseHandle(hArch[NO_MAT]);
 		exit(-1);	
 	}


	//Apuntamos a los segmentos para manipulacion
	apTA = apDA;
	apTB = apDB;
	apTS = apDS;
	
	//Primero, vamos a ejecutar al nieto
	ZeroMemory(&si,sizeof(si));
	si.cb = sizeof(si);

	ZeroMemory(&pi,sizeof(pi));
	if(!CreateProcess(NULL,path,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
		printf("Fallo al crear el proceso hijoMulti\n");
		UnmapViewOfFile(apDA);
		UnmapViewOfFile(apDB);
		UnmapViewOfFile(apDS);
	 	CloseHandle(hArch[0]);
	 	CloseHandle(hArch[1]);
	 	CloseHandle(hArch[2]); 	
	 	exit(1);
	}

	//Si lo pudo crear, esperamos
	while(*apTS!='h'){
		sleep(1);
	}

	//Ahora ejecutamos la suma
	//A = A + B
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			apTA[i][j] = apTA[i][j] + apTB[i][j];
		}
	}

	//Terminamos, pasamos el semaforo al padre
	*apTS = 'p';
	
	UnmapViewOfFile(apDA);
	UnmapViewOfFile(apDB);
	UnmapViewOfFile(apDS);
 	CloseHandle(hArch[0]);
 	CloseHandle(hArch[1]);
 	CloseHandle(hArch[2]);

 	exit(0); 
}