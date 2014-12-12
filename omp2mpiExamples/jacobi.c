#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <string.h>
#define MAXM 100
#define MAXN 100
#define SPANI 1
#define SPANJ 1
#define WORKSIZE (SPANI + MAXM + SPANI)
#define LINESIZE (SPANJ + MAXN + SPANJ)

double myTableOut[WORKSIZE][LINESIZE];
double myTable[WORKSIZE][LINESIZE];
void init(double table[WORKSIZE][LINESIZE], double tableOut[WORKSIZE][LINESIZE])
{
  memset(table, 0, WORKSIZE*LINESIZE*sizeof(double));
  memset(tableOut, 0, WORKSIZE*LINESIZE*sizeof(double));
}
void displayRegion(double table[WORKSIZE][LINESIZE])
{
  int i,j;
 
  double sum=0.;
  for (i=0; i < WORKSIZE; i++){
    for (j=0; j < LINESIZE; j++) {
      sum += table[i][j];
    }
  }
  
}


int main()
{
  
  int index =0;
  double theDiffNorm = 1;
  double RefDiffNorm = 0;
  int iterations = 2;
  int worksize=WORKSIZE, linesize=LINESIZE;
  int i,j,o,a;
  double diffsum,diff,diffmul;
  init( myTable,  myTableOut);
  for (index=0; (index < iterations); index++ )
    { 
  #pragma omp parallel for shared(myTableOut) private(i,j) check
    for (i=SPANI; i <  WORKSIZE - SPANI; i++) {
      for (j=SPANJ; j < LINESIZE - SPANJ; j++) {
	double neighbor =cos(myTable[i-SPANI][j]) +sin(myTable[i][j-SPANJ]) +sin(myTable[i][j+SPANJ]) +cos(myTable[i+SPANI][j]);
	myTableOut[i][j] = neighbor/3;
      }
    }
      theDiffNorm = 0.0;
      diffsum=theDiffNorm;
      a=0;
   #pragma omp parallel for reduction(+:diffsum) shared(myTable) private(i,j) check
      for (i = 1;i < (1 + MAXM + 1) - 1; i++)
	{
	    for (j = 1;j < (1 + MAXN + 1) - 1;j++)
	    {
		diff = myTableOut[i][j] - myTable[i][j];
		diffmul = diff * diff;
		diffsum += diffmul;
                a=2;
		myTable[i][j] = myTableOut[i][j];
	    }
	}
	theDiffNorm=diffsum;

    }
  displayRegion( myTable);
 printf("theDiffNorm:%.12g RefDiffNorm=%.12g;\n", theDiffNorm, RefDiffNorm);

  return 0;
}