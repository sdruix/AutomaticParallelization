#include <string.h>
#include <math.h>
#include <sys/time.h>


/* Default problem size. */
#ifndef TSTEPS
# define TSTEPS 100//25
#endif
#ifndef N
# define N 4000//1000
#endif



double A[N][N];

static void init_array() {
    int i, j;
    
    for (i = 0; i < N;) {
        for (j = 0; j < N;) {
            A[i][j] = ((double)(i - 3) * j + 10) / N;
            j++;
        }
        i++;
    }
}


int main(int argc, char** argv) {
    int t, i, j;
    int tsteps = TSTEPS;
    int n = N;
    
    /* Initialize array. */
    init_array();
struct timeval start, end;
    long mtime, seconds, useconds;    
    gettimeofday(&start, NULL);    
    for (t = 0; t <= tsteps - 1; t++) {
#pragma omp parallel for private (j)  check
        for (i = 1; i <= n - 2; i++) 
            for (j = 1; j <= n - 2; j++)        
                A[i][j] = (A[i - 1][j - 1] + A[i - 1][j] + A[i - 1][j + 1]
                        + A[i][j - 1] + A[i][j] + A[i][j + 1] + A[i + 1][j - 1]
                        + A[i + 1][j] + A[i + 1][j + 1]) / 9.0;
            
        
    }
    
gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Elapsed time: %ld milliseconds\n", mtime);    
    double total = 0;
    for(int y=1; y<N; ++y){
        for(int x=0; x<N; ++x) {
            total+= A[y][x];
        }
    }
    printf("Total: %f\n",total);
    
    
    return 0;
}

