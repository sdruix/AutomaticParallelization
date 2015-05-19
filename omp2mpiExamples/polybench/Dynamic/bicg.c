#include <string.h>
#include <math.h>


/* Default problem size. */
#ifndef NX
# define NX 4096
#endif
#ifndef NY
# define NY 4096
#endif
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif


double A[NX][NY];
double r[NX];
double s[NX];
double p[NX];
double q[NX];

static void init_array() {
  int i, j;

  for (i = 0; i < NX;i++) {
    r[i] = i * M_PI;
    p[i] = i * M_PI;
    for (j = 0; j < NY;j++) {
      A[i][j] = ((double)i * j) / NX;
    }
  }
}


int main(int argc, char** argv) {
  int i, j;
  int nx = NX;
  int ny = NY;

  /* Initialize array. */
  init_array();

  #pragma omp parallel for check
  for (i = 0; i < ny; i++)
    s[i] = 0;
  #pragma omp parallel for private (j) check
  for (i = 0; i < nx; i++) {
    q[i] = 0;
    for (j = 0; j < ny; j++) {
      s[j] = s[j] + r[i] * A[i][j];
      q[i] = q[i] + A[i][j] * p[j];
    }
  }

double total = 0;
  for (int iter = 0; iter < nx; iter++) {
            total+=q[iter];
        }
  
 printf("total=%f\n",total);



  return 0;
}
