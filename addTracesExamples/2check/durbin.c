#include <string.h>
#include <math.h>


/* Default problem size. */
#ifndef N
# define N 10
#endif


double y[N][N];
double sum[N][N];
double beta[N];
double alpha[N];
double r[N]; //input
double out[N]; //output

static void init_array() {
  int i;

  for (i = 0; i < N;i++) {
    r[i] = i * 3.14159265358979323846;
  }
}



int main(int argc, char** argv) {
  int i, k;
  int n = N;


  init_array();
  
  y[0][0] = r[0];
  beta[0] = 1;
  alpha[0] = r[0];
  #pragma omp analyze_access_pattern var(alpha,beta,y,sum) iter(k,i) 
  for (k = 1; k < n; k++) {
    beta[k] = beta[k - 1] - alpha[k - 1] * alpha[k - 1] * beta[k - 1];
    sum[0][k] = r[k];
    for (i = 0; i <= k - 1; i++)
      sum[i + 1][k] = sum[i][k] + r[k - (i) - 1] * y[i][k - 1];
    alpha[k] = -sum[k][k] * beta[k];
    for (i = 0; i <= k - 1; i++)
      y[i][k] = y[i][k - 1] + alpha[k] * y[k - (i) - 1][k - 1];
    y[k][k] = alpha[k];
  }
  for (i = 0; i < n; i++)
    out[i] = y[i][N - 1];
 double total = 0;
    for(int x=0; x<n; ++x){
            total+= out[x];
    }
    printf("Total: %f\n",total);


  return 0;
}
