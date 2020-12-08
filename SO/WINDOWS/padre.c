/*
	FECHA: 09-12-2020
	AUTORA: S GAMALIEL
	DESCRIPCION: Este programa crea cuatro espacios de memoria
		compartida donde se almacenan 4 matrices. Crea una hijo
		que se encarga de sumar las matrices 1 y 2.
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
//Si modificas NO_MAT, agrega o elimina IDs en el arreglo keys[] 
#define NO_MAT 3
//Modifica el tamaño de la matriz
#define N 5 
//Modifica el tipo de dato si deseas
#define TAM_MEM  N*N*sizeof(char)

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

/*
	FUNCION: saveResults
	RECIBE: Una matriz de enteros (a) y un nombre para el 
		archivo que almacenara sus datos (*name)
	DESCRIPCION: Obtiene la matriz inversa de la matriz dada
		(si es que aplica) y guarda la matriz en el archivo
		especificado. Si no hay inversa guarda la indicacion
		de que no existe.
	OBSERVACIONES: El nombre es un archivo .txt para poder ser
		visualizado.
*/
void saveResults(unsigned char a[N][N], char *name){
	int m[N][N];
	float mInv[N][N];
	char i = 0, j = 0;
	FILE *file;

	file = fopen(name,"w");

	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			m[i][j]=a[i][j];
	if(inverse(m,mInv)==0){
		fprintf(file,"La matriz es singular o identidad\n");
	}else{
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				fprintf(file,"%i,",mInv[i][j]);
			}
			fprintf(file,"\n");
		}	
	}

	fclose(file);
	return;
}

void main(){
	//Estructuras para la creacion de procesos hijos
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE hArch[NO_MAT] = {NULL,NULL,NULL}; //Arreglo de handlers para las matrices
	char *ids[NO_MAT] = {"MatrizA","MatrizB","MatrizC"};
	//Direccion al programa que ejecutara el proceso hijo
	char path[] = "C:/Users//gamma//Documents//Programas//ESCOM_PERSONAL//SO//WINDOWS//hijoSuma.exe";
	char i = 0, j = 0; 
	unsigned char matA[N][N] = {{1,2,3,4,5},{6,7,8,9,0},{5,4,3,2,1},{8,7,6,5,4},{4,7,8,9,1}};
	unsigned char matB[N][N] = {{1,2,3,4,5},{6,7,8,9,0},{5,4,3,2,1},{8,7,6,5,4},{4,7,8,9,1}};
	unsigned char (*apDA)[N], (*apDB)[N], (*apDC)[N];
	unsigned char (*apTA)[N], (*apTB)[N], (*apTC)[N];
	//Obtenemos la memoria para las matrices
	for(i=0;i<NO_MAT;i++){
		//Obtenemos la memoria compartida
		if((hArch[i]=OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,ids[i])) == NULL){
			printf("No se abrio archivo de mapeo de la memoria compartida para la matriz %i: (ERROR %i)\n", i, GetLastError());
			exit(-1);
		}
	}


	if((apDA=(unsigned char(*)[N])MapViewOfFile(hArch[0],FILE_MAP_ALL_ACCESS,0,0,TAM_MEM)) == NULL){
 		printf("No se accedio a la memoria compartida de la matriz A: (%i)\n", GetLastError());// 
 		CloseHandle(hArch[0]);
 		exit(-1);
 	}

 	if((apDB=(unsigned char(*)[N])MapViewOfFile(hArch[1],FILE_MAP_ALL_ACCESS,0,0,TAM_MEM)) == NULL){
 		printf("No se accedio a la memoria compartida de la matriz A: (%i)\n", GetLastError());// 
 		CloseHandle(hArch[1]);
 		exit(-1);
 	}

 	if((apDC=(unsigned char(*)[N])MapViewOfFile(hArch[2],FILE_MAP_ALL_ACCESS,0,0,TAM_MEM)) == NULL){
 		printf("No se accedio a la memoria compartida de la matriz A: (%i)\n", GetLastError());// 
 		CloseHandle(hArch[2]);
 		exit(-1);
 	}

 	//Apuntadores para poder manipular las matrices
 	apTA = apDA;
 	apTB = apDB;
 	apTC = apDC;

 	//Inicializamos las matrices
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			apTA[i][j]=matA[i][j];
			apTB[i][j]=matB[i][j];
			apTC[i][j]=0;
		}
	}

	//Creamos el proceso hijo
	ZeroMemory(&si,sizeof(si));
	si.cb = sizeof(si);

	ZeroMemory(&pi,sizeof(pi));
	if(!CreateProcess(NULL,path,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
		printf("Fallo al crear el proceso hijoSuma\n");
		UnmapViewOfFile(apDA);
	 	UnmapViewOfFile(apDB);
	 	UnmapViewOfFile(apDC);   
	 	CloseHandle(hArch[0]);   
	 	CloseHandle(hArch[1]);   
	 	CloseHandle(hArch[2]);   	
	 	exit(1);
	}

	//Si lo pudo crear
	WaitForSingleObject(pi.hProcess,INFINITE);
 	
	printf("Hijos terminados\n");

	//Vaciamos las matrices resultantes en matA y matB
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			matA[i][j] = apTA[i][j];
			matB[i][j] = apTC[i][j];
		}
	}

	printf("La matriz C = A + B es:\n");
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			printf("%i,",matB[i][j]);
		}
		printf("\n");
	}	

	printf("La matriz C = A * B es:\n");
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			printf("%i,",matA[i][j]);
		}
		printf("\n");
	}

	saveResults(matA,"suma.txt");
	printf("Guardados los resultados de la suma\n");
	saveResults(matB,"multiplicacion.txt");
	printf("Guardados los resultados de la multiplicacion\n");

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
 	UnmapViewOfFile(apDA);
 	UnmapViewOfFile(apDB);
 	UnmapViewOfFile(apDC);   
 	CloseHandle(hArch[0]);   
 	CloseHandle(hArch[1]);   
 	CloseHandle(hArch[2]);   
 	exit(0); 
}