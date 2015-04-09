#include <string.h>
#include <math.h>

/* Default problem size. */
#ifndef Y
# define Y 1000
#endif
#ifndef X
# define X 1000
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
    
    
    /*  C := alpha*A*A' + beta*C */
#pragma omp parallel for private(j) schedule(static) check
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            C[i][j] *= beta;
#pragma omp parallel for private(j,k) schedule(static) check
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            for (k = 0; k < m; k++)
                C[i][j] += alpha * A[i][k] * A[j][k];
        
        double total = 0;
        for(int y=0; y<Y; ++y){
            for(int x=0; x<X; ++x) {
                total+= C[y][x];
            }
        }
        printf("Total: %f\n",total);
        
        
        
        return 0;
}

