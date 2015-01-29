#include <stdio.h>
#define N 4000

int main()
{
	double sum=0, pi;
	double step = 1.0/(double) N;
#pragma omp parallel for schedule(static) reduction(+:sum) check
	for(int i = 0; i<N; ++i) {
		double x = (i+0.5) * step;
		sum = sum + 4.0/(1.0+x*x);
	}
	pi = step*sum;
	printf("PI: %f\n", pi);	
	return pi;
}

