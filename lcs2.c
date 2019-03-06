#include <stdio.h>
#include <stdlib.h>

void print_array(int *arr, int size){
	for (int i=0; i<size; i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
}

void print_array_2D(int **arr, int rows, int cols){
	for (int i=0; i<rows; i++){
		for (int j=0; j<cols; j++)
			printf("%d ",arr[i][j]);
		printf("\n");
	}
	printf("\n");
}

int ** malloc_2d(int n, int m){
	int ** matrix = malloc(n*sizeof(int*));
	for (int row = 0; row < n; row ++){
		matrix[row] = malloc(m*sizeof(int));
	}
	return matrix;
}

void free_2d(int ** matrix, int n){
	for (int row = 0; row < n; row ++){
		free(matrix[row]);
	}
	free(matrix);
}

int max(int a, int b, int c){
	int max = a;
	if (b > max) max = b;
	if (c > max) max = c;
	return max;
}

int value(int * a, int * b, int ** matrix, int brow, int bcol, int type){
	if (type && (a[brow]==b[bcol])) return matrix[brow][bcol]+1;
	return matrix[brow][bcol];
}

int lcs2(int *a, int n,  int *b, int m) {
	//write your code here

	int ** matrix = malloc_2d(n+1,m+1);
	for (int row = 0; row < n+1; row ++){
		matrix[row][0] = 0;
	}
	for (int col = 0; col < m+1; col ++){
		matrix[0][col] = 0;
	}
	for (int row = 1; row < n+1; row ++){
		for (int col = 1; col < m+1; col ++){
			matrix[row][col] = max(value(a, b, matrix, row-1, col, 0),
														 value(a, b, matrix, row, col-1, 0),
													 	 value(a, b, matrix, row-1, col-1, 1));
		}
	}
	// print_array_2D(matrix, n+1, m+1);
	free_2d(matrix, n+1);
	return matrix[n][m];
}

int main() {
	int n, m;

	printf("Enter value of n: ");
	fflush(stdout);
	scanf("%d", &n);

	int * a = malloc(n*sizeof(int));
	printf("Enter %d values for array a, separated by spaces:\n", n);
	fflush(stdout);
	for (int i=0; i < n; i++){
		scanf("%d", &a[i]);
	}

	printf("Enter value of m: ");
	fflush(stdout);
	scanf("%d", &m);

	int * b = malloc(m*sizeof(int));
	printf("Enter %d values for array b:\n", m);
	fflush(stdout);
	for (int i=0; i < m; i++){
		scanf("%d", &b[i]);
	}

	printf("Input sequences are:\n");
	print_array(a, n);
	print_array(b, m);
	fflush(stdout);

	int lcs = lcs2(a, n, b, m);
	free(a);
	free(b);
	printf("LCS = %d\n",lcs);

	return 0;
}
