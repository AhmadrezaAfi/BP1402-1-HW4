#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

// allocate enough memory for matrix
void allocateMatrix(int*** matrix, int rows, int cols) {
	*matrix = (int**)malloc(rows*sizeof(int*));
    for(int i=0; i< rows; i++){
    	(*matrix)[i] = (int*)malloc(cols*sizeof(int));
	}

}

// fill our matrix in order to be a Toeplitz matrix
void fillToeplitz(int** matrix, int n, int* ptr) {
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			int dif = j-i;
			if(dif<0)
			    dif = dif*-1+n-1;
			matrix[i][j] = ptr[dif];
		}
	}

}

// check elements f matrix
int checkMatrix(int** matrix, int i, int j){
    return matrix[i-1][j-1];
}

// printMatrix
void printMatrix(int** matrix, int rows, int cols) {
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			printf("%d,  ", *(*(matrix+i)+j));
		}
		printf("\n");
	}
	printf("\n");

}

// calculate determinant of our matrix
int determinantMatrix(int** matrix, int n) {
	int det=0;
	if (n==2){
		det= matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0];
		return det;
	}
	for (int i=0; i<n; i++){
		int** arr1;
		allocateMatrix(&arr1, n-1, n-1);
		for (int j=0; j<n-1; j++){
			for(int m=0; m<n-1; m++){
				if (m>=i){
					(arr1)[j][m] = matrix[j+1][m+1];
				}
				else{
				    (arr1)[j][m] = matrix[j+1][m];
			    }
			}                                 

		}
//		printMatrix(*arr1, n-1, n-1);
		if (i%2==0) 
		    det=det+determinantMatrix(arr1, n-1)*matrix[0][i];
		else
		    det=det-determinantMatrix(arr1, n-1)*matrix[0][i];
	}
	return det;
}


// free the memory
void freeMatrix(int** matrix, int rows) {
	for(int i=0; i<rows; i++){
		free(matrix[i]);
	}
	free(matrix);

}

