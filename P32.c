#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timing.h"
#define N 1500     /* matrix size */
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int main (int argc, char *argv[]) 
{
int	i, j, k;
timing_t tstart, tend;
double	a[N][N],           /* matrix A to be multiplied */
  b[N][N],           /* matrix B to be multiplied */
	c[N][N];           /* result matrix C */

  for (i=0; i<N; i++)
    for (j=0; j<N; j++)
      a[i][j]= i+j;

  for (i=0; i<N; i++)
    for (j=0; j<N; j++)
      b[i][j]= i*j;

  for (i=0; i<N; i++)
    for (j=0; j<N; j++)
      c[i][j]= 0;

get_time(&tstart);

/******** openacc **********/
#pragma acc data copy(u), create(utmp) # a single copy of data
#pragma acc kernels
{
  #pragma acc loop gang
  #pragma acc loop vector(128)
  for (i=0; i<N; i++){
    for(j=0; j<N; j++){      
      for (k=0; k<N; k++){
        c[i][j] += a[i][k] * b[k][j];
      }
    }
}
get_time(&tend);


  printf("Elapsed time: %g s\n", timespec_diff(tstart, tend));

  printf("*****************************************************\n");

  printf("Result Matrix:\n");
  printf("i=0,j=0,c=%6.2f, i=n-1,j=n-1,c=%6.2f\n",c[0][0],c[N-1][N-1]);
  /*
  for (i=0; i<N; i++)
  {
    for (j=0; j<N; j++) {
      printf("%6.2f   ", c[i][j]);
    }
    printf("\n"); 
  }*/
  printf("******************************************************\n");
  printf ("Done.\n");
printf("Elapsed time: %g s\n", timespec_diff(tstart, tend));
}

