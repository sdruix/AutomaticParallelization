#include <string.h>
#include <math.h>

/* Default problem size. */
#ifndef Y
# define Y 4000
#endif


double A[Y][Y];
double x1[Y];
double y_1[Y];
double x2[Y];
double y_2[Y];

static void init_array() {
    int i, j;
    
    for (i = 0; i < Y;) {
        x1[i] = ((double)i) / Y;
        x2[i] = ((double)i + 1) / Y;
        y_1[i] = ((double)i + 3) / Y;
        y_2[i] = ((double)i + 4) / Y;
        for (j = 0; j < Y;) {
            A[i][j] = ((double)i * j) / Y;
            j++;
        }
        i++;
    }
}


int main(int argc, char** argv) {
    int i, j;
    int n = Y;
    
    /* Initialize array. */
    init_array();
    
    
#pragma omp parallel for private (j) schedule(static) check
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            x1[i] = x1[i] + A[i][j] * y_1[j];
#pragma omp parallel for private (j) schedule(static) check
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            x2[i] = x2[i] + A[j][i] * y_2[j];
    
    double total = 0;
    for(int y=0; y<n; ++y){
        total+= x2[y];
    }
    printf("Total: %f\n",total);
    
    
    
    
    return 0;
}
