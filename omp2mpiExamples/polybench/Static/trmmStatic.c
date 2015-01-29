#include <string.h>
#include <math.h>


/* Default problem size. */
#ifndef N
# define N 4000
#endif


/* Array declaration. Enable malloc if POLYBENCH_TEST_MALLOC. */
double alpha;
double A[N][N];
double B[N][N];

static void init_array() {
  int i, j;

  alpha = 12435;
  for (i = 0; i < N;) {
    for (j = 0; j < N;) {
      A[i][j] = ((double)i * j) / N;
      B[i][j] = ((double)i * j + 1) / N;
      j++;
    }
    i++;
  }
}


int main(int argc, char** argv) {
  int i, j, k;
  int n = N;

  /* Initialize array. */
  init_array();

#pragma omp parallel for private (j, k) schedule(static) check
  for (i = 1; i < n; i++)
    for (j = 0; j < n; j++)
      for (k = 0; k < i; k++)
        B[i][j] += alpha * A[i][k] * B[j][k];

double total = 0;
    for(int y=0; y<N; ++y){
        for(int x=0; x<N; ++x) {
            total+= A[y][x];
        }
    }
    printf("Total: %f\n",total);

  return 0;
}

