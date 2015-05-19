#include <string.h>
#include <math.h>


/* Default problem size. */
#ifndef X
# define X 10
#endif
#ifndef Y
# define Y 10
#endif

double nrm;
double A[X][Y];
double R[X][Y];
double Q[X][Y];

static void init_array() {
  int i, j;

  for (i = 0; i < X; ) {
    for (j = 0; j < Y; ) {
      A[i][j] = ((double)(i + 1) * (j + 1)) / X;
      j++;
    }
    i++;
  }
}



int main(int argc, char** argv) {
  int i, j, k;
  int m = X;
  int n = Y;

  /* Initialize array. */
  init_array();
#pragma omp parallel for private (i, j) check
  for (k = 0; k < n; k++) {
    nrm = 0;
    for (i = 0; i < m; i++)
      nrm += A[i][k] * A[i][k];
    R[k][k] = sqrt(nrm);
    for (i = 0; i < m; i++)
      Q[i][k] = A[i][k] / R[k][k];
    for (j = k + 1; j < n; j++) {
      R[k][j] = 0;
      for (i = 0; i < m; i++)
        R[k][j] += Q[i][k] * A[i][j];
      for (i = 0; i < m; i++)
        A[i][j] = A[i][j] - Q[i][k] * R[k][j];
    }
  }
  double total = 0;
  for (int iter = 0; iter < n; iter++) {
      for (int iter2 = 0; iter2 < m; iter2++) {
            total+=A[iter][iter2];       
        }
  }
  
 printf("total=%f\n",total);
  return 0;
}
