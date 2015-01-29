#include <string.h>
#include <math.h>


/* Default problem size. */
#ifndef NI
# define NI 4000
#endif
#ifndef NJ
# define NJ 4000
#endif
#ifndef NK
# define NK 4000
#endif


double alpha;
double beta;
double C[NI][NJ];
double A[NI][NK];
double B[NK][NJ];

static void init_array() {
    int i, j;
    
    alpha = 32412;
    beta = 2123;
    for (i = 0; i < NI; ) {
        for (j = 0; j < NK; ) {
            A[i][j] = ((double)i * j) / NI;
            j++;
        }
        i++;
    }
    for (i = 0; i < NK; ) {
        for (j = 0; j < NJ; ) {
            B[i][j] = ((double)i * j + 1) / NJ;
            j++;
        }
        i++;
    }
    for (i = 0; i < NI; ) {
        for (j = 0; j < NJ; ) {
            C[i][j] = ((double)i * j + 2) / NJ;
            j++;
        }
        i++;
    }
}

int main(int argc, char** argv) {
    int i, j, k;
    int ni = NI;
    int nj = NJ;
    int nk = NK;
    
    /* Initialize array. */
    init_array();
    
    
#pragma omp parallel for private (j, k) schedule(static) check
    for (i = 0; i < ni; i++)
        for (j = 0; j < nj; j++) {
            C[i][j] *= beta;
            for (k = 0; k < nk; ++k)
                C[i][j] += alpha * A[i][k] * B[k][j];
        }
    
    
    double total = 0;
    for(int y=0; y<ni; ++y){
        for(int x=0; x<nj; ++x) {
            total+= C[y][x];
        }
    }
    printf("Total: %f\n",total);
    
    return 0;
}

