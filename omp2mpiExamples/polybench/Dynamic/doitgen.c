#include <string.h>
#include <math.h>
#include <sys/time.h>
/* Default problem size. */
#ifndef NR
# define NR 500//500
#endif
#ifndef NQ
# define NQ 500//500
#endif
#ifndef NP
# define NP 500//500
#endif

double A[NR][NQ][NP];
double sum[NR][NQ][NP];
double C4[NP][NP];

static void init_array() {
  int i, j, k;

  for (i = 0; i < NR;) {
    for (j = 0; j < NQ;) {
      for (k = 0; k < NP;) {
        A[i][j][k] = ((double)i * j + k) / NP;
        k++;
      }
      j++;
    }
    i++;
  }
  for (i = 0; i < NP; i++) {
    for (j = 0; j < NP; j++) {
      C4[i][j] = ((double)i * j) / NP;
      j++;
    }
    i++;
  }
}


int main(int argc, char** argv) {
  int r, q, p, s;
  int nr = NR;
  int nq = NQ;
  int np = NP;

  /* Initialize array. */
  init_array();
  struct timeval start, end;
    long mtime, seconds, useconds;    
    gettimeofday(&start, NULL);
  #pragma omp parallel for private (q, p, s) check
  for (r = 0; r < nr; r++)
    for (q = 0; q < nq; q++) {
      for (p = 0; p < np; p++) {
        sum[r][q][p] = 0;
        for (s = 0; s < np; s++)
          sum[r][q][p] = sum[r][q][p] + A[r][q][s] * C4[s][p];
      }
      for (p = 0; p < np; p++)
        A[r][q][p] = sum[r][q][p];
    }
    gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Elapsed time: %ld milliseconds\n", mtime);
  double total = 0;
  for(int x=0; x<nr; ++x){
      for(int y=0; y<nq; ++y) {
          for(int z=0; z<np; ++z) {
            total+= A[x][y][z];
          }
      }
  }
  printf("Total: %f\n",total);


  return 0;
}

