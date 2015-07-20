#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include <getopt.h>

#define MAXSTEP     1000
#define CX          0.001
#define CY          0.001


void setupBoundaryConditions (double** X, unsigned long int sizex, unsigned long int sizey);
void initializeArray         (double** X, unsigned long int sizex, unsigned long int sizey);

double*  makeDoubleArray   (unsigned long int size);
double** make2DDoubleArray (unsigned long int sizex, unsigned long int sizey);
void     free2DDoubleArray (double **X, unsigned long int size);
void     save (double** X, unsigned long int x, unsigned long int y, char* filename);



/*
 *  subroutine update
 */
 void update(unsigned long int NXPROB, unsigned long int NYPROB, double **X1, double **X2) {
   long int i, j;

   for (i = 1; i < NXPROB; i++) 
   {
      	for (j = 1; j < NYPROB; j++) 
      	{
        	X2[i][j] = X1[i][j] 
         		+ CX * ( X1[i+1][j] + X1[i-1][j] - 2.0 * X1[i][j] )
				+ CY * ( X1[i][j+1] + X1[i][j-1] - 2.0 * X1[i][j] );
      	}
    }
 }

 /*
  * Main
  */ 

int main(int argc, char* argv[]) {
    long int s, it;
	unsigned int flag, verbose;
	unsigned int NX, NY, NXPROB, NYPROB;
	double start, end;
	int iz;
	
	// Defaut values
	NX = 100;
	NY = 100;

  	// create file and verbose flags 
  	flag = 0;
  	verbose = 0;

 	// Parse command line options 
  	int opt;
  	char *file = NULL;
  	while ((opt = getopt(argc, argv, "hvs:f:")) != -1) {
        switch (opt) {
        case 'v': 
			verbose = 1; 
			break;
        case 's': 
			if( !(s=atoi(optarg)) )  {
				fprintf(stderr, "Cannot parse %s value.\n", optarg);
           		exit(EXIT_FAILURE);
			}
			NX = NY = s; 
			break;
        case 'f': 
			file = optarg;
			flag = 1;
			break;
		case 'h':
        default:
            fprintf(stderr, "Usage: %s [-s SIZE] [-f output file]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }


	// Set initial data values	
	NXPROB = NX - 1;
	NYPROB = NY - 1;

	if(verbose) {
		fprintf(stdout, "[INFO] Setting map size to %d (%dx%d)\n", NX*NY, NX, NY);	
		fprintf(stdout, "[INFO] Max iter %d\n", MAXSTEP);
	}
	if(verbose && flag) {
		fprintf(stdout, "[INFO] Using output file %s\n", file);
	}


	// Memory allocation			
	double** X[2];
	X[0] = make2DDoubleArray (NX, NY);
	X[1] = make2DDoubleArray (NX, NY);

	// Set initial and boundary conditions 
	initializeArray (X[0], NX, NY);
	setupBoundaryConditions(X[0], NX, NY);
	setupBoundaryConditions(X[1], NX, NY);


	// Main calculations
	iz = 0;
	for (it = 0; it < MAXSTEP; it++) 
	{
  		update(NXPROB, NYPROB, X[iz], X[1-iz]);
  		iz = 1 - iz;
    }

	// Save output file
    if(flag) save(X[iz], NX, NY, file);

	free2DDoubleArray(X[0], NX);
	free2DDoubleArray(X[1], NX);

	// Get information: wall clock time, problem size, ... 
	if(verbose)
	{
		fprintf(stdout, "[INFO] Convergence after %d steps\n", MAXSTEP);
		fprintf(stdout, "[INFO] Problem size %d [%dx%d]\n", NY*NX, NX, NY);
		if(flag) fprintf(stdout, "[INFO] Output file  %s\n", file);
	} 
	

	exit(EXIT_SUCCESS);
}

void setupBoundaryConditions(double** X, unsigned long int x, unsigned long int y) {
	/* set boundary conditions for ix, jy = 0 and ix, jy = n-1 */
	unsigned long int ix, jy, i, j;
	double leftBC = 0, 
		rightBC = 0, 
		topBC = 0, 
		bottomBC = 0;

	/* setup the bottom and top BCs, jy = 0 and jy = n-1 or arraySizeY - 1 */
	for (i = 0; i < x; i++)
	{
		X[i][0] = bottomBC;	//bottom BC
		X[i][y-1] = topBC;	//top BC
	}	

	/* setup the left and right BCs, ix = 0 and ix = arraySizeX - 1 */
	for (j = 0; j < y; j++) 
	{
		X[0][j]   = leftBC;	  //left BC
		X[x-1][j] = rightBC;  //right BC
	}

	/* set the values at the corner nodes as averages of both sides*/
	// bottom left
	X[0][0] 	= 0.5 * (leftBC + bottomBC);
	// top left
	X[0][y-1]   = 0.5 * (topBC + leftBC);
	// top right
	X[x-1][y-1] = 0.5 * (topBC + rightBC);
	// bottom right
	X[x-1][0]   = 0.5 * (bottomBC + rightBC);
}


void initializeArray(double** X, unsigned long int x, unsigned long int y) {
   	unsigned long int i, j;

   	for (i = 1; i < x; i++) 
   	{
    	for (j = 1; j < y; j++)
    	{ 
        	X[i][j] = (double)MAXSTEP+(i * (x - i - 1) * j * (y - j - 1));
        }
 	}

   	for (i = 0; i < x; i++) 
   	{
		X[i][0] = 0;	//bottom BC
		X[i][y-1] = 0;	//top BC
   	}
    for (j = 1; j < y; j++)
    { 
		X[0][j]   = 0;  //left BC
		X[x-1][j] = 0;  //right BC
    }
}

void free2DDoubleArray(double **X, unsigned long int size) {
    unsigned long int i;
    for (i = 0; i < size; ++i) {
        free(X[i]);
    }
    free(X);
}

double** make2DDoubleArray(unsigned long int x, unsigned long int y) {
	double** X;
	unsigned long int ix;
	X = (double**) malloc(x*sizeof(double*));
	for (ix= 0; ix < x; ix++) {
		X[ix] =(double*) malloc(y*sizeof(double));
	}
	return X;
}

double* makeDoubleArray(unsigned long int arraySize) {
	double* theArray;
	theArray = (double*) malloc(arraySize*sizeof(double));
	return theArray;
}

void save(double** X, unsigned long int x, unsigned long int y, char* filename) {
  	unsigned long int i, j;
   	FILE* file;
	file = fopen(filename,"w");

	for (i = 0; i < x; i++) 
	{
		for (j = 0; j < y; j++)
		{
			fprintf(file,"%8.3f ", X[i][j]);
		}
		fprintf(file,"\n");
	}
    fclose(file);
}
