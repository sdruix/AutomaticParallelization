#include <string.h>
#include <math.h>

/* Default problem size. */
#ifndef Y
# define Y 10
#endif
#ifndef X
# define X 10
#endif


double alpha;
double beta;
double acc;
double A[Y][Y];
double B[X][Y];
double C[X][Y];

static inline
void init_array() {
  int i, j;

  alpha = 12435;
  beta = 4546;
  for (i = 0; i < Y;) {
    for (j = 0; j < Y;) {
      A[i][j] = ((double)i * j) / Y;
      j++;
    }
    i++;
  }
  for (i = 0; i < X;) {
    for (j = 0; j < Y;) {
      B[i][j] = ((double)i * j + 1) / Y;
      C[i][j] = ((double)i * j + 2) / Y;
      j++;
      i++;
    }
  }
}

int main(int argc, char** argv) {
  int i, j, k;
  int n = Y;
  int m = X;

  /* Initialize array. */
  init_array();


  /*  C := alpha*A*B + beta*C, A is symetric */
  
  for (i = 0; i < m; i++) {
    #pragma omp parallel for private(k) check
    for (j = 0; j < n; j++) {
      acc = 0;
      for (k = 0; k < j - 1; k++) {
        C[k][j] += alpha * A[k][i] * B[i][j];
        acc += B[k][j] * A[k][i];
      }
      C[i][j] = beta * C[i][j] + alpha * A[i][i] * B[i][j] + alpha * acc;
    }
  }
  
  
  double total = 0;
    for(int x=0; x<m; ++x){
        for(int y=0; y<n; ++y) {
            total+= C[x][y];
        }
    }
    printf("Total: %f\n",total);


  return 0;
}
