#include <string.h>
#include <math.h>



/* Default problem size. */
#ifndef N
# define N 8192
#endif

/* Array declaration. Enable malloc if POLYBENCH_TEST_MALLOC. */
double A[N][N];
double x[N];
double c[N];

static void init_array() {
  int i, j;

  for (i = 0; i < N;) {
    c[i] = ((double)i) / (double)N;
    for (j = 0; j < N;) {
      A[i][j] = ((double)i * j) / N;
      j++;
    }
    i++;
  }
}


int main(int argc, char** argv) {
  int i, j;
  int n = N;

  /* Initialize array. */
  init_array();


#pragma omp parallel for private (j) check
  for (i = 0; i < n; i++) {
    x[i] = c[i];
    for (j = 0; j <= i - 1; j++)
      x[i] = x[i] - A[i][j] * x[j];
    x[i] = x[i] / A[i][i];
  }
double total = 0;
  for (int iter = 0; iter < n; iter++) {
            total+=x[iter];       
  }
  
 printf("total=%f\n",total);

  return 0;
}
