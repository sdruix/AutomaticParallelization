#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include <getopt.h>
#include "mpi.h"

#define MAXSTEP     1000
#define CX          0.001
#define CY          0.001


void setupBoundaryConditions (double** X, unsigned long int sizex, unsigned long int sizey);
void initializeArray         (double** X, unsigned long int x, unsigned long int NX, unsigned long int y, unsigned int offset, unsigned int rank, unsigned int np);

double*  makeDoubleArray   (unsigned long int size);
double** make2DDoubleArray (unsigned long int sizex, unsigned long int sizey);
void     free2DDoubleArray (double **X, unsigned long int size);
void     save (double** X, unsigned long int x, unsigned long int y, char* filename);
double   gettime(void);
void     printTable(double **X, unsigned int x, unsigned int y, unsigned int rank, unsigned int offset);

enum MPI_TYPE  { MASTER = 0, WORKER};

/*
 *  subroutine update
 */
void update(unsigned long int NXPROB, unsigned long int NYPROB, double **X1, double **X2) {
	long int i, j;

	for (i=1; i < NXPROB; i++)
	{
		for (j = 1; j < NYPROB; j++)
		{
			X2[i][j] = X1[i][j]
				+ CX * ( X1[i+1][j] + X1[i-1][j] - 2.0 * X1[i][j] )
				+ CY * ( X1[i][j+1] + X1[i][j-1] - 2.0 * X1[i][j] );
		}
	}
}

void updateNonBlocking(unsigned long int initNX, unsigned long int endNX, unsigned long int NYPROB, double **X1, double **X2, unsigned int rank, unsigned int np, long int it, MPI_Request sendRequest[], MPI_Request recvRequest[]) {
	
	long int i, j;
	

	//No bloquejant: primer es processaran totes les files que no depenguin de processos veïns. 
	//Es deixen pel final les files que requereixin d'un receive.

	//--== Files sense dependències ==--
	for (i = initNX; i < endNX; i++)
		for (j = 1; j < NYPROB; j++)
			X2[i][j] = X1[i][j]
				+ CX * ( X1[i+1][j] + X1[i-1][j] - 2.0 * X1[i][j] )
				+ CY * ( X1[i][j+1] + X1[i][j-1] - 2.0 * X1[i][j] );


	//--== Files amb dependències ==--
	//Esperem a rebre la fila del procés inferior/superior (depenent del procés)
	MPI_Wait(&recvRequest[0], MPI_STATUS_IGNORE);
	//Esperem a que s'hagi enviat el missatge correctament abans de sobreescriure les dades
	MPI_Wait(&sendRequest[0], MPI_STATUS_IGNORE);

	if (rank==MASTER){
		//El procés 0 només ha de rebre l'última fila i processar la penúltima
		i = endNX;
		for (j = 1; j < NYPROB; j++)
			X2[i][j] = X1[i][j]
					+ CX * ( X1[i+1][j] + X1[i-1][j] - 2.0 * X1[i][j] )
					+ CY * ( X1[i][j+1] + X1[i][j-1] - 2.0 * X1[i][j] );

	}else if (rank==np-1){
		//L'últim procés només ha de rebre la primera fila i processar la segona fila
		i = initNX-1; //O també i = 1;
		for (j = 1; j < NYPROB; j++)
			X2[i][j] = X1[i][j]
					+ CX * ( X1[i+1][j] + X1[i-1][j] - 2.0 * X1[i][j] )
					+ CY * ( X1[i][j+1] + X1[i][j-1] - 2.0 * X1[i][j] );
	}else{
		//Un procés del mig ha de rebre la 1a i última fila, i processar la segona i penúltima fila
		i = initNX-1; //O també i = 1;
		for (j = 1; j < NYPROB; j++)
			X2[i][j] = X1[i][j]
					+ CX * ( X1[i+1][j] + X1[i-1][j] - 2.0 * X1[i][j] )
					+ CY * ( X1[i][j+1] + X1[i][j-1] - 2.0 * X1[i][j] );

		//Esperem per l'enviament i resposta del procés veï inferior
		MPI_Wait(&recvRequest[1], MPI_STATUS_IGNORE);
		MPI_Wait(&sendRequest[1], MPI_STATUS_IGNORE);
		i = endNX;
		for (j = 1; j < NYPROB; j++)
			X2[i][j] = X1[i][j]
					+ CX * ( X1[i+1][j] + X1[i-1][j] - 2.0 * X1[i][j] )
					+ CY * ( X1[i][j+1] + X1[i][j-1] - 2.0 * X1[i][j] );
	}
}

void realitzarComunicacio(unsigned int rank, unsigned int np, double **X, unsigned long int pNX, unsigned long int NY, long int it, MPI_Request sendRequest[], MPI_Request recvRequest[]){
	

	// NOTA: El TAG es la iteracio, assegurant-nos de que rebem cada iteració i no ens saltem cap

	if (rank==MASTER){
		// Enviem la penultima fila
		MPI_Isend(&X[pNX-2][1], NY-2, MPI_DOUBLE, 1, it, MPI_COMM_WORLD, &sendRequest[0]);
		// Rebem l'ultima fila
		MPI_Irecv(&X[pNX-1][1], NY-2, MPI_DOUBLE, 1, it, MPI_COMM_WORLD, &recvRequest[0]);
	} else if (rank==np-1){
		// Enviem la segona fila al anterior
		MPI_Isend(&X[1][1], NY-2, MPI_DOUBLE, np-2, it, MPI_COMM_WORLD, &sendRequest[0]);
		// Rebem la primera fila
		MPI_Irecv(&X[0][1], NY-2, MPI_DOUBLE, np-2, it, MPI_COMM_WORLD, &recvRequest[0]);
	} else {
		// Enviem la segona fila al anterior, la penultima al seguent
		MPI_Isend(&X[1][1], NY-2, MPI_DOUBLE, rank-1, it, MPI_COMM_WORLD, &sendRequest[0]);
		MPI_Isend(&X[pNX-2][1], NY-2, MPI_DOUBLE, rank+1, it, MPI_COMM_WORLD, &sendRequest[1]);
		// Rebem la primera i l'ultima fila
		MPI_Irecv(&X[0][1], NY-2, MPI_DOUBLE, rank-1, it, MPI_COMM_WORLD, &recvRequest[0]);
		MPI_Irecv(&X[pNX-1][1], NY-2, MPI_DOUBLE, rank+1, it, MPI_COMM_WORLD, &recvRequest[1]);
	}

}

void ajuntarMatriuFinal(unsigned int rank, unsigned int np, double **X, double **X2, unsigned long int NX, unsigned long int pNX, unsigned long int NY){

	int i,pNXmig,pNXfinal,numElemMig,numElemFinal,filaInici,midaEnviament;

	int recvcounts[np]; // numero d'elements que rep de cada proces
	int displs[np]; 	// desplaçament respecte el buffer inicial on ha de rebre cada resposta

	pNXmig = floor(NX/np); // Numero de files que te cada worker del mig, sense les extra
	pNXfinal = pNXmig+(NX-pNXmig*np); // Numero de files que te el worker final, sense les extra

	numElemMig = NY*pNXmig; // files*numElements
	numElemFinal = NY*pNXfinal; // files*numElements


	if (rank==MASTER){
		// Preparem les arrays amb info de recieve
		for (i = 0; i < np-1; i++){ // Cas MASTER i mig
			recvcounts[i] = numElemMig;
			displs[i] = i*numElemMig;
		}
		recvcounts[i] = numElemFinal; // Cas final (i és np-1)
		displs[i] = i*numElemMig;

		filaInici = 0;
		midaEnviament = numElemMig;
		
	} else if (rank==np-1) {
		filaInici = 1;
		midaEnviament = numElemFinal;
	} else {
		filaInici = 1;
		midaEnviament = numElemMig;
	}
	
	// MPI_Gatherv: La V final es de "varying", és a dir, permet agrupar dades de diferents mides.
	// https://www.open-mpi.org/doc/v1.8/man3/MPI_Gatherv.3.php
	// MPI_Gatherv(sendBuf, sendCount, sendtype, recvbuf, recvcounts[], displs[], recvtype, root, comm)
	// La gràcia esta en que cadascu envia lo seu, i en el master la part del recvcounts i displs és important, ja que indica
	// que rebrà de cada worker (inclos ell mateix) i a on ho colocarà.
	MPI_Gatherv(&X[filaInici][0], midaEnviament, MPI_DOUBLE, &X2[0][0], recvcounts, displs, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
}

 /*
  * Main
  */

int main(int argc, char* argv[]) {
	long int s, it;
	unsigned int flag, verbose;
	unsigned int NX, NY, pNX, initNX, endNX, NYPROB, offset, np, rank;
	double start, end;
	int iz;

	// Initialize the MPI environment
	MPI_Init(&argc, &argv);
	MPI_Request recvRequest[2], sendRequest[2]; //Control comunicació no bloquejant
	MPI_Comm    World = MPI_COMM_WORLD;
	// Get the number of processes
	MPI_Comm_size(World, &np); // number of procs
	if (np<3){
	  printf("Error: 3 or more processes are needed (%d used)\n", np);
	  MPI_Finalize();
	  exit(EXIT_FAILURE);
	}

	// Get the rank of the process
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); // my rank in [0..P).

	if (rank==MASTER)
	  fprintf(stdout, "[INFO] Processes created: %d.\n",np);

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
				  MPI_Finalize();
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
				MPI_Finalize();
				exit(EXIT_FAILURE);
		}
	}


	if (rank==MASTER){
		if(verbose) {
			fprintf(stdout, "[INFO] Setting map size to %d (%dx%d)\n", NX*NY, NX, NY);
			fprintf(stdout, "[INFO] Max iter %d\n", MAXSTEP);
		}
		if(verbose && flag) {
			fprintf(stdout, "[INFO] Using output file %s\n", file);
		}
	}

	// Program starts here
	start = gettime();

	// Memory allocation
	double** X[2];

	//Partició hortizontal de la matriu X en 'np' processos
	pNX = floor(NX/np);

	if (rank==MASTER || rank==np-1){
		//1r procés i últim: només s'agafa una fila de més (el 1r procés agafa
		//l'última fila de més, i l'últim procés agafa la primera fila de més)
		pNX += 1;

		if (rank == MASTER){
			//El master és l'únic que la seva fila no és compartida, per tant no té offset
			offset = 0;
		} else {
			//Si la divisió NY/np no és entera l'últim procés agafarà files de més
			//fins el final de la matriu X
			pNX += NX - (floor(NX/np)*np);
		}

	} else {
		//procés del mig: agafa dues files de més (1a i última)
		pNX += 2;
	}
	//Fi partició

	X[0] = make2DDoubleArray (pNX, NY);
	X[1] = make2DDoubleArray (pNX, NY);

  //Càlcul de l'offset dins de X segons l'id del procés
  /*L'offset t'indica a quin índex de la matriu X general (algorisme seqüencial)
  pertany la 1a fila de la matriu X partida de cada procés (algorisme MPI)
  D'aquesta forma podem inicialitzar la matriu tal com ho fem en seqüencial*/

	if (rank!=MASTER)
		//La 1a fila de tots els WORKERs es correspon realment a l'última fila del procés
		//anterior, per això restem una posició a l'offset.
		offset = floor(NX/np)*rank-1;

  //DEBUG
  //fprintf(stdout, "[WORKER %d] Offset: %d | pNX: %d.\n",rank,offset,pNX);

	// Set initial and boundary conditions
	initializeArray (X[0], pNX, NX, NY, offset, rank, np);
	initializeArray (X[1], pNX, NX, NY, offset, rank, np);

	// setupBoundaryConditions(X[0], NX, NY);
	// setupBoundaryConditions(X[1], NX, NY);


	// Inicialitzem aquestes variables aquí segons el tipus de procés per no haver-ho
	// de fer en totes les iteracions dins de l'updateNonBlocking
	NYPROB = NY - 1;
	//initNX i endNX indiquen el rang files a processar en la funció 'updateNonBlocking'
	//que no depenen d'altres processos (la fila endNX no inclosa)
	if (rank==MASTER){
		initNX = 1;
		endNX = pNX - 2;
	}
	else if (rank==np-1){
		initNX = 2;
		endNX = pNX - 1;
	}else{
		initNX = 2;
		endNX = pNX - 2;
	}
	//Amb això ens evitem que peti el programa en casos puntuals on pNX 
	//sigui tan petit que no hi hagi files sense dependències
	if (initNX>endNX) 
		endNX=initNX;
	

	// Main calculations
	iz = 0; it = 0;
	//A la 1a iteració no hi ha comunicació en l'update
	if(verbose) {
		fprintf(stdout, "[WORKER %d] iteration %ld, time %.3f seconds\n",rank, it, gettime()-start);
	}
	update(pNX-1, NYPROB, X[iz], X[1-iz]);
	iz = 1 - iz;

	//Resta d'iteracions (update no bloquejant)
	for (it = 1; it < MAXSTEP; it++)
	{
		// Actualitzem amb els valors dels nostres companys workers
		realitzarComunicacio(rank, np, X[iz], pNX, NY, it, sendRequest, recvRequest);

		if(verbose && (it%(MAXSTEP/10) == 0)) {
			fprintf(stdout, "[WORKER %d] iteration %ld, time %.3f seconds\n",rank, it, gettime()-start);
		}
		updateNonBlocking(initNX, endNX, NYPROB, X[iz], X[1-iz], rank, np, it, sendRequest, recvRequest);
		iz = 1 - iz;
	}

	// A X[iz] tenim les finals, però separades en els diferents workers. S'ha de tornar a ajuntar tot al master
	// Creem de nou X[1-iz] amb la mida original, i hi posem les dades del master. Seguidament demanem totes les altres dades

	// Preparem martiu de la mida original, només cal a la master
	X[1-iz] = make2DDoubleArray(NX, NY);

	// Reagrupem. X serà X[iz] (resultats parcials) i X2 X[1-iz], a on quedarà el resultat final reagrupat
	ajuntarMatriuFinal(rank, np, X[iz], X[1-iz], NX, pNX, NY);

	// Save output file
	if(flag && rank==MASTER) save(X[1-iz], NX, NY, file);

	free2DDoubleArray(X[iz], pNX);
	free2DDoubleArray(X[1-iz], NX);

	// End time
	end = gettime();

	// Get information: wall clock time, problem size, ...
	if (rank==MASTER){
		if(verbose){
			fprintf(stdout, "[INFO] Convergence after %d steps\n", MAXSTEP);
			fprintf(stdout, "[INFO] Problem size %d [%dx%d]\n", NY*NX, NX, NY);
			fprintf(stdout, "[INFO] Wall clock time %lf seconds\n",(end-start));
			if(flag) fprintf(stdout, "[INFO] Output file  %s\n", file);
		} else {
			printf("Time %.3f seconds, Size %d [%dx%d]\n", end - start, NY*NX, NX, NY);
		}
	}

	// Shut down MPI
	MPI_Finalize();

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


void initializeArray(double** X, unsigned long int x, unsigned long int originalX, unsigned long int y, unsigned int offset, unsigned int rank, unsigned int np) {
	unsigned long int i, j;

	if (rank==MASTER){
	  //La 1a fila del 1r procés s'inicialitza a 0
	  for (j = 1; j < y; j++)
		  X[0][j]   = 0;  //top BC
	  i = 1;
	}
	else
	  i = 0;

	for (; i < x; i++)
		for (j = 1; j < y-1; j++)
			X[i][j] = (double)MAXSTEP+((i+offset) * (originalX - (i+offset) - 1) * j * (y - j - 1));

	//Inicialitzem a 0 les columnes de la dreta i de l'esquerre (tots els processos)
	for (i = 0; i < x; i++){
			X[i][0] = 0;	//left BC
			X[i][y-1] = 0;	//right BC
	}

	//Inicialitzem a 0 l'última fila de l'últim procés
	if (rank==np-1)
	  for (j = 1; j < y; j++)
			X[x-1][j] = 0;  //bottom BC

	//DEBUG
	//if (rank==2)
	  //printTable(X, x, y, rank, offset);


}

void free2DDoubleArray(double **X, unsigned long int size) {
	// unsigned long int i;
	// for (i = 0; i < size; ++i) {
	// 	free(X[i]);
	// }
	// free(X);

	// Llibrerar segons s'ha creat (veure make2DDoubleArray)
	free(X[0]);
	free(X);
}

void printTable(double **X, unsigned int x, unsigned int y, unsigned int rank, unsigned int offset){
  int i, j;
  fprintf(stdout, "----Taula X del procés %d (x: %d, y: %d, off: %d):\n\t", rank, x, y, offset);
  for (i=0; i < x; i++){
	fprintf(stdout, "%d|\t", offset+i);
	for (j = 0; j < y; j++)
	  fprintf(stdout, "%.1f\t", X[i][j]);
	  fprintf(stdout, "\n\t");
	}
	fprintf(stdout, "\n");
}

double** make2DDoubleArray(unsigned long int x, unsigned long int y) {
	// double** X;
	// unsigned long int ix;
	// X = (double**) malloc(x*sizeof(double*));
	// for (ix= 0; ix < x; ix++) {
	// 	X[ix] =(double*) malloc(y*sizeof(double));
	// }
	// return X;

	// Nova forma de muntar l'array, que s'assegura de l'espai contigu en memoria
	// http://stackoverflow.com/questions/5901476/sending-and-receiving-2d-array-over-mpi

	int i;
	double* data = (double*)malloc(x*y*sizeof(double));
    double** array= (double**)malloc(x*sizeof(double*));
    for (i=0; i<x; i++)
        array[i] = &(data[y*i]);

    return array;
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

/* Timing function */
double gettime(void) {
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return tv.tv_sec + 1e-6*tv.tv_usec;
}
