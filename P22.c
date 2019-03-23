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

/******** simple matrix multiplication **********/

  for (i=0; i<N; i++){
    for(j=0; j<N; j++){      
      for (k=0; k<N; k++){
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
/******* loop unrolling ********/
  /*
  for (i=0; i<N; i++){
    for(j=0; j<N; j++){      
      for (k=0; k<N; k+=4){
        c[i][j] = c[i][j]+a[i][k] * b[k][j]+a[i][k+1] * b[k+1][j]+a[i][k+2] * b[k+2][j]+a[i][k+3] * b[k+3][j];
      }
    }
  }*/

/******** matrix blocking ********/
 /* 
const int block_size=30;

for (k = 0; k < N; k += block_size){
  for (j = 0; j < N; j += block_size){
    for (i = 0; i <N; ++i){
      for (int jj = j; jj <  MIN(j + block_size, N); ++jj){
        for (int kk = k; kk < MIN(k + block_size, N); ++kk){
          c[i][jj] += a[i][kk] * b[kk][jj];
        }
      }
    }
  }
}*/

/******** matrix blocking and unrolling ********/
 /*
const int block_size=30;

for (k = 0; k < N; k += block_size){
  for (j = 0; j < N; j += block_size){
    for (i = 0; i <N; ++i){
      for (int jj = j; jj <  MIN(j + block_size, N); ++jj){
        for (int kk = k; kk < MIN(k + block_size, N); kk+=4){
          c[i][jj] = c[i][jj]+a[i][kk] * b[kk][jj]+a[i][kk+1] * b[kk+1][jj]+a[i][kk+2] * b[kk+2][jj]+a[i][kk+3] * b[kk+3][jj];
        }
      }
    }
  }
}*/




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

