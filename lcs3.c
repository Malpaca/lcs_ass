#include <stdio.h>
#include <stdlib.h>

void print_array(int *arr, int size){
	for (int i=0; i<size; i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
}

int *** malloc_3d(int n, int m, int l){
	int *** matrix = malloc(n*sizeof(int**));
	for (int x = 0; x < n; x ++){
		matrix[x] = malloc(m*sizeof(int*));
		for (int y = 0; y < m; y++){
			matrix[x][y] = malloc(l*sizeof(int));
		}
	}
	return matrix;
}

void free_3d(int *** matrix, int n, int m){
	for (int x = 0; x < n; x ++){
		for (int y = 0; y < m; y++){
			free(matrix[x][y]);
		}
		free(matrix[x]);
	}
	free(matrix);
}

int max(int a, int b, int c, int d){
	int max = a;
	if (b > max) max = b;
	if (c > max) max = c;
	if (d > max) max = d;
	return max;
}

int value(int * a, int * b, int* c, int *** matrix, int bx, int by, int bz, int type){
	if (type && (a[bx]==b[by] && b[by]==c[bz])) return matrix[bx][by][bz]+1;
	return matrix[bx][by][bz];
}

int lcs3(int *a, int n,  int *b, int m, int *c, int l) {
	//write your code here

	int *** matrix = malloc_3d(n+1,m+1,l+1);
	for (int x = 0; x < n+1; x ++){
		matrix[x][0][0] = 0;
	}
	for (int y = 0; y < m+1; y ++){
		matrix[0][y][0] = 0;
	}
	for (int z = 0; z < l+1; z ++){
		matrix[0][0][z] = 0;
	}
	for (int x = 1; x < n+1; x ++){
		for (int y = 1; y < m+1; y ++){
			for (int z = 1; z < l+1; z++){
				matrix[x][y][z] = max(value(a, b, c, matrix, x-1, y, z, 0),
													 	  value(a, b, c, matrix, x, y-1, z, 0),
													    value(a, b, c, matrix, x, y, z-1, 0),
													    value(a, b, c, matrix, x-1, y-1, z-1, 1));
			}
		}
	}
	free_3d(matrix, n+1, m+1)
	return matrix[n][m][l];
}

int main() {
	int n, m, l;

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

	printf("Enter value of l: ");
	fflush(stdout);
	scanf("%d", &l);

	int * c = malloc(l*sizeof(int));
	printf("Enter %d values for array b:\n", l);
	fflush(stdout);
	for (int i=0; i < l; i++){
		scanf("%d", &c[i]);
	}

	printf("Input sequences are:\n");
	print_array(a, n);
	print_array(b, m);
	print_array(c, l);
	fflush(stdout);

	int lcs = lcs3(a, n, b, m, c, l);
	printf("LCS = %d\n",lcs);

	return 0;
}
