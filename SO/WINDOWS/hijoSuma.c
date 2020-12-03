#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define TAM_MEM 25

void main(){
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE hArchA = NULL, hArchB = NULL, hArchC = NULL;
	char *idA = "MatrizA";
	char *idB = "MatrizB";
	char *idC = "MatrizC";
	char path[] = "C:/Users//gamma//Documents//Programas//ESCOM_PERSONAL//SO//WINDOWS//hijoMulti.exe";
	char (*apDA)[5], (*apTA)[5], (*apDB)[5], (*apTB)[5], (*apDC)[5], (*apTC)[5], i = 0, j = 0;

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

	if((hArchC=OpenFileMapping(
			FILE_MAP_ALL_ACCESS,// acceso lectura/escritura de la memoria compartida
			FALSE,// no se hereda el nombre                  
			idC))// identificador de la memoria compartida
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

 	if((apDC=(char(*)[5])MapViewOfFile(hArchC, // Manejador del mapeo 
	                         FILE_MAP_ALL_ACCESS, // Permiso de lectura/escritura en la memoria
	                         0,0,TAM_MEM)) == NULL){
 		printf("No se accedio a la memoria compartida de la matriz B: (%i)\n", GetLastError());// 
 		CloseHandle(hArchB);
 		exit(-1);
 	}

 	apTA = apDA;
 	apTB = apDB;
 	apTC = apDC;

	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			apTC[i][j] = apTA[i][j] + apTB[i][j];
		}
	}
	
	ZeroMemory(&si,sizeof(si));
	si.cb = sizeof(si);

	ZeroMemory(&pi,sizeof(pi));
	if(!CreateProcess(NULL,path,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
		printf("Fallo al crear el proceso hijoMulti\n");
		UnmapViewOfFile(apDA);
	 	UnmapViewOfFile(apDB);
	 	UnmapViewOfFile(apDC);   
	 	CloseHandle(hArchA);   
	 	CloseHandle(hArchB);   
	 	CloseHandle(hArchC);   	
	 	exit(1);
	}

	//Si lo pudo crear
	WaitForSingleObject(pi.hProcess,INFINITE);

 	UnmapViewOfFile(apDA);
 	UnmapViewOfFile(apDB);
 	UnmapViewOfFile(apDC);   
 	CloseHandle(hArchA);   
 	CloseHandle(hArchB);   
 	CloseHandle(hArchC);   
 	exit(0); 
}