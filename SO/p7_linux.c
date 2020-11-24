/*
	FECHA: 24/11/2020
	AUTORA: S. GAMALIEL
	DESCRIPCIÓN:
		Programe una aplicacion que cree un proceso hijo a partir
		de un proceso padre, el proceso padre enviara al proceso hijo, a traves
		de una tuberia, dos matrices de 10x10  multiplicar por el hijo, mientras
		tanto , el proceso hijo creara un hijo de el (nieto), al cual se enviaran dos
		matrices de 10x10 (via tuberia). Una vez calculado el resultado de la suma, el 
		nieto devolvera la matriz resultando (via tuberia) a su abuelo. El hijo regresara
		la matriz resultante a su padre (via tuberia). Finalmente, el proceso padre
		obtendra la matriz inversa de cada una de las matrices recibidas y escribira los resultados
		en un archivo por matriz.
*/
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>    /* Servidor de la memoria compartida */ 
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdio.h>
#define N 10


/*
	FUNCION: sumar
	RECIBE: Apuntador a una matriz A y a una matriz B, ambas de tamaño NxN
	DESCRIPCION: SUma dos matrices de NxN
*/
void sumar(int *A, int *B){
	return;
}

/*
	FUNCION: multiplicar
	RECIBE: Apuntador a una matriz A y a una matriz B, ambas de tamaño NxN
	DESCRIPCION: Multiplica dos matrices de NxN
*/
void multiplicar(int *A, int *B){
	return;
}

void main(){
	int pidH = 0, pidN = 0, i = 0, j = 0; //idHijo, idNieto
	int A[10][10] = {{0,1,2,3,4,5,6,7,8,9},{9,8,7,6,5,4,3,2,1,0},{1,3,5,7,9,0,2,4,6,8},{0,1,2,3,4,5,6,7,8,9},{9,8,7,6,5,4,3,2,1,0},{1,3,5,7,9,0,2,4,6,8},{0,1,2,3,4,5,6,7,8,9},{0,1,2,3,4,5,6,7,8,9},{9,8,7,6,5,4,3,2,1,0},{1,3,5,7,9,0,2,4,6,8}};
	//int B[10][10] = {{0,1,2,3,4,5,6,7,8,9},{9,8,7,6,5,4,3,2,1,0},{1,3,5,7,9,0,2,4,6,8},{0,1,2,3,4,5,6,7,8,9},{9,8,7,6,5,4,3,2,1,0},{1,3,5,7,9,0,2,4,6,8},{0,1,2,3,4,5,6,7,8,9},{0,1,2,3,4,5,6,7,8,9},{9,8,7,6,5,4,3,2,1,0},{1,3,5,7,9,0,2,4,6,8}};	
	int (*ptr)[N] = (int (*)[N]) mmap(NULL,N*N*sizeof(int),PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON,-1,0);
	
	if(ptr==MAP_FAILED){
		printf("Error al mapear memoria\n");
		exit(1);
	}


	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			ptr[i][j]=A[i][j];
		}
	}
	

	pidH = fork(); //Se crea el proceso hijo
	
	if(pidH == 0){ //Se trata del hijo
		pidN = fork(); //Se crea el nieto
	}

	//Procedemos a las operaciones
	if(pidH == 0 && pidN == 0){ //Si se trata del nieto
		//Ejecuta la suma de dos matrices
		printf("Soy el nieto:\n");
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				printf("%i,",ptr[i][j]);
				ptr[i][j]=5;
			}
			printf("\n");
		}
	}else if(pidH == 0 && pidN > 0){ //Se trata del hijo
		//Ejecuta una multiplicacion de matrices
		wait(NULL);
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				printf("%i,",ptr[i][j]);
				ptr[i][j]=6;
			}
			printf("\n");
		}
	}else{//Se trata del padre
		//Ejecuta la inversa de las matrices regresadas por el hijo y nieto
		wait(NULL);
		printf("Soy el padre:\n");
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				printf("%i,",ptr[i][j]);
			}
			printf("\n");
		}
	}

	if(munmap(ptr,sizeof(A))){
		printf("Error al unmmap\n");
		exit(1);
	}
}