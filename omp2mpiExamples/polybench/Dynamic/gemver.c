#include <string.h>
#include <math.h>


/* Default problem size. */
#ifndef Y
# define Y 8192
#endif


double alpha;
double beta;
double A[Y][Y];
double B[Y][Y];
double x[Y];
double u1[Y];
double u2[Y];
double v2[Y];
double v1[Y];
double w[Y];
double y[Y];
double z[Y];

static void init_array() {
  int i, j;

  alpha = 43532;
  beta = 12313;
  for (i = 0; i < Y;) {
    u1[i] = i;
    u2[i] = (i + 1) / Y / 2.0;
    v1[i] = (i + 1) / Y / 4.0;
    v2[i] = (i + 1) / Y / 6.0;
    y[i] = (i + 1) / Y / 8.0;
    z[i] = (i + 1) / Y / 9.0;
    x[i] = 0.0;
    w[i] = 0.0;
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
  

#pragma omp parallel for private (j) check
  for (i = 0; i < Y; i++)
    for (j = 0; j < Y; j++)
      A[i][j] = A[i][j] + u1[i] * v1[j] + u2[i] * v2[j];
#pragma omp parallel for private (j) check
  for (i = 0; i < Y; i++)
    for (j = 0; j < Y; j++)
      x[i] = x[i] + beta * A[j][i] * y[j]; 
#pragma omp parallel for check
  for (i = 0; i < Y; i++)
    x[i] = x[i] + z[i];
#pragma omp parallel for private (j) check
  for (i = 0; i < Y; i++)
    for (j = 0; j < Y; j++)
      w[i] = w[i] + alpha * A[i][j] * x[j];

 double total = 0;
  for (int iter = 0; iter < Y; iter++) {
    total+=w[iter];
  }
  
 printf("total=%f\n",total);


  return 0;
}
