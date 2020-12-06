/*
	FECHA: 09-12-2020
	AUTORA: S GAMALIEL
	DESCRIPCION: Este programa crea cuatro espacios de memoria
		compartida donde se almacenan 4 matrices. Crea una hijo
		que se encarga de sumar las matrices 1 y 2.
*/
#include <stdlib.h>
#include <sys/types.h>      /* Cliente de la memoria compartida */ 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <unistd.h>
#include <wait.h>
#define TAM_MEM  25 

void init(void **matrix, char rows, char cols){
	char i = 0;
	size_t noCols = cols * sizeof(char);
	matrix[0] = matrix+noCols;
	for(i=1;i<rows;i++){
		matrix[i] = (matrix[i-1]+rows);
	}
	return;
}

void main(){

	char **mats[4] = {NULL,NULL,NULL,NULL}; //Arreglo de matrices
	key_t keys[4] = {5510,5511,5512,5513}; //Los ultimos dos numeros son hex
	int ids[4] = {-1,-1,-1,-1};
	char i = 0, j = 0, k = 0;
	int idChild = -1, idCChild = -1;

	//Obtengo la memoria de las tres matrices
	for(i=0;i<4;i++){
		ids[i] = shmget(keys[i],TAM_MEM,IPC_CREAT|0666);
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

	//Vamos a inicializar las matrices
	for(i=0;i<4;i++){
		init((void *)mats[i],5,5);
	}
	
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			mats[0][i][j] = 1;
			mats[1][i][j] = 1;
			mats[2][i][j] = 1;
			mats[3][i][j] = 1;		
		}
	}

	//Creamos un hijo que realiza la suma de las matrices A y B
	idChild = fork();
	if(idChild < 0){
		perror("Error ocurred during child creation:\n");
		exit(1);
	}

	//Verificamos de quien se trata
	if(idChild == 0){ //Es el hijo
		char *argv[1];
		argv[0] = NULL;
		idCChild = fork();
		if(idCChild > 0){
			execv("./hijoSuma",argv);
		}else if(idCChild == 0){
			execv("./hijoMulti",argv);
		}
	}else{//Es el padre
		wait(NULL);
		printf("Mi chavo me envia esto:\n");
		for(i=0;i<4;i++){
			init((void*)mats[i],5,5);
		}
		for(i=0;i<5;i++){
			for(j=0;j<5;j++){
				printf("%i,",mats[3][i][j]);
			}
			printf("\n");
		}
		//Desvinculamos la memoria compartida y salimos del programa
		for(i=0;i<4;i++){
			shmdt(mats[i]);
		}
		exit(0);
	}
	
}