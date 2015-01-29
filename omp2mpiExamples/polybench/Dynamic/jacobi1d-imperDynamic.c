#include <string.h>
#include <math.h>
#include <sys/time.h>
/* Default problem size. */
#ifndef TSTEPS
# define TSTEPS 100
#endif
#ifndef Y
# define Y 4000
#endif


double A[Y];
double B[Y];

static void init_array() {
    int i, j;
    
    for (i = 0; i < Y;) {
        A[i] = ((double)4 * i + 10) / Y;
        B[i] = ((double)7 * i + 11) / Y;
        i++;
    }
}


int main(int argc, char** argv) {
    int t, i, j;
    int tsteps = TSTEPS;
    int n = Y;
    
    /* Initialize array. */
    init_array();
struct timeval start, end;
    long mtime, seconds, useconds;    
    gettimeofday(&start, NULL);    
    
    for (t = 0; t < tsteps; t++) {
#pragma omp parallel for check
        for (i = 2; i < n - 1; i++)
            B[i] = 0.33333 * (A[i - 1] + A[i] + A[i + 1]);
#pragma omp parallel for check
        for (j = 2; j < n - 1; j++)
            A[j] = B[j];
    }
    gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Elapsed time: %ld milliseconds\n", mtime);
    double total = 0;
    for(int y=0; y<Y; ++y){
        total+= A[y];
        
    }
    printf("Total: %f\n",total);
    
    
    
    
    return 0;
}

