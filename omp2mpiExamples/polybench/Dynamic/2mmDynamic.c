#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

/* Default problem size. */
#ifndef NI
# define NI 4096
#endif
#ifndef NJ
# define NJ 4096
#endif
#ifndef NK
# define NK 4096
#endif
#ifndef NL
# define NL 4096
#endif


double alpha1;
double beta1;
double alpha2;
double beta2;
double C[NI][NJ];
double A[NI][NK];
double B[NK][NJ];
double D[NJ][NL];
double E[NI][NL];

static void init_array() {
    int i, j;
    
    alpha1 = 32412;
    beta1 = 2123;
    alpha2 = 132412;
    beta2 = 92123;
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
    for (i = 0; i < NJ; ) {
        for (j = 0; j < NL; ) {
            D[i][j] = ((double)i * j + 2) / NJ;
            j++;
        }
        i++;
    }
    for (i = 0; i < NI; ) {
        for (j = 0; j < NL; ) {
            E[i][j] = ((double)i * j + 2) / NJ;
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
    int nl = NL;
    /* Initialize array. */
    init_array();
    struct timeval start, end;
    long mtime, seconds, useconds;  
    
    gettimeofday(&start, NULL);
    
#pragma omp parallel for private (j, k) check
    for (i = 0; i < ni; i++)
        for (j = 0; j < nj; j++) {
            C[i][j] = 0;
            for (k = 0; k < nk; ++k) 
                    C[i][j] += A[i][k] * B[k][j];

        }
  
#pragma omp parallel for private (j, k) check
    for (i = 0; i < ni; i++)
        for (j = 0; j < nl; j++) {
            E[i][j] = 0;
            for (k = 0; k < nj; ++k)
                E[i][j] += C[i][k] * D[k][j];
        }
    gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Elapsed time: %ld milliseconds\n", mtime);
    double total = 0;
    for(int y=0; y<ni; ++y){
        for(int x=0; x<ni; ++x) {
            total+= E[y][x];
        }
    }
    printf("Total: %f\n",total);
    return 0;
}

