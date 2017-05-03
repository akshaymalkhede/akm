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

//// Write data to file
void write_data(char *filename,double A[][col1],int row)
{
printf("\n Creating %s file, Please wait...",filename);
FILE *fp;
int i,j;
fp=fopen(filename,"w+");
for(i=0;i<row;i++)
{
////    fprintf(fp,"\n%d",i+1);

	for(j=0;j<col1;j++)
	{
		fprintf(fp,"%g,",A[i][j]);
	}
	fprintf(fp,"\n");
}
fclose(fp);
printf("\n %s file created",filename);
}


//matrix multiplication function. A,B = input matrix    C=output matrix
//row= row of A    mid= common factor of A and B        col=column of B
void matrix_mul(double A[][col1],double B[][col2],double C[][col3],int row,int mid,int col)
{
	int i,j,k;
	double sum;
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			sum=0;
			for(k=0;k<mid;k++)
			{
				sum=sum+A[i][k]*B[k][i];
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
	int i,j,k,epoch;
	const short int l=12,m=11,n=1;	//Number of input, hidden and output neurons
	const double eta=0.88,alpha=0.67,lamda=0.5;
	char *filename;
	double I[740][12],J[296][12],T[740][1],deltav[12][11],deltaw[11][1],v[12][11],w[11][1],ih[11][1],oh[11],sum;
	double io[1][1],z[11][1],d,oo,y[11][1],e[11][0],stard[11][1],stardT[1][11];
	double vt[11][12],wt[1][11],Ik[12][1],x[12][11],error_rate[1000];
	memset(deltav, 0, sizeof(deltav[0][0]) * 12 * 11);	//to make all zeros
	memset(deltav, 0, sizeof(deltaw[0][0]) * 11 * 1);	//to make all zeros
	for(i=0;i<444;i++){T[i][0]=0;}	//zeros(444,1)
	for(i=444;i<740;i++){T[i][0]=1;}	//ones(296,1)
	col1=11;col2=12;	//set columns for v and v-transpose
	matrix_transpose(v,vt);
	col1=1;col2=11;
	matrix_transpose(w,wt);
	//read data into I
	filename="con_inrush.csv";
	col1=12;
	read_data(I,filename);
	filename="con_fault.csv";
	col1=12;
	read_data(J,filename);
	printf("Please Wait...\n");
	for(i=444;i<740;i++)	//combining I and J  ie  I=[inr;flt];
	{
		for(j=0;j<12;j++)
		{
			I[i][j]=J[i][j];
		}
	}
	
	

	srand(1);
	for(i = 0;i < 12;i++)
	{
		for(j = 0;j < 11;j++)
		{
			v[i][j] = (double)(rand()%100 + 1);
		}
	}
	for(i = 0;i < 11;i++)
	{
		for(j = 0;j < 1;j++)
		{
			w[i][j] = (double)(rand()%100 + 1);
		}
	}


	for(epoch=0;epoch<1000;epoch++)
	{
		sum=0;
		for(k=0;k<740;k++)
		{

			for(j=0;j<12;j++){Ik[j][1]=I[k][j];}	//calculation of Ik'
			col1=12,col2=1,col3=1;
			matrix_mul(vt,Ik,ih,11,12,1);	//calculation of ih
			for(i=0;i<11;i++)
			{
				oh[i]=(2/(1+exp(-lamda*ih[i][0])))-1;
				z[i][0]=oh[i];		// calculation for z
			}
			col1=11,col2=1,col3=1;
			matrix_mul(wt,z,io,1,11,1);	//calculation for io
			oo=(2/(1+exp(-lamda*io[0][0])))-1;
			d=(lamda/2)*((T[k][0]-oo)*(1-oo*oo));
			for(i=0;i<11;i++)
			{
				y[i][0]=d*z[i][0];	//calculation for y
				deltaw[i][0]=(alpha*deltaw[i][0])+(eta*y[i][0]);	//calculation for deltaw
				e[i][0]=w[i][0]*d;	//calculation for e
				stard[i][0]=(lamda/2)*e[i][0]*((z[i][0]*z[i][0])-1);	//calculation for stard
			}
			for(i=0;i<12;i++){Ik[i][0]=I[k][i];}	//calculation for Ik transpose
			for(i=0;i<11;i++){stardT[0][i]=stard[i][0];}	//calculation for stard transpose
			col1=1;col2=11;col3=11;
			matrix_mul(Ik,stardT,x,12,1,11);	//calculation for x
			for(i=0;i<12;i++)
			{
				for(j=0;j<11;j++)
				{
					deltav[i][j]=(alpha*deltav[i][j])+(eta*x[i][j]);
					v[i][j]=v[i][j]+deltav[i][j];
				}
			}
			for(i=0;i<11;i++){w[i][0]=w[i][0]+deltaw[i][0];}
			d=(T[k][0]-oo)*(T[k][0]-oo);	//calculation for EP11 (taken EP11 as d )
			d=sqrt(d)/n;
			sum=d+sum;

			}
		error_rate[epoch]=sum/740;

		}
	filename="datav.csv";col1=11;write_data(filename,v,12);	//save weights v and w
	filename="dataw.csv";col1=1;write_data(filename,w,11);

return 0;
}

