/*
	FECHA: 09-12-2020
	AUTORA: S GAMALIEL
	DESCRIPCION: Este programa realiza la suma de dos matrices
		que son dadas por un espacio de memoria compartida.
*/
#include <stdlib.h>
#include <sys/types.h>      /* Cliente de la memoria compartida */ 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
//Si modificas NO_MAT, agrega o elimina IDs en el arreglo keys[] 
#define NO_MAT 2
//Modifica el tamaño de la matriz
#define N 5 
//Modifica el tipo de dato si deseas
#define TAM_MEM  N*N*sizeof(char)

/*
	FUNCION: init
	RECIBE: Apuntador a la matriz (**matrix), numero de filas (rows)
		,numero de columnas (cols).
	DESCRIPCION: Prepara el segmento de memoria apuntado por **matrix,
		para ser utilizado como una matriz rows*cols.
	OBSERVACIONES: Debe ser llamada antes de cualquier manipulacion a la
		matriz deseada. Se puede modificar el tipo de datos para rows
		y cols, segun sea el tamaño de la matriz, actualmente el tamaño
		maximo es 255*255
*/
void init(void **matrix, unsigned char rows, unsigned char cols){
	char i = 0;
	size_t noCols = cols * sizeof(char);
	matrix[0] = matrix+noCols;
	for(i=1;i<rows;i++){
		matrix[i] = (matrix[i-1]+rows);
	}
	return;
}

void main(int argc, char *argv[]){
	char **mats[NO_MAT]; //Arreglo de matrices
	char *apDS, *apTS;
	key_t keys[NO_MAT+1] = {5510,5511,5599}; //A(10), B(11) y semaforo (99)
	int ids[NO_MAT+1];
	char i = 0, j = 0;

	//Obtengo la memoria de las matrices
	for(i=0;i<NO_MAT;i++){
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

	//Obtengo la memoria del semaforo
	ids[NO_MAT] = shmget(keys[NO_MAT],sizeof(char),0666);
	if(ids[NO_MAT] == -1){
		perror("Sem: An error ocurred during shmget():\n");
		exit(1);
	}
	//Obtengo acceso a la memoria, soy admin
	apDS = shmat(ids[NO_MAT],NULL,0);
	if(apDS == (char *) -1){
		perror("Sem: An error ocurred during shmat():\n");
		exit(1);
	}

	apTS = apDS;

	//Espero a que termine el nieto
	while(*apTS != 'h'){
		sleep(1);
	}

	for(i=0;i<NO_MAT;i++){
		init((void*)mats[i],5,5);
	}

	//A = A+B
	printf("Soy el hijo, la suma es %i:\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			mats[0][i][j] = mats[0][i][j] + mats[1][i][j];	
			printf("%i,",mats[0][i][j]);
		}
		printf("\n");
	}

	//Le paso el control al padre
	*apTS = 'p';

	//Desvinculamos la memoria compartida y salimos del programa
	for(i=0;i<NO_MAT;i++){
		shmdt(mats[i]);
	}
	exit(0);
}