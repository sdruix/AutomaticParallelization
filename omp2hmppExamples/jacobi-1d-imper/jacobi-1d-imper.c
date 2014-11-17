#include <string.h>
#include <math.h>

/* Default problem size. */
#ifndef TSTEPS
# define TSTEPS 1000
#endif
#ifndef Y
# define Y 1000000
#endif


double A[Y];
double B[Y];

static void init_array() {
  int i, j;

  for (i = 0; i < Y;) {
    A[i] = ((double)4 * i + 10) / Y;
    B[i] = ((double)7 * i + 11) / Y;
    i++;
  }
}


int main(int argc, char** argv) {
  int t, i, j;
  int tsteps = TSTEPS;
  int n = Y;

  /* Initialize array. */
  init_array();


#pragma omp parallel fixed(9,1,0)
{
  for (t = 0; t < tsteps; t++) {
    #pragma omp for
    for (i = 2; i < n - 1; i++)
      B[i] = 0.33333 * (A[i - 1] + A[i] + A[i + 1]);
    #pragma omp for
    for (j = 2; j < n - 1; j++)
      A[j] = B[j];
  }
}




  return 0;
}
