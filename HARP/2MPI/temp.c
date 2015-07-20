#include <mpi.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
double alpha;
double beta;
double A[4096][4096];
double B[4096][4096];
double x[4096];
double y[4096];
double tmp[4096];
static void init_array()
{
    int i, j;
    alpha = 43532;
    beta = 12313;
    for (i = 0;
        i < 4096;
        )
    {
        x[i] = ((double) i) / 4096;
        for (j = 0;
            j < 4096;
            )
        {
            A[i][j] = ((double) i * j) / 4096;
            j++;
        }
        i++;
    }
}
int main(int argc, char **argv)
{
    int i, j;
    int n = 4096;
    init_array();
    struct timeval start, end;
    long mtime, seconds, useconds;
    gettimeofday(&start, ((void *) 0));
#pragma omp parallel for private(j) check
    for (i = 0;
        i < n;
        i++)
    {
        tmp[i] = 0;
        y[i] = 0;
        for (j = 0;
            j < n;
            j++)
        {
            tmp[i] = A[i][j] * x[j] + tmp[i];
            y[i] = B[i][j] * x[j] + y[i];
        }
        y[i] = alpha * tmp[i] + beta * y[i];
    }
    gettimeofday(&end, ((void *) 0));
    seconds = end.tv_sec - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    mtime = ((seconds) * 1000 + useconds / 1000.0) + 0.5;
    printf("Elapsed time: %ld milliseconds\n", mtime);
    double total = 0;
    for (int l = 0;
        l < n;
        ++l)
    {
        total += y[l];
    }
    printf("Total: %f\n", total);
    return 0;
}
