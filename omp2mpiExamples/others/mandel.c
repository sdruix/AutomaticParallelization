#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int main ( void );
int i4_min ( int i1, int i2 );
void timestamp ( void );

/******************************************************************************/

int main ( void ) {
  int m = 2048;
  int n = 2048;

  int b[m][n];
  int c;
  int c_max;
  int count[m][n];
  int count_max = 2000;
  int g[m][n];
  int i;
  int ierror;
  int j;
  int jhi;
  int jlo;
  int k;
  char *output_filename = "mandelbrot.ppm";
  FILE *output_unit;
  int r[m][n];
  double x_max =   1.25;
  double x_min = - 2.25;
  double x;
  double x1;
  double x2;
  double y_max =   1.75;
  double y_min = - 1.75;
  double y;
  double y1;
  double y2;

/*
  Carry out the iteration for each pixel, determining COUNT.
*/

#pragma omp parallel for shared( b, count, count_max, g, r, x_max, x_min, y_max, y_min ) private( i, j, k, x, x1, x2, y, y1, y2 ) check
  for ( i = 0; i < m; i++ ){
    for ( j = 0; j < n; j++ ){
      x = ( ( double ) (     j - 1 ) * x_max + ( double ) ( m - j     ) * x_min )  / ( double ) ( m     - 1 );
      y = ( ( double ) (     i - 1 ) * y_max  + ( double ) ( n - i     ) * y_min ) / ( double ) ( n     - 1 );
      count[i][j] = 0;
      x1 = x;
      y1 = y;
      for ( k = 1; k <= count_max; k++ ) {
        x2 = x1 * x1 - y1 * y1 + x;
        y2 = 2 * x1 * y1 + y;
        if ( x2 < -2.0 || 2.0 < x2 || y2 < -2.0 || 2.0 < y2 ) {
          count[i][j] = k;
          break;
        }
        x1 = x2;
        y1 = y2;
      }
      if ( ( count[i][j] % 2 ) == 1 ) {
        r[i][j] = 255;
        g[i][j] = 255;
        b[i][j] = 255;
      } else {
        c = ( int ) ( 255.0 * sqrt ( sqrt ( sqrt (( ( double ) ( count[i][j] ) / ( double ) ( count_max ) ) ) ) ) );
        r[i][j] = 3 * c / 5;
        g[i][j] = 3 * c / 5;
        b[i][j] = c;
      }
    }
  }
/*
  Write data to an ASCII PPM file.
*/
  output_unit = fopen ( output_filename, "wt" );

  fprintf ( output_unit, "P3\n" );
  fprintf ( output_unit, "%d  %d\n", n, m );
  fprintf ( output_unit, "%d\n", 255 );
  for ( i = 0; i < m; i++ ) {
    for ( jlo = 0; jlo < n; jlo = jlo + 4 ) {
      jhi = i4_min ( jlo + 4, n );
      for ( j = jlo; j < jhi; j++ ) {
        fprintf ( output_unit, "  %d  %d  %d", r[i][j], g[i][j], b[i][j] );
      }
      fprintf ( output_unit, "\n" );
    }
  }

  fclose ( output_unit );

  return 0;
}
/******************************************************************************/

int i4_min ( int i1, int i2 ){
  int value;

  if ( i1 < i2 )
  {
    value = i1;
  }
  else
  {
    value = i2;
  }
  return value;
}
/******************************************************************************/

