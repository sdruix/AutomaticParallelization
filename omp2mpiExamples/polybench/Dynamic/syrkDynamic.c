#include <string.h>
#include <math.h>
#include <sys/time.h>
/* Default problem size. */
#ifndef Y
# define Y 4000//1000
#endif
#ifndef X
# define X 4000//1000
#endif

double alpha;
double beta;
double A[Y][X];
double C[Y][Y];

static void init_array() {
    int i, j;
    
    alpha = 12435;
    beta = 4546;
    for (i = 0; i < Y;) {
        for (j = 0; j < X;) {
            A[i][j] = ((double)i * j) / Y;
            j++;
        }
        for (j = 0; j < Y; ) {
            C[i][j] = ((double)i * j + 2) / Y;
            j++;
        }
        i++;
    }
}


int main(int argc, char** argv) {
    int i, j, k;
    int n = Y;
    int m = X;
    
    /* Initialize array. */
    init_array();
 struct timeval start, end;
    long mtime, seconds, useconds;    
    gettimeofday(&start, NULL);   
    
    /*  C := alpha*A*A' + beta*C */
#pragma omp parallel for private(j) check
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            C[i][j] *= beta;
#pragma omp parallel for private(j,k) check
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            for (k = 0; k < m; k++)
                C[i][j] += alpha * A[i][k] * A[j][k];
 gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Elapsed time: %ld milliseconds\n", mtime);       
        double total = 0;
        for(int y=0; y<Y; ++y){
            for(int x=0; x<X; ++x) {
                total+= C[y][x];
            }
        }
        printf("Total: %f\n",total);
        
        
        
        return 0;
}

