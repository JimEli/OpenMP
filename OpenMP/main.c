#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h> // Include for timing purposes.

// C/C++ Preprocessor Definitions: _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996) 

// With OpenMP:
void mxvWithOpenMP(int m, int n, double *a, double *b, double *c) {
	int i, j;

#pragma omp parallel for default(none) shared(m, n, a, b, c) private(i, j)
	for (i = 0; i<m; i++) {
		//a[i] = 0.0;
		for (j = 0; j<n; j++)
			a[i] += b[i*n + j] * c[j];
	} // End of omp parallel for statement.
}

// Without OpenMP:
void mxvWithoutOpenMP(int m, int n, double *a, double *b, double *c) {
	for (int i = 0; i<m; i++) {
		//a[i] = 0.0;
		for (int j = 0; j<n; j++)
			a[i] += b[i*n + j] * c[j];
	}
}

int main(int argc, char *argv[]) {
	double *a, *b, *c;
	int m, n;

	//printf("Please give m and n: ");
	//scanf("%d %d", &m, &n);
	m = n = 10000;

	// Reserve memory for arrays.
	if ((a = (double *)malloc(m * sizeof(double))) == NULL)
		perror("memory allocation for a");
	if ((b = (double *)malloc(m*n * sizeof(double))) == NULL)
		perror("memory allocation for b");
	if ((c = (double *)malloc(n * sizeof(double))) == NULL)
		perror("memory allocation for c");

	// Initalize arrays.
	printf("Initializing matrix B and vector c\n");
	for (int j = 0; j<n; j++)
		c[j] = 2.0;
	for (int i = 0; i<m; i++)
		for (int j = 0; j<n; j++)
			b[i*n + j] = i;

	// Conduct comparison.
	printf("Executing mxv function without OpenMP for m = %d n = %d\n", m, n);
	clock_t tic = clock();	// start timer.
	mxvWithoutOpenMP(m, n, a, b, c);
	clock_t toc = clock();	// terminate timer.
	printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	printf("Executing mxv2 function with OpenMP for m = %d n = %d\n", m, n);
	tic = clock();	// start timer.
	mxvWithOpenMP(m, n, a, b, c);
	toc = clock();	// terminate timer.
	printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	// Exit
	free(a);
	free(b);
	free(c);

	return(0);
}
