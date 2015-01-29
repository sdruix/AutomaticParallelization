#include <string.h>
#include <math.h>



/* Default problem size. */
#ifndef TSTEPS
# define TSTEPS 100
#endif
#ifndef N
# define N 4000
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
    
    for (t = 0; t <= tsteps - 1; t++) {
#pragma omp parallel for private (j)  schedule(static) check
        for (i = 1; i <= n - 2; i++)
            for (j = 1; j <= n - 2; j++)
                A[i][j] = (A[i - 1][j - 1] + A[i - 1][j] + A[i - 1][j + 1]
                        + A[i][j - 1] + A[i][j] + A[i][j + 1] + A[i + 1][j - 1]
                        + A[i + 1][j] + A[i + 1][j + 1]) / 9.0;
    }
    
    
    double total = 0;
    for(int y=0; y<N; ++y){
        for(int x=0; x<N; ++x) {
            total+= A[y][x];
        }
    }
    printf("Total: %f\n",total);
    
    
    return 0;
}

