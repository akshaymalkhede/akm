#include "ledcfg.h"

/*
 *  The Board Support Library is divided into several modules, each
 *  of which has its own include file.  The file dsk6713.h must be included
 *  in every program that uses the BSL.  This example also includes
 *  dsk6713_led.h and dsk6713_dip.h because it uses the LED and DIP modules.
 */
#include "dsk6713.h"
#include "dsk6713_led.h"
#include "dsk6713_dip.h"

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

int col1,col2,col3;	//global variable to provide column size for dynamic multidimensional arrays

int read_data(double A[][col1],char *filename)
{
	char buffer[1024],str1[]=",";	//buffer size affects length of characters to be scanned
   	char *line,*ch;
   	int i=0,j=0,k=0;
	printf("Reading file \"%s\"\n",filename);
   	FILE *fstream = fopen(filename,"r");
   	if(fstream == NULL)
   	{
      printf("\nFile \"%s\" opening failed.", filename);
      return -1 ;
   	}

   	while((line=fgets(buffer,sizeof(buffer),fstream)) != NULL)
   	{
   		ch = strtok(line, ",");
  		while (ch != NULL)
		  {
  			sscanf(ch,"%lf", &A[i][j]);	//scannning with long float will scan whole data
			ch = strtok(NULL, " ,");
  			j=j+1;
  		}
  	j=0;
  	i=i+1;
	}
	printf("Finished reading \"%s\"\n",filename);
return 0;
}

//matrix multiplication function. A,B = input matrix    C=output matrix
//row= row of A    mid= common factor of A and B        col=column of B
void matrix_mul(double A[][col1],double B[][col2],double C[][col3],int row,int mid,int col)
{
	int i,j,k;
	float sum;
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			sum=0;
			for(k=0;k<mid;k++)
			{
				sum=sum + (A[i][k]*B[k][i]);
				printf("%f \n",sum);
			}
			C[i][j]=sum;
		}
	}
}

void matrix_transpose(double A[][col1] ,double B[][col2])  // to create transpose of a matrix
{
	int i,j;
	for(i=0;i<col2;i++)
	{
		for(j=0;j<col1;j++)
		{
			B[j][i]=A[i][j];
		}
	}
}

int main()
{
	int i,j,k;
	const short int l=12,m=11,n=1;	//Number of input, hidden and output neurons	
	const float eta=0.9,alpha=0.6,lamda=0.6;
	char *filename;
	double TP[12][11],v[11][12],w[11][1],ih[12][1],oh[11],io[1][1],oo[12];	//TP data we have to read from file
	double TPk[11][1],vt[12][11],wt[1][11],z[11][1];
	srand(1);
	for(i = 0;i < 12;i++)
	{
		for(j = 0;j < 11;j++)
		{
			TP[i][j] = rand()%100 + 1;
		}
	}
	filename="datav.csv";
	col1=12;read_data(v,filename);	// provide column for v matrix
	filename="dataw.csv";
	col1=1;read_data(w,filename);
	col1=12,col2=11;
	matrix_transpose(v,vt);
	col1=1,col2=11;
	matrix_transpose(w,wt);
	for(k=0;k<12;k++)
	{
		for(i=0;i<11;i++){TPk[i][0]=TP[k][i];}	//calculation of TP transpose ( that is TPk )	
		col1=11,col2=1,col3=1;
		matrix_mul(vt,TPk,ih,12,11,1);
		for(i=0;i<m;i++)
		{
			oh[i]=(2/(1+exp(-lamda*ih[i][0])))-1;
			z[i][0]=oh[i];		//calculation of z=oh'
		}
		col1=11,col2=1,col3=1;
		matrix_mul(wt,z,io,1,11,1);	//calculation for io ( io will be single element )
		oo[k]=(2/(1+exp(-lamda*io[0][0])))-1;
	}
	for(k=0;k<12;k++)
	{
		if(oo[k]<=0.05){printf("Magnetizing Inrush Condition. \n");}
		if(oo[k]>0.05){printf("Fault Condition.\n");}
	}
return 0;
}
