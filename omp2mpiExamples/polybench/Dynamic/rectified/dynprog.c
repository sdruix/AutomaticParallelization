#include <string.h>
#include <math.h>

/* Default problem size. */
#ifndef TSTEPS
# define TSTEPS 2
#endif
#ifndef LENGTH
# define LENGTH 4
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
  
  for (iter = 0; iter < tsteps; iter++) {
      
//    #pragma omp parallel for check
    for (i = 0; i <= length - 1; i++)
      for (j = 0; j <= length - 1; j++)
        c[i][j] = 0;
    
    for (i = 0; i <= length - 2; i++) {
      for (j = i + 1; j <= length - 1; j++) {
        sum_c[i][j][i] = 0;
        #pragma omp parallel for check
        for (k = i + 1; k <= j - 1; k++)
          sum_c[i][j][k] = sum_c[i][j][k - 1] + c[i][k] + c[k][j];
        c[i][j] = sum_c[i][j][j - 1] + W[i][j];
      }
    }
    out += c[0][length - 1];
  }



    printf("Total: %f\n",out);


  return 0;
}
