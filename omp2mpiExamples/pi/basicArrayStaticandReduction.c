#include <stdio.h>
#include <string.h>
#define N 4000

int main()
{
    double sum[N], pi, total=0;
    memset(sum,0,sizeof(double)*N);
    double step = 1.0/(double) N;
#pragma omp parallel for schedule(static) check
    for(int i = 0; i<N; ++i) {
            double x = (i+0.5) * step;
            sum[i] = 4.0/(1.0+x*x);
    }
//#pragma omp parallel for schedule(static) reduction(+:total) check
    for (int j=0; j<N; ++j){
        total += sum[j];
    }
    pi = step*total;
    printf("PI: %f\n", pi);	
    return pi;
}
