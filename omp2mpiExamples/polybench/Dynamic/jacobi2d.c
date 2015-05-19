#include <string.h>
#include <math.h>

/* Default problem size. */
#ifndef TSTEPS
# define TSTEPS 50//100
#endif
#ifndef Y
# define Y 4096//4000
#endif


/* Array declaration. Enable malloc if POLYBENCH_TEST_MALLOC. */
double A[Y][Y];
double B[Y][Y];

static void init_array() {
    int i, j;
    
    for (i = 0; i < Y;) {
        for (j = 0; j < Y;) {
            A[i][j] = ((double)i * (j + 2) + 10) / Y;
            B[i][j] = ((double)(i - 4) * (j - 1) + 11) / Y;
            j++;
        }
        i++;
    }
    
}


int main(int argc, char** argv) {
    int t, i, j;
    int tsteps = TSTEPS;
    int n = Y;
    
    /* Initialize array. */
    init_array();
    
    
    
    for (t = 0; t < tsteps; t++) {
#pragma omp parallel for private(i,j) check
        for (i = 2; i < n - 1; i++)
            for (j = 2; j < n - 1; j++)
                B[i][j] = 0.2 * (A[i][j] + A[i][j - 1] + A[i][1 + j] + A[1 + i][j]
                        + A[i - 1][j]);
#pragma omp parallel for private(i,j) check
        for (i = 2; i < n - 1; i++)
            for (j = 2; j < n - 1; j++)
                A[i][j] = B[i][j];
    }
    
    
    double total = 0;
    for(int x=2; x<Y-1; ++x){
        for(int y=2; y<Y-1; ++y) {
            total+= A[x][y];
        }
    }
    printf("Total: %f\n",total);
    
    
    return 0;
}
