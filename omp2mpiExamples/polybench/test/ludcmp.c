#include <string.h>
#include <math.h>
#include <sys/time.h>

/* Default problem size. */
#ifndef N
# define N 10
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
struct timeval start, end;
    long mtime, seconds, useconds;    
    gettimeofday(&start, NULL);    

    for (i = 0; i < n; i++) {
        //#pragma omp parallel for private (k, w) check
        for (j = i + 1; j <= n; j++) {
            w = a[j][i];
            for (k = 0; k < i; k++)
                w = w - a[j][k] * a[k][i];
            a[j][i] = w / a[i][i];
        }
        //#pragma omp parallel for private (k, w) check
        for (j = i + 1; j <= n; j++) {
            w = a[i + 1][j];
            for (k = 0; k <= i; k++)
                w = w - a[i + 1][k] * a[k][j];
            a[i + 1][j] = w;
        }
    }
    y[0] = b[0];

    for (i = 1; i <= n; i++) {
        w = b[i];
        #pragma omp parallel for reduction (-:w) check
        for (j = 0; j < i; j++)
            w -= a[i][j] * y[j];
        y[i] = w;
    }
    x[n] = y[n] / a[n][n];
    for (i = 0; i <= n - 1; i++) {
        w = y[n - 1 - i];
        //#pragma omp parallel for reduction (-:w) check
        for (j = n - i; j <= n; j++) 
            w = w - a[n - 1 - i][j] * x[j];
        
        
        x[n - 1 - i] = w / a[n - 1 - i][n - 1 - i];
    }
gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Elapsed time: %ld milliseconds\n", mtime);    
    double total = 0;
//    for(int l=0; l<N; ++l){
//        total+= x[l];
//    }
    
    
    return 0;
}

