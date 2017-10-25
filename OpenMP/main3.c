#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Include for timing purposes.

// C/C++ Preprocessor Definitions: _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996) 

//
// Simplistic dot-product demonstartion.
//
#define SIZE 10000

int main(void) {
	volatile double sum;
	volatile double a[SIZE], b[SIZE];
	int i, n = SIZE;
	
	for (i = 0; i < n; i++) {
		a[i] = i * 0.5;
		b[i] = i * 2.0;
	}

	sum = 0;
#pragma omp parallel for default(none) reduction(+:sum) 
	for (i = 0; i < n; i++) {
		sum = sum + a[i] * b[i];
	}

	printf("sum = %lf\n", sum);
}
