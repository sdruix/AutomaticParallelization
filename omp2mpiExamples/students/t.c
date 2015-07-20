#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include <getopt.h>

#define MAXSTEP     1000
#define CX          0.001
#define CY          0.001
#define NX 6
#define NY 6

void setupBoundaryConditions (double X[NX][NY], unsigned long int sizex, unsigned long int sizey);
void initializeArray         (double X[NX][NY], unsigned long int sizex, unsigned long int sizey);

double*  makeDoubleArray   (unsigned long int size);
double** make2DDoubleArray (unsigned long int sizex, unsigned long int sizey);

void     save (double X[NX][NY], unsigned long int x, unsigned long int y, char* filename);
double   gettime(void);


 /*
  * Main
  */ 

double X1[NX][NY];
double X2[NX][NY];

int main(int argc, char* argv[]) {
    long int s, it;
    unsigned int flag, verbose;
    unsigned int NXPROB, NYPROB;
    double start, end;
    int iz;

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

    // Program starts here 

    // Set initial and boundary conditions 
    initializeArray (X1, NX, NY);
    setupBoundaryConditions(X1, NX, NY);
    setupBoundaryConditions(X2, NX, NY);


    // Main calculations
    iz = 0;
    for (it = 0; it < 1000; it++) { 
        unsigned long int _p_0_update_14 = NXPROB;
        unsigned long int _p_1_update_14 = NYPROB;
        double **_p_2_update_14 = X[iz];
        double **_p_3_update_14 = X[1 - iz];
        
        long int i, j;
#pragma omp parallel for private(j) check
        for (i = 1;i < _p_0_update_14; i++) {
            for (j = 1; j < _p_1_update_14; j++) {
                _p_3_update_14[i][j] = _p_2_update_14[i][j] + 0.001 * (_p_2_update_14[i + 1][j] + _p_2_update_14[i - 1][j] - 2.0 * _p_2_update_14[i][j]) + 0.001 * (_p_2_update_14[i][j + 1] + _p_2_update_14[i][j - 1] - 2.0 * _p_2_update_14[i][j]);
            }
        }
        
        iz = 1 - iz;
    }

    // Save output file
    if(flag) save(X2, NX, NY, file);

    // End time
    end = gettime();
    
    // Get information: wall clock time, problem size, ... 
    if(verbose)
    {
        fprintf(stdout, "[INFO] Convergence after %d steps\n", MAXSTEP);
        fprintf(stdout, "[INFO] Problem size %d [%dx%d]\n", NY*NX, NX, NY);
        fprintf(stdout, "[INFO] Wall clock time %lf seconds\n",(end-start));
        if(flag) fprintf(stdout, "[INFO] Output file  %s\n", file);
    } 
    else 
    {
        printf("Time %.3f seconds, Size %d [%dx%d]\n", end - start, NY*NX, NX, NY);
    }

    exit(EXIT_SUCCESS);
}

void setupBoundaryConditions(double X[NX][NY], unsigned long int x, unsigned long int y) {
    /* set boundary conditions for ix, jy = 0 and ix, jy = n-1 */
    unsigned long int ix, jy, i, j;
    double leftBC = 0, 
        rightBC = 0, 
        topBC = 0, 
        bottomBC = 0;

    /* setup the bottom and top BCs, jy = 0 and jy = n-1 or arraySizeY - 1 */
    for (i = 0; i < x; i++)
    {
        X[i][0] = bottomBC; //bottom BC
        X[i][y-1] = topBC;  //top BC
    }   

    /* setup the left and right BCs, ix = 0 and ix = arraySizeX - 1 */
    for (j = 0; j < y; j++) 
    {
        X[0][j]   = leftBC;   //left BC
        X[x-1][j] = rightBC;  //right BC
    }

    /* set the values at the corner nodes as averages of both sides*/
    // bottom left
    X[0][0]     = 0.5 * (leftBC + bottomBC);
    // top left
    X[0][y-1]   = 0.5 * (topBC + leftBC);
    // top right
    X[x-1][y-1] = 0.5 * (topBC + rightBC);
    // bottom right
    X[x-1][0]   = 0.5 * (bottomBC + rightBC);
}


void initializeArray(double X[NX][NY], unsigned long int x, unsigned long int y) {
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
        X[i][0] = 0;    //bottom BC
        X[i][y-1] = 0;  //top BC
    }
    for (j = 1; j < y; j++)
    { 
        X[0][j]   = 0;  //left BC
        X[x-1][j] = 0;  //right BC
    }
}


void save(double X[NX][NY], unsigned long int x, unsigned long int y, char* filename) {
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

/* Timing function */
double gettime(void) {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec + 1e-6*tv.tv_usec;
}