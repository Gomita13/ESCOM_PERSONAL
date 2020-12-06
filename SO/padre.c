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
#define N 5

void getCofactor(int A[N][N], int temp[N][N], int p, int q, int n){ 
    char i = 0, j = 0;
    int row = 0, col = 0;
    // Looping for each element of the matrix 
    for (row = 0; row < n; row++){ 
        for (col = 0; col < n; col++){ 
            //  Copying into temporary matrix only those element 
            //  which are not in given row and column 
            if (row != p && col != q){ 
                temp[i][j++] = A[row][col]; 
                // Row is filled, so increase row index and 
                // reset col index 
                if (j == n - 1){ 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 
} 
  
/* Recursive function for finding determinant of matrix. 
   n is current dimension of A[][]. */
int determinant(int A[N][N], int n){ 
    int D = 0; // Initialize result 
    int f = 0;
    //  Base case : if matrix contains single element 
    if (n == 1) 
        return A[0][0]; 
    int temp[N][N]; // To store cofactors 
    int sign = 1;  // To store sign multiplier  
     // Iterate for each element of first row 
    for (f = 0; f < n; f++){ 
        // Getting Cofactor of A[0][f] 
        getCofactor(A, temp, 0, f, n); 
        D += sign * A[0][f] * determinant(temp, n - 1); 
        // terms are to be added with alternate sign 
        sign = -sign; 
    } 
    return D; 
} 
  
// Function to get adjoint of A[N][N] in adj[N][N]. 
void adjoint(int A[N][N],int adj[N][N]){ 
    char i = 0, j = 0;

    if (N == 1){ 
        adj[0][0] = 1; 
        return; 
    } 
  
    // temp is used to store cofactors of A[][] 
    int sign = 1, temp[N][N]; 
    for (i=0; i<N; i++){ 
        for (j=0; j<N; j++){ 
            // Get cofactor of A[i][j] 
            getCofactor(A, temp, i, j, N); 
            // sign of adj[j][i] positive if sum of row 
            // and column indexes is even. 
            sign = ((i+j)%2==0)? 1: -1; 
            // Interchanging rows and columns to get the 
            // transpose of the cofactor matrix 
            adj[j][i] = (sign)*(determinant(temp, N-1)); 
        } 
    } 
} 
  
// Function to calculate and store inverse, returns false if 
// matrix is singular 
char inverse(int A[N][N], float inverse[N][N]){ 
    char i = 0, j = 0;
    // Find determinant of A[][] 
    int det = determinant(A, N); 
    if (det == 0){ 
        return 0; 
    } 
    // Find adjoint 
    int adj[N][N]; 
    adjoint(A, adj); 
    // Find Inverse using formula "inverse(A) = adj(A)/det(A)" 
    for (i=0; i<N; i++) 
        for (j=0; j<N; j++) 
            inverse[i][j] = adj[i][j]/det; 
    return 1; 
} 

void saveResults(int a[N][N], char *name){
	float mInv[N][N];
	char i = 0, j = 0;
	FILE *file;

	file = fopen(name,"w");

	if(inverse(a,mInv)==0){
		fprintf(file,"La matriz es singular o identidad\n");
	}else{
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				fprintf(file,"%f,",mInv[i][j]);
			}
			fprintf(file,"\n");
		}	
	}

	fclose(file);
	return;
}


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
	int A[5][5] = {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
	int B[5][5] = {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
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
		
		for(i=0;i<4;i++){
			init((void*)mats[i],5,5);
		}

		for(i=0;i<5;i++){
			for(j=0;j<5;j++){
				//Guardamos los resultados de C y D en las matrices tipo int A y B
				A[i][j] = mats[2][i][j];
				B[i][j] = mats[3][i][j];
			}
		}

		//Desvinculamos la memoria compartida y salimos del programa
		for(i=0;i<4;i++){
			shmdt(mats[i]);
		}

		printf("Guardando matrices en archivos...\n");
		saveResults(A,"suma.txt");
		printf("Resultados de la suma guardados!\n");
		saveResults(B,"multiplicacion.txt");
		printf("Resultados de la multiplicacion guardados!\n");
		exit(0);
	}
	
}