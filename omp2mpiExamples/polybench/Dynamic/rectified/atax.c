#include <string.h>
#include <math.h>


/* Default problem size. */
#ifndef NX
# define NX 10
#endif
#ifndef NY
# define NY 10
#endif


double A[NX][NY];
double x[NY];
double y[NY];
double tmp[NX];

static void init_array() {
  int i, j;

  for (i = 0; i < NX;) {
    x[i] = i * 3.14159265358979323846;
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


  for (i = 0; i < nx; i++)
    y[i] = 0;
  
  for (i = 0; i < ny; i++) {
    tmp[i] = 0;
    #pragma omp parallel for check
    for (j = 0; j < ny; j++)
      tmp[i] = tmp[i] + A[i][j] * x[j];
    #pragma omp parallel for check
    for (j = 0; j < ny; j++)
      y[j] = y[j] + A[i][j] * tmp[i];
  }
  
   double total = 0;
    for(int x=0; x<ny; ++x){
            total+= y[x];
    }
    printf("Total: %f\n",total);
  return 0;
}
