#include <string.h>
#include <math.h>


/* Default problem size. */
#ifndef TMAX
# define TMAX 2048
#endif
#ifndef NX
# define NX 4096
#endif
#ifndef NY
# define NY 4096
#endif


/* Array declaration. Enable malloc if POLYBENCH_TEST_MALLOC. */
double _fict_[TMAX];
double ex[NX][NY];
double ey[NX][NY];
double hz[NX][NY];

static void init_array() {
  int i, j;

  for (i = 0; i < TMAX;) {
    _fict_[i] = (double)i;
    i++;
  }
  for (i = 0; i < NX;) {
    for (j = 0; j < NY;) {
      ex[i][j] = ((double)i * (j + 1) + 1) / NX;
      ey[i][j] = ((double)(i - 1) * j + 2) / NX;
      hz[i][j] = ((double)(i - 9) * (j + 4) + 3) / NX;
      j++;
    }

    i++;
  }
}


int main(int argc, char** argv) {
  int t, i, j;
  int tmax = TMAX;
  int nx = NX;
  int ny = NY;

  /* Initialize array. */
  init_array();



  for (t = 0; t < tmax; t++) {
    for (j = 0; j < ny; j++)
      ey[0][j] = _fict_[t];
    #pragma omp parallel for private (j) check
    for (i = 1; i < nx; i++)
      for (j = 0; j < ny; j++)
        ey[i][j] = ey[i][j] - 0.5 * (hz[i][j] - hz[i - 1][j]);
    #pragma omp parallel for private (j) check
    for (i = 0; i < nx; i++)
      for (j = 1; j < ny; j++)
        ex[i][j] = ex[i][j] - 0.5 * (hz[i][j] - hz[i][j - 1]);
    #pragma omp parallel for private (j) check
    for (i = 0; i < nx - 1; i++)
      for (j = 0; j < ny - 1; j++)
        hz[i][j] = hz[i][j] - 0.7 * (ex[i][j + 1] - ex[i][j] + ey[i + 1][j]
            - ey[i][j]);
  }

double total = 0;
  for (int iter = 0; iter < nx -1; iter++) {
      for (int iter2 = 0; iter2 < ny - 1; iter2++) {
            total+=hz[iter][iter2];
        }
      }
 printf("total=%f\n",total);


  return 0;
}
