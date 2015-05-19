#include <string.h>
#include <math.h>

/* Default problem size. */
#ifndef X
# define X 2048
#endif
#ifndef Y
# define Y 2048
#endif
#ifndef T
# define T 2048
#endif

double tot[4];
double Gauss[4];
double g_tmp_image[Y][X];
double g_acc1[Y][X][4];
double g_acc2[Y][X][4];
double in_image[Y][X]; //input
double gauss_image[Y][X]; //output

static void init_array() {
  int i, j;

  for (i = 0; i < Y;) {
    for (j = 0; j < X;) {
      in_image[i][j] = ((double)i * j) / X;
      j++;
    }
    i++;
  }
  for (i = 0; i < 4;) {
    Gauss[i] = i;
    i++;
  }
}


int main(int argc, char** argv) {
  int x, y, k;
  int t = T;
  int m = X;
  int n = Y;

  /* Initialize array. */
  init_array();

  tot[0] = 0;
  
#pragma omp parallel for check
  for (k = t - 1; k <= 1 + t; k++)
    tot[k + 2 - t] = tot[k + 1 - t] + Gauss[k - t + 1];
#pragma omp parallel for check
  for (k = t - 1; k <= 1 + t; k++)
    tot[k + 2 - t] = tot[k + 1 - t] + Gauss[k - t + 1];
#pragma omp parallel for private(y,k) check
  for (x = 1; x < n - 2; x++) {
    for (y = 0; y < m; y++) {
      g_acc1[x][y][0] = 0;
      for (k = t - 1; k <= 1 + t; k++)
        g_acc1[x][y][k + 2 - t] = g_acc1[x][y][k + 1 - t]
            + in_image[x + k - t][y] * Gauss[k - t + 1];
      g_tmp_image[x][y] = g_acc1[x][y][3] / tot[3];
    }
  }
#pragma omp parallel for private(y,k) check
  for (x = 1; x < n - 1; x++) {
    for (y = 1; y < m - 1; y++) {
      g_acc2[x][y][0] = 0;
      for (k = t - 1; k <= 1 + t; k++)
        g_acc2[x][y][k + 2 - t] = g_acc2[x][y][k + 1 - t] + g_tmp_image[x][y
            + k - t] * Gauss[k - t + 1];
      gauss_image[x][y] = g_acc2[x][y][3] / tot[3];
    }
  }


  double total = 0;
  for (int iter = 1; iter < n - 1; iter++) {
      for (int iter2 = 1; iter2 < m - 1; iter2++) {
            total+=gauss_image[iter][iter2];       
        }
  }
  
 printf("total=%d\n",total);


  return 0;
}
