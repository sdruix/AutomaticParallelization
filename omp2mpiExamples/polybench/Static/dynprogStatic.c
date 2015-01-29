#include <string.h>
#include <math.h>

/* Default problem size. */
#ifndef TSTEPS
# define TSTEPS 1000
#endif
#ifndef LENGTH
# define LENGTH 100
#endif

double out;
double sum_c[LENGTH][LENGTH][LENGTH];
double c[LENGTH][LENGTH];
double W[LENGTH][LENGTH]; //input

static inline
void init_array() {
    int i, j;
    
    for (i = 0; i < LENGTH; ) {
        for (j = 0; j < LENGTH; ) {
            W[i][j] = ((double)i * j + 1) / LENGTH;
            j++;
        }
        i++;
    }
}


int main(int argc, char** argv) {
    int iter, i, j, k;
    int length = LENGTH;
    int tsteps = TSTEPS;
    
    /* Initialize array. */
    init_array();
    
    
    out = 0;
    
#pragma omp parallel for private (j) schedule(static) check
    for (iter = 0; iter < tsteps; iter++) {
        for (i = 0; i <= length - 1; i++)
            for (j = 0; j <= length - 1; j++)
                c[i][j] = 0;
#pragma omp parallel for private (j, k) schedule(static) check
        for (i = 0; i <= length - 2; i++) {
            for (j = i + 1; j <= length - 1; j++) {
                sum_c[i][j][i] = 0;
                for (k = i + 1; k <= j - 1; k++)
                    sum_c[i][j][k] = sum_c[i][j][k - 1] + c[i][k] + c[k][j];
                c[i][j] = sum_c[i][j][j - 1] + W[i][j];
            }
        }
        out += c[0][length - 1];
    }
    
    double total = 0;
    for(int y=0; y<LENGTH; ++y){
        for(int x=0; x<LENGTH; ++x) {
            total+= c[y][x];
        }
    }
    printf("Total: %f\n",total);
    
    
    return 0;
}
