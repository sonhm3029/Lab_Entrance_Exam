#include <math.h> 
#include <stdio.h> 
#include <stdlib.h>
#define N 512


int main()
{
	FILE *file;
	file = fopen("path_to_input_file", "r");//openfile
	if( file == NULL)
	{
		printf("Error!");
		exit(1);
	}

	int a[N][N], newArray[N][N], i, j, k;//array to represent image matrix
	int hist[256] = {0};
	int cdfHist[256] = {0};
    for ( i = 0; i<N; i++)
    {
    	for ( j = 0; j<N; j++)
    	{
    		fscanf(file,"%d", &a[i][j]);
		}
	}
	// Calculate for histogram (calculate frequency)
    for ( k = 0; k< 256; k++)
    {
    	for ( i = 0; i<N; i++)
    	{
    		for ( j = 0; j<N; j++)
    		{
    			if( a[i][j] == k)
    			{
    				hist[k] += 1;
				}
			}
		}
	}
	
	//	The cumulative distribution function (cdf)
	
	cdfHist[0] = hist[0];
	for ( k = 1; k < 256; k++)
	{
		cdfHist[k] += (hist[k]+ cdfHist[k -1]);
	//		printf("\n cdfHist[%d] = %d",k, cdfHist[k]);
	}

	//  Calculate cdfmin
	int cdfmin;
	for( k = 0; k < 256; k++)
	{
		if( hist[k] != 0)
		{
			cdfmin = cdfHist[k];
			break;
		}
	}	
	
	// Final calculate for equalization histogram
	for( k = 0; k <256; k++)
	{
		for( i =0; i < N; i++)
		{
			for( j =0; j<N; j++)
			{
				if( a[i][j] == k)
				{
					newArray[i][j] = ((cdfHist[k] - cdfmin)*254)/(N*N- cdfmin);
				}
			}
		}
	}
	
	//write newArray into text file
	FILE *newFile;
	newFile = fopen("path_to_output_file","w");
	for( i = 0; i<N; i++)
	{
  		for ( j=0; j<N; j++)
  		{
  			fprintf(newFile,"%-4d", newArray[i][j]);
		}
		fprintf(newFile,"\n");
	}
	
	return 0;
}