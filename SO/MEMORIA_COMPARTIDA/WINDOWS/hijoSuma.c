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
	HANDLE hArch[NO_MAT] = {NULL,NULL}; //Arreglo de handlers para las matrices y semaforo
	char *ids[NO_MAT] = {"MatrizA","MatrizB"};
	//Direccion al programa que ejecutara el proceso hijo
	char path[] = "C:/Users//gamma//Documents//Programas//ESCOM_PERSONAL//SO//MEMORIA_COMPARTIDA//WINDOWS//hijoMulti.exe";
	unsigned char (*apDA)[N], (*apDB)[N]; //Apuntadores para datos
	unsigned char (*apTA)[N], (*apTB)[N]; //Apuntadores para manipulacion
	char i = 0, j = 0; 

	//Obtenemos la memoria para las matrices
	for(i=0;i<NO_MAT;i++){
		//Obtenemos la memoria compartida
		if((hArch[i]=OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,ids[i])) == NULL){
			printf("(hijoSuma) No se abrio archivo de mapeo de la memoria compartida para la matriz %i: (ERROR %i)\n", i, GetLastError());
			exit(-1);
		}
	} 
	
	//Abrimos la memoria compartida
	if((apDA=(unsigned char(*)[N])MapViewOfFile(hArch[0],FILE_MAP_ALL_ACCESS,0,0,TAM_MEM)) == NULL){
 		printf("(hijoSuma) No se accedio a la memoria compartida de la matriz A: (ERROR %i)\n", GetLastError());// 
 		CloseHandle(hArch[0]);
 		exit(-1);
	}

	if((apDB=(unsigned char(*)[N])MapViewOfFile(hArch[1],FILE_MAP_ALL_ACCESS,0,0,TAM_MEM)) == NULL){
 		printf("(hijoSuma) No se accedio a la memoria compartida de la matriz A: (ERROR %i)\n", GetLastError());// 
 		CloseHandle(hArch[1]);
 		exit(-1);
	}

	//Apuntamos a los segmentos para manipulacion
	apTA = apDA;
	apTB = apDB;
	
	//Primero, vamos a ejecutar al nieto
	ZeroMemory(&si,sizeof(si));
	si.cb = sizeof(si);

	ZeroMemory(&pi,sizeof(pi));
	if(!CreateProcess(NULL,path,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
		printf("(hijoSuma) Fallo al crear el proceso hijoMulti\n");
		UnmapViewOfFile(apDA);
		UnmapViewOfFile(apDB);
	 	CloseHandle(hArch[0]);
	 	CloseHandle(hArch[1]);
	 	CloseHandle(semPH);
	 	CloseHandle(semHN);
	 	CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	 	exit(1);
	}

	//Si lo pudo crear, esperamos a que el hijo termine
	WaitForSingleObject(pi.hProcess,INFINITE);

	printf("El nieto ha terminado\n");
	//Ahora ejecutamos la suma
	//A = A + B
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			apTA[i][j] = apTA[i][j] + apTB[i][j];
		}
	}

	UnmapViewOfFile(apDA);
	UnmapViewOfFile(apDB);
 	CloseHandle(hArch[0]);
 	CloseHandle(hArch[1]);
 	CloseHandle(semPH);
 	CloseHandle(semHN);
 	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
 	exit(0); 
}