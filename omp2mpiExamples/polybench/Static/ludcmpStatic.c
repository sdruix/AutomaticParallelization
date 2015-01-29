#include <string.h>
#include <math.h>


/* Default problem size. */
#ifndef N
# define N 4000
#endif


double w;
double a[N + 1][N + 1];
double x[N + 1];
double y[N + 1];
double b[N + 1];

static void init_array() {
    int i, j;
    
    for (i = 0; i <= N;) {
        x[i] = ((double)i + 1) / N;
        b[i] = ((double)i + 2) / N;
        for (j = 0; j <= N;) {
            a[i][j] = ((double)i * j + 1) / N;
            j++;
        }
        i++;
    }
}


int main(int argc, char** argv) {
    int i, j, k;
    int n = N;
    
    /* Initialize array. */
    init_array();
    
    
    
    b[0] = 1.0;
    
#pragma omp parallel for private (j, k, w) schedule(static) check
    for (i = 0; i < n; i++) {
        for (j = i + 1; j <= n; j++) {
            w = a[j][i];
            for (k = 0; k < i; k++)
                w = w - a[j][k] * a[k][i];
            a[j][i] = w / a[i][i];
        }
        for (j = i + 1; j <= n; j++) {
            w = a[i + 1][j];
            for (k = 0; k <= i; k++)
                w = w - a[i + 1][k] * a[k][j];
            a[i + 1][j] = w;
        }
    }
    y[0] = b[0];
#pragma omp parallel for private (j, w) schedule(static) check
    for (i = 1; i <= n; i++) {
        w = b[i];
        for (j = 0; j < i; j++)
            w = w - a[i][j] * y[j];
        y[i] = w;
    }
    x[n] = y[n] / a[n][n];
#pragma omp parallel for private (j, w) check
    for (i = 0; i <= n - 1; i++) {
        w = y[n - 1 - (i)];
        for (j = n - i; j <= n; j++)
            w = w - a[n - 1 - (i)][j] * x[j];
        x[n - 1 - (i)] = w / a[n - 1 - (i)][n - 1 - (i)];
    }
    
    double total = 0;
    for(int y=0; y<N; ++y){
        total+= x[y];
    }
    printf("Total: %f\n",total);
    
    return 0;
}

