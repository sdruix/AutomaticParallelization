#include <string.h>
#include <math.h>
#include <sys/time.h>

/* Default problem size. */
#ifndef X
# define X 10
#endif
#ifndef Y
# define Y 10
#endif


/* Array declaration. Enable malloc if POLYBENCH_TEST_MALLOC. */
double float_n = 321414134.01;
double eps = 0.005;
double data[X + 1][Y + 1];
double symmat[X + 1][X + 1];
double stddev[X + 1];
double mean[X + 1];

static void init_array() {
  int i, j;

  for (i = 0; i <= X;) {
    for (j = 0; j <= Y;) {
      data[i][j] = ((double)i * j) / (X + 1);
      j++;
    }
    i++;
  }
}


int main(int argc, char** argv) {
  int i, j, j1, j2;
  int m = X;
  int n = Y;

  /* Initialize array. */
  init_array();
struct timeval start, end;
    long mtime, seconds, useconds;    
    gettimeofday(&start, NULL);

#define sqrt_of_array_cell(x,j) sqrt(x[j])
  #pragma omp parallel for private (i) check
  for (j = 1; j < m + 1; j++) {
    mean[j] = 0.0;
    for (i = 1; i <= n; i++)
      mean[j] += data[i][j];
    mean[j] /= float_n;
  }

  #pragma omp parallel for private (i) check
  for (j = 1; j < m + 1; j++) {
    stddev[j] = 0.0;
    for (i = 1; i <= n; i++)
      stddev[j] += (data[i][j] - mean[j]) * (data[i][j] - mean[j]);
    stddev[j] /= float_n;
    stddev[j] = sqrt_of_array_cell(stddev, j);
    /* The following in an inelegant but usual way to handle
     near-zero std. dev. values, which below would cause a zero-
     divide. */
    stddev[j] = stddev[j] <= eps ? 1.0 : stddev[j];
  }

  /* Center and reduce the column vectors. */
  #pragma omp parallel for private (j) check
  for (i = 1; i < n + 1; i++)
    for (j = 1; j <= m; j++) {
      data[i][j] -= mean[j];
      data[i][j] /= sqrt(float_n) * stddev[j];
    }

  /* Calculate the m * m correlation matrix. */
  #pragma omp parallel for private (j2, i) check
  for (j1 = 1; j1 < m ; j1++) {
    for (j2 = j1; j2 <= m; j2++) {
      symmat[j1][j2] = 0.0;
      for (i = 1; i <= n; i++)
        symmat[j1][j2] += (data[i][j1] * data[i][j2]);
      symmat[j2][j1] = symmat[j1][j2];
    }
  }
    gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Elapsed time: %ld milliseconds\n", mtime);
  symmat[m][m] = 1.0;
  double total = 0;
  for(int y=1; y<=m; ++y){
      for(int x=y; x<=m; ++x) {
          total+= symmat[x][y];
      }
  }
  printf("Total: %f\n",total);


  return 0;
}

