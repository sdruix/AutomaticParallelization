#include <string.h>
#include <math.h>


/* Default problem size. */
#ifndef TSTEPS
# define TSTEPS 2
#endif
#ifndef Y
# define Y 10
#endif


double X[Y][Y];
double A[Y][Y];
double B[Y][Y];

void init_array() {
  int i, j;

  for (i = 0; i < Y; ) {
    for (j = 0; j < Y; ) {
      int r = rand();
      X[i][j] = ((double)i * (j + 1) + 1) / Y;
      A[i][j] = ((double)(i - 1) * (j + 4) + 2) / Y;
      B[i][j] = ((double)(i + 3) * (j + 7) + 3) / Y;
      j++;
    }
    i++;
  }
}


int main(int argc, char** argv) {
  int t, i1, i2;
  int n = Y;
  int tsteps = TSTEPS;

  /* Initialize array. */
  init_array();



    for (t = 0; t < tsteps; t++) {
      
      for (i1 = 0; i1 < n; i1++)
        #pragma omp analyze_access_pattern var(X) iter(i1) 
	for (i2 = 1; i2 < n; i2++) {
	  X[i1][i2] = X[i1][i2] - X[i1][i2 - 1] * A[i1][i2] / B[i1][i2 - 1];
	  B[i1][i2] = B[i1][i2] - A[i1][i2] * A[i1][i2] / B[i1][i2 - 1];
	}
      #pragma omp analyze_access_pattern var(X) iter(i1) 
      for (i1 = 0; i1 < n; i1++)
	X[i1][n - 1] = X[i1][n - 1] / B[i1][n - 1];
      #pragma omp analyze_access_pattern var(X) iter(i1) 
      for (i1 = 0; i1 < n; i1++)
	for (i2 = 0; i2 < n - 2; i2++)
	  X[i1][n - i2 - 2] = (X[i1][n - 2 - i2] - X[i1][n - 2 - i2 - 1]
	      * A[i1][n - i2 - 3]) / B[i1][n - 3 - i2];
//     #pragma omp analyze_access_pattern var(X,B) iter(i1) //
      for (i1 = 1; i1 < n; i1++)
	for (i2 = 0; i2 < n; i2++) {
	  X[i1][i2] = X[i1][i2] - X[i1 - 1][i2] * A[i1][i2] / B[i1 - 1][i2];
	  B[i1][i2] = B[i1][i2] - A[i1][i2] * A[i1][i2] / B[i1 - 1][i2];
	}
      #pragma omp analyze_access_pattern var(X) iter(i2) 
      for (i2 = 0; i2 < n; i2++)
	X[n - 1][i2] = X[n - 1][i2] / B[n - 1][i2];
//      #pragma omp analyze_access_pattern var(X) iter(i2) //
      for (i1 = 0; i1 < n - 2; i1++)
	for (i2 = 0; i2 < n; i2++)
	  X[n - 2 - i1][i2] = (X[n - 2 - i1][i2] - X[n - i1 - 3][i2] * A[n - 3
	      - i1][i2]) / B[n - 2 - i1][i2];
    }
  
  double total = 0;
  for (i1 = 0; i1 < n - 2; i1++) {
	for (i2 = 0; i2 < n; i2++) {
            total+=X[i1][i2];
        }
  }
  printf("total=%f\n",total);
  


  return 0;
}