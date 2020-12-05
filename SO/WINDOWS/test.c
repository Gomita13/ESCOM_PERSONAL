#include <stdio.h>

void init(int a[2][2]){
	char i = 0, j = 0;
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			a[i][j] = 69;
		}
	}
	return;
}

void main(){
	int A[2][2];
	char i = 0, j = 0;
	init(A);
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			printf("%i,",A[i][j]);
		}
		printf("\n");
	}
}