#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define TAM_MEM 25
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
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE hArchA = NULL, hArchB = NULL, hArchC = NULL, hArchD = NULL;
	char *idA = "MatrizA";
	char *idB = "MatrizB";
	char *idC = "MatrizC";
	char *idD = "MatrizD";
	unsigned char matA[5][5] = {{1,2,3,4,5},{6,7,8,9,0},{5,4,3,2,1},{8,7,6,5,4},{4,7,8,9,1}};
	unsigned char matB[5][5] = {{1,2,3,4,5},{6,7,8,9,0},{5,4,3,2,1},{8,7,6,5,4},{4,7,8,9,1}};
	char path[] = "C:/Users//gamma//Documents//Programas//ESCOM_PERSONAL//SO//WINDOWS//hijoSuma.exe";
	unsigned char (*apDA)[5], (*apTA)[5], (*apDB)[5], (*apTB)[5], (*apDC)[5], (*apTC)[5], (*apDD)[5], (*apTD)[5], i = 0, j = 0;

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

	if((apDA=(unsigned char(*)[5])MapViewOfFile(hArchA, // Manejador del mapeo 
	                         FILE_MAP_ALL_ACCESS, // Permiso de lectura/escritura en la memoria
	                         0,0,TAM_MEM)) == NULL){
 		printf("No se accedio a la memoria compartida de la matriz A: (%i)\n", GetLastError());// 
 		CloseHandle(hArchA);
 		exit(-1);
 	}

 	if((apDB=(unsigned char(*)[5])MapViewOfFile(hArchB, // Manejador del mapeo 
	                         FILE_MAP_ALL_ACCESS, // Permiso de lectura/escritura en la memoria
	                         0,0,TAM_MEM)) == NULL){
 		printf("No se accedio a la memoria compartida de la matriz B: (%i)\n", GetLastError());// 
 		CloseHandle(hArchB);
 		exit(-1);
 	}

 	if((apDC=(unsigned char(*)[5])MapViewOfFile(hArchC, // Manejador del mapeo 
	                         FILE_MAP_ALL_ACCESS, // Permiso de lectura/escritura en la memoria
	                         0,0,TAM_MEM)) == NULL){
 		printf("No se accedio a la memoria compartida de la matriz C: (%i)\n", GetLastError());// 
 		CloseHandle(hArchC);
 		exit(-1);
 	}

 	if((apDD=(unsigned char(*)[5])MapViewOfFile(hArchD, // Manejador del mapeo 
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
 	
	printf("Hijos terminados\n");

	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			matA[i][j] = apTC[i][j];
			matB[i][j] = apTD[i][j];
		}
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
 	CloseHandle(hArchA);   
 	CloseHandle(hArchB);   
 	CloseHandle(hArchC);   
 	exit(0); 
}