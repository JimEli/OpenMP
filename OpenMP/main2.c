#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Include for timing purposes.

// C/C++ Preprocessor Definitions: _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996) 

void funcA() {
	printf("In funcA: this section is executed by thread %d\n",
		omp_get_thread_num());
}

void funcB() {
	printf("In funcB: this section is executed by thread %d\n",
		omp_get_thread_num());
}


int main(int argc, char *argv[]) {
  nt i, n=3;

#pragma omp parallel private(i)
	{
#pragma omp for
		for (i = 0; i<n; i++)
			printf("Thread %d executes loop iteration %d\n",
				omp_get_thread_num(), i);
	} // End of parallel region

#pragma omp parallel
	{
#pragma omp sections
		{
#pragma omp section
			(void)funcA();
#pragma omp section
			(void)funcB();
		} // End of sections block 
	} // End of parallel region 

	return(0);
}
