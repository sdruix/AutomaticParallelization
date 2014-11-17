#include <string.h>
#include <math.h>



/* Default problem size. */
#ifndef Y
# define Y 4000
#endif

/* Array declaration. Enable malloc if POLYBENCH_TEST_MALLOC. */
double A[Y][Y];

static void init_array() {
  int i, j;

  for (i = 0; i < Y;) {
    for (j = 0; j < Y;) {
      A[i][j] = ((double)i * j + 1) / Y;
      j++;
    }
    i++;
  }
}


int main(int argc, char** argv) {
  int i, j, k;
  int n = Y;

  /* Initialize array. */
  init_array();

#pragma omp parallel fixed(9,1,0)
{
  #pragma omp for private (j, i)
  for (k = 0; k < n; k++) {
    for (j = k + 1; j < n; j++)
      A[k][j] = A[k][j] / A[k][k];
    for (i = k + 1; i < n; i++)
      for (j = k + 1; j < n; j++)
        A[i][j] = A[i][j] - A[i][k] * A[k][j];
  }

}
  return 0;
}
