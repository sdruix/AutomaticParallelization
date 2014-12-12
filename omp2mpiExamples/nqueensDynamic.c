#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
#define MAX_N 16
int check_acceptable(int queen_rows[MAX_N], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = i+1; j < n; j++)
        {
            // two queens in the same row => not a solution!
            if (queen_rows[i] == queen_rows[j]) return 0;
            // two queens in the same diagonal => not a solution!
            if (queen_rows[i] - queen_rows[j] == i - j ||
                    queen_rows[i] - queen_rows[j] == j - i)
                return 0;
        }
    }
    return 1;
}
int main(int argc, char* argv[])
{
    int n;
    int max_iter = 1;
    int number_solutions = 0;
    
    int i;
    n = 8;
    
    for (i = 0; i < n; i++)
    {
        max_iter *= n;
    }
    
    int iter;
    int code;
    int queen_rows[MAX_N];
#pragma omp parallel for reduction(+:number_solutions) private(code) check
    for (iter = 0; iter < max_iter; iter++)
    {
        int i;
        
        //memset(queen_rows, NULL, sizeof(int)*MAX_N);
        
        code = iter;
        // the index correspond to the queen's number and the queen's collumn
        // we only generate configurations where there's only one queen per collumn
        for (i = 0; i < n; i++)
        {
            queen_rows[i] = code % n;
            code /= n;
        }
        if (check_acceptable(queen_rows, n))
        {
            number_solutions += 1;
            for (i = 0; i < n; i++)
            {
                queen_rows[i] = NULL;
		
            }
        }
    }
    // get end time


    printf("Number of found solutions is %d\n", number_solutions);
    return 0;
}



