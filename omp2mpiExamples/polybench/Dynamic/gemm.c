#include <string.h>
#include <math.h>
#include <sys/time.h>

/* Default problem size. */
#ifndef NI
# define NI 4096//4096
#endif
#ifndef NJ
# define NJ 4096//4096
#endif
#ifndef NK
# define NK 4096//4096
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
struct timeval start, end;
    long mtime, seconds, useconds;    
    gettimeofday(&start, NULL);    
    
#pragma omp parallel for private (j, k) check
    for (i = 0; i < ni; i++)
        for (j = 0; j < nj; j++) {
            C[i][j] *= beta;
            for (k = 0; k < nk; ++k)
                C[i][j] += alpha * A[i][k] * B[k][j];
        }
    
 gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Elapsed time: %ld milliseconds\n", mtime);   
    double total = 0;
    for(int x=0; x<ni; ++x){
        for(int y=0; y<nj; ++y) {
            total+= C[x][y];
        }
    }
    printf("Total: %f\n",total);
    
    return 0;
}

