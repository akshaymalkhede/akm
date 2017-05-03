#include<iostream>
#include<iomanip>
using namespace std;
int main()
{int inr[5][2];
int inr_transpose[2][5];
for(int i=0;i<5;i++)
{for(int j=0;j<2;j++)
{inr[i][j]= i+j+1;
cout<<setw(5)<<inr[i][j];
}cout<<endl;}
for (int i = 0;i <5; i++)
{for (int j =0; j <2; j++)
{inr_transpose[j][i]=inr[i][j];	
}
}
cout<<"inr transpose"<<endl;;
for(int i=0;i<2;i++)
{for (int j=0;j<5;j++){
cout<<setw(5)<<inr_transpose[i][j];
}cout<<endl;}

float T[740][1];
cout<<"target matrix"<<endl;
for(int i=0;i<740;i++)
{for(int j=0;j<1;j++)
{if(i<444)
{T[i][j]=0;
}else
{T[i][j]=1;
}
cout<<T[i][j]<<endl;}}
int l=2;
int m=3;
int n=1;
float e=0.88;
float a=0.67;
float y=0.5;
 float dv[l][m];   float dw[m][n];
 float v[l][m];float vtranspose[m][l];
float w[m][n];int iteration =1;
cout<<"Now enter v matrix"<<endl;
for(int i=0;i<l;i++)
{for(int j=0;j<m;j++)
{cout<<"v "<<i+1<<j+1<<" ";
cin>>v[i][j];}}
for (int i = 0;i <l; i++)
{for (int j = 0; j <m; j++)
{vtranspose[j][i]=v[i][j];	
}
}
cout<<"vtranspose"<<endl;;
for(int i=0;i<m;i++)
{for (int j=0;j<l;j++){

cout<<setw(3)<<vtranspose[i][j];
}cout<<endl;}
float ih[2][5];

for(int i=0;i<m;i++){
for(int k=0;k<5;k++)
{ih[i][k]=0;
for(int j=0;j<l;j++){
ih[i][k]=ih[i][k]+vtranspose[i][j]*inr_transpose[j][k];

}}}cout<<"hidden input matrix"<<endl;
for(int i=0;i<3;i++)
{for(int j=0;j<5;j++)
cout<<setw(3)<<ih[i][j];
cout<<endl;}}

 //}
 //} 

