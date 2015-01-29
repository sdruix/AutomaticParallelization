#include <string.h>
#include <math.h>
#include <sys/time.h>

/* Default problem size. */
#ifndef _PB_NI
# define _PB_NI 8192
#endif
#ifndef _PB_NJ
# define _PB_NJ 8192
#endif


double A[_PB_NI][_PB_NJ];
double B[_PB_NI][_PB_NJ];

static void init_array(ni,nj) {
  int i, j;

  for (i = 0; i < ni; i++)
    for (j = 0; j < nj; j++)
      {
	A[i][j] = ((double) (i + j) / nj);
      }
}


int main(int argc, char** argv) {
  int i, j;
  int ni=_PB_NI, nj= _PB_NJ;
  /* Initialize array. */
  init_array(ni,nj);
struct timeval start, end;
    long mtime, seconds, useconds;    
    gettimeofday(&start, NULL);
  #pragma omp parallel for private (j) check
  for (i = 1; i < _PB_NI - 1; ++i)
    for (j = 1; j < _PB_NJ - 1; ++j)
      {
	B[i][j]
	  =  0.2 * A[i-1][j-1] + 0.5 * A[i-1][j] + -0.8 * A[i-1][j+1]
	  + -0.3 * A[ i ][j-1] + 0.6 * A[ i ][j] + -0.9 * A[ i ][j+1]
	  +  0.4 * A[i+1][j-1] + 0.7 * A[i+1][j] +  0.1 * A[i+1][j+1];
      }
gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Elapsed time: %ld milliseconds\n", mtime);
 double total = 0;
  for(int y=0; y<_PB_NI; ++y){
      for(int x=0; x<_PB_NJ; ++x) {
          total+= B[y][x];
      }
  }
  printf("Total: %f\n",total);

  return 0;
}
