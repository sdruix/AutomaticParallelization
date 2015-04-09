#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#define N 4000

int main()
{
    double sum[N], pi, total=0;
    memset(sum,0,sizeof(double)*N);
    
    double step;
    


        step = 1.0/(double) N;
    
    
    struct timeval start, end;
    long mtime, seconds, useconds;    
    gettimeofday(&start, NULL);
#pragma omp parallel for check
    for(int i = 0; i<N; ++i) {
            double x = (i+0.5) * step;
            sum[i] = 4.0/(1.0+x*x);    
    }
//#pragma omp parallel for reduction(+:total) check
    for (int j=0; j<N; ++j){
        total += sum[j];
    }
     gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Elapsed time: %ld milliseconds\n", mtime);

    pi = step*total;
    printf("PI: %f\n", pi);	
    return pi;
}
