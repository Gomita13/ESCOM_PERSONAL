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
#include <sys/sem.h>
#include <stdio.h> 
#include <unistd.h>
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
	char *apDS;
	key_t keys[NO_MAT+2] = {5510,5511,5598,5599}; //A(10), B(11), semaforoPH (98) y semfaoroHN(99)
	int ids[NO_MAT+2];
	char i = 0, j = 0;
	struct sembuf bf1 = {0,-1,0};
	struct sembuf bf2 = {0,1,0};

	//Obtengo la memoria de las matrices
	for(i=0;i<NO_MAT;i++){
		ids[i] = shmget(keys[i],TAM_MEM,0666);
		if(ids[i] == -1){
			perror("(hijoSuma.c) An error ocurred during shmget():\n");
			exit(1);
		}
		//Obtengo acceso a la memoria, soy admin
		mats[i] = shmat(ids[i],NULL,0);
		if(mats[i] == (char **) -1){
			perror("(hijoSuma.c) An error ocurred during shmat():\n");
			exit(1);
		}
	}

	//Obtengo el semaforo de mi padre//Creamos el semaforo 
	if((ids[NO_MAT] = semget(keys[NO_MAT],1,0)) == -1){
		printf("(hijoSuma.c) An error ocurred during semget(PH)\n");
		exit(-1);	
	}

	//Lo bloqueo
	if(semop(ids[NO_MAT],&bf1,1) == -1){
		printf("(hijoSuma.c) An error ocurred during semop(PH-lock)\n");
		exit(-1);
	}	

	//Creo mi propio semaforo para compartir con mi hijo
	if((ids[NO_MAT+1] = semget(keys[NO_MAT+1],1,IPC_CREAT | 0666)) == -1){
		printf("(hijoSuma.c) An error ocurred during semget(HN)\n");
		exit(-1);	
	}

	//Libero el semaforoHN
	if(semop(ids[NO_MAT+1],&bf2,1) == -1){
		printf("(hijoSuma.c) An error ocurred during semop(HN-unlock)\n");
		exit(-1);
	}

	//Le doy chance de bloquear el semaofor a mi hijo
	sleep(4);

	//Ya lo libero, ahora yo lo bloqueo
	bf2.sem_op = -1;
	//Espero a que libere el semaforo
	if(semop(ids[NO_MAT+1],&bf2,1) == -1){
		printf("(hijoSuma.c) An error ocurred during semop(HN-lock)\n");
		exit(-1);
	}

	for(i=0;i<NO_MAT;i++){
		init((void*)mats[i],5,5);
	}

	//A = A+B
	printf("Soy el hijo, la suma es:\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			mats[0][i][j] = mats[0][i][j] + mats[1][i][j];	
			printf("%i,",mats[0][i][j]);
		}
		printf("\n");
	}

	//Desvinculamos la memoria compartida y salimos del programa
	for(i=0;i<NO_MAT;i++){
		shmdt(mats[i]);
	}
	
	//Desbloqueo el semaforo del padre
	bf1.sem_op = 1;
	if(semop(ids[NO_MAT],&bf1,1) == -1){
		printf("(hijoSuma.c) An error ocurred during semop(PH-unlock)\n");
		exit(-1);
	}


	exit(0);
}