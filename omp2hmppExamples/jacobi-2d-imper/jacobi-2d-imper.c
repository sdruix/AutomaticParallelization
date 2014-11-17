#include <string.h>
#include <math.h>

/* Default problem size. */
#ifndef TSTEPS
# define TSTEPS 100
#endif
#ifndef Y
# define Y 4000
#endif


/* Array declaration. Enable malloc if POLYBENCH_TEST_MALLOC. */
double A[Y][Y];
double B[Y][Y];

static void init_array() {
  int i, j;

  for (i = 0; i < Y;) {
    for (j = 0; j < Y;) {
      A[i][j] = ((double)i * (j + 2) + 10) / Y;
      B[i][j] = ((double)(i - 4) * (j - 1) + 11) / Y;
      j++;
    }
    i++;
  }

}


int main(int argc, char** argv) {
  int t, i, j;
  int tsteps = TSTEPS;
  int n = Y;

  /* Initialize array. */
  init_array();

#pragma omp parallel private(i,j) fixed(9,1,0)
{

  for (t = 0; t < tsteps; t++) {
    #pragma omp for
    for (i = 2; i < n - 1; i++)
      for (j = 2; j < n - 1; j++)
        B[i][j] = 0.2 * (A[i][j] + A[i][j - 1] + A[i][1 + j] + A[1 + i][j]
            + A[i - 1][j]);
    #pragma omp for
    for (i = 2; i < n - 1; i++)
      for (j = 2; j < n - 1; j++)
        A[i][j] = B[i][j];
  }

}



  return 0;
}
