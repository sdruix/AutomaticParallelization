#include <string.h>
#include <math.h>
#include <sys/time.h>
/* Default problem size. */
#ifndef Y
# define Y 8192//4000//1000
#endif



double alpha;
double beta;
double A[Y][Y];
double B[Y][Y];
double x[Y];
double y[Y];
double tmp[Y];

static void init_array() {
  int i, j;

  alpha = 43532;
  beta = 12313;
  for (i = 0; i < Y; ) {
    x[i] = ((double)i) / Y;
    for (j = 0; j < Y; ) {
      A[i][j] = ((double)i * j) / Y;
      j++;
    }
    i++;
  }
}



int main(int argc, char** argv) {
  int i, j;
  int n = Y;

  /* Initialize array. */
  init_array();
struct timeval start, end;
    long mtime, seconds, useconds;    
    gettimeofday(&start, NULL);
 #pragma omp parallel for private (j) check
  for (i = 0; i < n; i++) {
    tmp[i] = 0;
    y[i] = 0;
    for (j = 0; j < n; j++) {
      tmp[i] = A[i][j] * x[j] + tmp[i];
      y[i] = B[i][j] * x[j] + y[i];
    }
    y[i] = alpha * tmp[i] + beta * y[i];
  }
gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Elapsed time: %ld milliseconds\n", mtime);
  double total = 0;
    for(int l=0; l<n; ++l) {
        total+= y[l];
    }

    printf("Total: %f\n",total);


  return 0;
}

