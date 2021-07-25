#include <stdio.h>
#include <stdlib.h> 
#define N 512


void sortArray(int filterMask[])
{	
	int i,n = 9,j;
	int temp;
	for ( i = 0; i< n-1; i++)
	{
		for( j = i+1; j<n; j++)
		{
			if(filterMask[j]<filterMask[i])
			{
				temp = filterMask[j];
				filterMask[j] = filterMask[i];
				filterMask[i] = temp; 
			}
		}
	}
}


int main()
{
	int a[514][514];// array to represent image matrix 
	FILE *f;
	int i,j;
	f = fopen("path_to_input_file","r");
	if( f == NULL)
	{
		printf("Error!");
		exit(1);
	}
   
   // Open file and read in into a 2D array.
   for( i = 0; i <514; i++)
   {
     a[i][0] = 0;
     a[i][513] = 0;
   }
   for( j = 0; j<514; j++)
   {
     a[0][j] = 0;
     a[513][j] = 0;
   }
	for( i =1; i<513; i++)
	{
   		for ( j=1; j<513; j++)
   		{
   			fscanf(f,"%d", &a[i][j]);
		}
	}
	
	
	// use Median Filter
	int filterMask[9];
	int newArray[512][512];
	// Median filter use a 3*3 filter matrix
	for (i =1; i<513;i++)
	{
		for(j =1; j<513; j++)
		{
			filterMask[0] = a[i-1][j-1]; 
            		filterMask[1] = a[i-1][j]; 
            		filterMask[2] = a[i-1][j+1]; 
            		filterMask[3] = a[i][j-1]; 
            		filterMask[4] = a[i][j]; 
            		filterMask[5] = a[i][j+1]; 
            		filterMask[6] = a[i+1][j-1]; 
            		filterMask[7] = a[i+1][j]; 
            		filterMask[8] = a[i+1][j+1]; 
            		//sort maskArray:
            		sortArray(filterMask);
            		newArray[i-1][j-1] = filterMask[4];// array for output matrix
		}
	}


	FILE *newFile;
	newFile = fopen("path_to_output_file","w");
	// write newArray into output file
	for( i =0; i<N; i++)
	{
  		for ( j=0; j<N; j++)
  		{
  			fprintf(newFile,"%-4d", newArray[i][j]);
		}
		fprintf(newFile,"\n");
	}
  return 0;
}


