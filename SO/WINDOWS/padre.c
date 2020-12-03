#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define TAM_MEM 25

void main(){
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE hArchA = NULL, hArchB = NULL, hArchC = NULL, hArchD = NULL;
	char *idA = "MatrizA";
	char *idB = "MatrizB";
	char *idC = "MatrizC";
	char *idD = "MatrizD";
	char matA[5][5] = {{1,2,3,4,5},{6,7,8,9,0},{5,4,3,2,1},{8,7,6,5,4},{4,7,8,9,1}};
	char matB[5][5] = {{1,2,3,4,5},{6,7,8,9,0},{5,4,3,2,1},{8,7,6,5,4},{4,7,8,9,1}};
	char path[] = "C:/Users//gamma//Documents//Programas//ESCOM_PERSONAL//SO//WINDOWS//hijoSuma.exe";
	char (*apDA)[5], (*apTA)[5], (*apDB)[5], (*apTB)[5], (*apDC)[5], (*apTC)[5], (*apDD)[5], (*apTD)[5], i = 0, j = 0;

	//Obten la memoria compartida
	if((hArchA=CreateFileMapping(INVALID_HANDLE_VALUE,// usa memoria compartida
	                  NULL,// seguridad por default
	                  PAGE_READWRITE,// acceso lectura/escritura a la memoria  
	                  0,// tamaño maxixmo parte alta de un DWORD
	                  TAM_MEM,// tamaño maxixmo parte baja de un DWORD
	                  idA)// identificador de la memoria compartida
	                  ) == NULL){
		printf("No se mapeo la memoria compartida para la matriz A: (%i)\n", GetLastError());
		exit(-1);
	}


	if((hArchB=CreateFileMapping(INVALID_HANDLE_VALUE,// usa memoria compartida
	                  NULL,// seguridad por default
	                  PAGE_READWRITE,// acceso lectura/escritura a la memoria  
	                  0,// tamaño maxixmo parte alta de un DWORD
	                  TAM_MEM,// tamaño maxixmo parte baja de un DWORD
	                  idB)// identificador de la memoria compartida
	                  ) == NULL){
		printf("No se mapeo la memoria compartida para la matriz B: (%i)\n", GetLastError());
		exit(-1);
	}

	if((hArchC=CreateFileMapping(INVALID_HANDLE_VALUE,// usa memoria compartida
	                  NULL,// seguridad por default
	                  PAGE_READWRITE,// acceso lectura/escritura a la memoria  
	                  0,// tamaño maxixmo parte alta de un DWORD
	                  TAM_MEM,// tamaño maxixmo parte baja de un DWORD
	                  idC)// identificador de la memoria compartida
	                  ) == NULL){
		printf("No se mapeo la memoria compartida para la matriz C: (%i)\n", GetLastError());
		exit(-1);
	}	

	if((hArchD=CreateFileMapping(INVALID_HANDLE_VALUE,// usa memoria compartida
	                  NULL,// seguridad por default
	                  PAGE_READWRITE,// acceso lectura/escritura a la memoria  
	                  0,// tamaño maxixmo parte alta de un DWORD
	                  TAM_MEM,// tamaño maxixmo parte baja de un DWORD
	                  idD)// identificador de la memoria compartida
	                  ) == NULL){
		printf("No se mapeo la memoria compartida para la matriz C: (%i)\n", GetLastError());
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
 		printf("No se accedio a la memoria compartida de la matriz C: (%i)\n", GetLastError());// 
 		CloseHandle(hArchC);
 		exit(-1);
 	}

 	if((apDD=(char(*)[5])MapViewOfFile(hArchD, // Manejador del mapeo 
	                         FILE_MAP_ALL_ACCESS, // Permiso de lectura/escritura en la memoria
	                         0,0,TAM_MEM)) == NULL){
 		printf("No se accedio a la memoria compartida de la matriz D: (%i)\n", GetLastError());// 
 		CloseHandle(hArchD);
 		exit(-1);
 	}

 	apTA = apDA;
 	apTB = apDB;
 	apTC = apDC;
	apTD = apDD;

	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			apTA[i][j]=matA[i][j];
			apTB[i][j]=matB[i][j];
			apTC[i][j]=0;
			apTD[i][j]=8;
		}
	}

	ZeroMemory(&si,sizeof(si));
	si.cb = sizeof(si);

	ZeroMemory(&pi,sizeof(pi));
	if(!CreateProcess(NULL,path,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
		printf("Fallo al crear el proceso hijoSuma\n");
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
 	
	printf("Mi chavo me envia esto:\n");

	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			printf("%i,",apTC[i][j]);
		}
		printf("\n");
	}

	printf("Mi nieto me envia esto:\n");

	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			printf("%i,",apTD[i][j]);
		}
		printf("\n");
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
 	UnmapViewOfFile(apDA);
 	UnmapViewOfFile(apDB);
 	UnmapViewOfFile(apDC);   
 	CloseHandle(hArchA);   
 	CloseHandle(hArchB);   
 	CloseHandle(hArchC);   
 	exit(0); 
}