/*
	FECHA: 09-12-2020
	AUTORA: S GAMALIEL
	DESCRIPCION: Este programa realiza la multiplicacion de dos matrices
		que son dadas por un espacio de memoria compartida.
*/
#include <stdlib.h>
#include <sys/types.h>      /* Cliente de la memoria compartida */ 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#define TAM_MEM  25 
#define N 5

void init(void **matrix, char rows, char cols){
	char i = 0;
	size_t noCols = cols * sizeof(char);
	matrix[0] = matrix+noCols;
	for(i=1;i<rows;i++){
		matrix[i] = (matrix[i-1]+rows);
	}
	return;
}

void main(int argc, char *argv[]){
	char **mats[3]; //Arreglo de matrices
	key_t keys[3] = {5510,5511,5513}; //Los ultimos dos numeros son hex
	int ids[3];
	char i = 0, j = 0, k = 0;

	//Obtengo la memoria de las tres matrices
	for(i=0;i<3;i++){
		ids[i] = shmget(keys[i],TAM_MEM,0666);
		if(ids[i] == -1){
			perror("An error ocurred during shmget():\n");
			exit(1);
		}
		//Obtengo acceso a la memoria, soy admin
		mats[i] = shmat(ids[i],NULL,0);
		if(mats[i] == (char **) -1){
			perror("An error ocurred during shmat():\n");
			exit(1);
		}
	}

	for(i=0;i<3;i++){
		init((void*)mats[i],5,5);
	}

	//Multiplicamos las matrices
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			mats[2][j][i]=0;
			for(k=0;k<N;k++){
				mats[2][j][i] += mats[0][j][k]*mats[1][k][i];
			}
		}
	}

	//Desvinculamos la memoria compartida y salimos del programa
	for(i=0;i<3;i++){
		shmdt(mats[i]);
	}
	exit(0);
}