#include <string.h>
#include <math.h>


/* Default problem size. */
#ifndef NX
# define NX 8000
#endif
#ifndef NY
# define NY 8000
#endif
#ifndef M_PI
# define M_PI 5
#endif

double A[NX][NY];
double x[NY];
double y[NY];
double tmp[NX];

static void init_array() {
  int i, j;

  for (i = 0; i < NX;) {
    x[i] = i * M_PI;
    for (j = 0; j < NY;) {
      A[i][j] = ((double)i * j) / NX;
      j++;
    }
    i++;
  }
}



int main(int argc, char** argv) {
  int i, j;
  int nx = NX;
  int ny = NY;

  /* Initialize array. */
  init_array();

#pragma omp parallel schedule(static) check
{
  #pragma omp for
  for (i = 0; i < nx; i++)
    y[i] = 0;
  #pragma omp for private (j)
  for (i = 0; i < ny; i++) {
    tmp[i] = 0;
    for (j = 0; j < ny; j++)
      tmp[i] = tmp[i] + A[i][j] * x[j];
    for (j = 0; j < ny; j++)
      y[j] = y[j] + A[i][j] * tmp[i];
  }

}
double total = 0;
  for (i = 0; i < ny; i++) {
      total += y[i];
  }
  printf("%f\n",total);
  return 0;
}
