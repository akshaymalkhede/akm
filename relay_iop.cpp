 #include<iostream>
 #include<cmath>
#include<iomanip>
using namespace std;
int main()

{
int inr[5][3];
int inr_transpose[3][5];
cout<<"inr matrix"<<endl;
for(int i=0;i<5;i++)
{for(int j=0;j<3;j++)
{inr[i][j]= i+j+1;
cout<<setw(5)<<inr[i][j];
}cout<<endl;}
for (int i = 0;i <5; i++)          //input matrix
{for (int j =0; j <3; j++)
{inr_transpose[j][i]=inr[i][j];	
}
}
cout<<"inr transpose matrix"<<endl;;
for(int i=0;i<3;i++)
{for (int j=0;j<5;j++){
cout<<setw(3)<<inr_transpose[i][j];
}cout<<endl;}

float T[1][5];
cout<<"output target matrix"<<endl;
for(int i=0;i<1;i++)
{for(int j=0;j<5;j++)
{if(j<3)                                       //target output matrix
{T[i][j]=1.20;
}else
{T[i][j]=1;
}
cout<<setw(5)<<T[i][j];}}
int l=3;
int m=2;
int n=1;
float e=0.88;
float a=0.67;
float y=0.5;
float dv[l][m];   float dw[m][n];
 float v[l][m]; float vtranspose[m][l];
float w[m][n];  float w_transpose[n][m]; 
 
float ih[m][5];
float oh[m][5];float oh_transpose[5][m];
float oo[n][5];float io[m][5];
cout<<endl;
cout<<"Now enter v matrix"<<endl;
for(int i=0;i<l;i++)
{for(int j=0;j<m;j++)
{cout<<"v "<<i+1<<j+1<<" ";
cin>>v[i][j];}}                            // v matrix initialisation
for (int i = 0;i <l; i++)
{for (int j = 0; j <m; j++)
{vtranspose[j][i]=v[i][j];	
}
}
cout<<"Now enter w matrix"<<endl;
for(int i=0;i<m;i++)                               // w matrix initialisation
{for(int j=0;j<n;j++)
{cout<<"w "<<i+1<<j+1<<" ";
cin>>w[i][j];}}int iteration =1;
float error_rate=1;

while(iteration<500)
{                                             //while loop begin
cout<<"iteration  "<<iteration<<endl;
cout<<"vtranspose matrix"<<endl;
for(int i=0;i<m;i++)
{for (int j=0;j<l;j++){
cout<<setw(5)<<vtranspose[i][j];
}cout<<endl;}
for(int i=0;i<m;i++){
for(int k=0;k<5;k++)
{ih[i][k]=0;
for(int j=0;j<l;j++){
ih[i][k]=ih[i][k]+vtranspose[i][j]*inr_transpose[j][k];

}}}                                                        // hidden layer input matrix
cout<<"hidden layer input matrix"<<endl;
for(int i=0;i<m;i++)
{for(int j=0;j<5;j++)
cout<<setw(5)<<ih[i][j];                            
cout<<endl;}
cout<<endl;
cout<<"output of hidden layer matrix"<<endl;
for(int i=0;i<m;i++)
{for(int j=0;j<5;j++)
{oh[i][j]=(2.0/(1.0+exp(-y*ih[i][j]))-1.0);
cout<<setw(10)<<oh[i][j];}                                       // hidden layer output matrix
cout<<endl;}
cout<<endl;
cout<<"transpose of output hidden matrix"<<endl;
for (int i = 0;i <m; i++)
{for (int j = 0; j <5; j++)
{oh_transpose[j][i]=oh[i][j];	
}
}
for(int i=0;i<5;i++)
{for (int j=0;j<m;j++){
cout<<setw(10)<<oh_transpose[i][j];
}cout<<endl;}
cout<<endl;

for (int i = 0;i <m; i++)
{for (int j = 0; j <n; j++)
{w_transpose[j][i]=w[i][j];	
}
}
cout<<"wtranspose matrix"<<endl;
for(int i=0;i<n;i++)
{for (int j=0;j<m;j++){
cout<<setw(5)<<w_transpose[i][j];
}cout<<endl;
}
cout<<endl;
for(int i=0;i<n;i++){
for(int k=0;k<5;k++)
{io[i][k]=0;
for(int j=0;j<m;j++){
io[i][k]=io[i][k]+w_transpose[i][j]*oh[j][k];

}}}
cout<<"output layer input matrix"<<endl;
for(int i=0;i<n;i++)
{for(int j=0;j<5;j++)                                                          //output layer input matrix
cout<<setw(10)<<io[i][j];
cout<<endl;}
cout<<endl;

cout<<"output layer output. matrix"<<endl;
for(int i=0;i<n;i++)
{for(int j=0;j<5;j++)
{oo[i][j]=(2.00/(1.00+exp(-y*io[i][j]))-1.00);
cout<<setw(10)<<oo[i][j];}                                                         //output layer output matrix
cout<<endl;}

float d[n][5];float d_transpose[5][n];
for(int i=0;i<n;i++)
{for(int j=0;j<5;j++){
d[i][j]=(y*((T[i][j]-oo[i][j])*(1.00-((oo[i][j])*(oo[i][j]))))/2.0);
cout<<setw(5)<<d[i][j];
}}
for (int i = 0;i <n; i++)
{for (int j = 0; j <5; j++)
{d_transpose[j][i]=d[i][j];	
}
}cout<<endl;
cout<<"dtranspose matrix"<<endl;
for(int i=0;i<5;i++)
{for (int j=0;j<n;j++){
cout<<setw(5)<<d_transpose[i][j];
}cout<<endl;                                               
}float z[m][n];
cout<<"z matrix"<<endl;
for(int i=0;i<m;i++){
for(int k=0;k<n;k++)
{z[i][k]=0;
for(int j=0;j<5;j++){
z[i][k]=z[i][k]+oh[i][j]*d_transpose[j][k];
}}}
for(int i=0;i<m;i++)
{for(int j=0;j<n;j++)
cout<<setw(5)<<z[i][j];
cout<<endl;}
for(int i=0;i<m;i++)
{for(int j=0;j<n;j++)
dw[i][j]=dw[i][j]*a+e*z[i][j];
}cout<<"dw matrix"<<endl;
for(int i=0;i<m;i++)                                                       // delta w matrix calculation
{for(int j=0;j<n;j++)
cout<<setw(5)<<dw[i][j];
cout<<endl;}

float ee[m][5];
cout<<" ee matrix"<<endl;
for(int i=0;i<m;i++){
for(int k=0;k<5;k++)
{ee[i][k]=0;
for(int j=0;j<n;j++){
ee[i][k]=ee[i][k]+w[i][j]*d[j][k];
}}}
for(int i=0;i<m;i++)
{for(int j=0;j<5;j++)
cout<<setw(5)<<ee[i][j];
cout<<endl;}

float stard[m][5];
for(int i=0;i<m;i++)
{for(int j=0;j<5;j++)
stard[i][j]=stard[i][j]+(y*(ee[i][j]*(((oh[i][j])*(oh[i][j]))-1))/2.0);
}cout<<"stard matrix"<<endl;
for(int i=0;i<m;i++)
{for(int j=0;j<5;j++)
cout<<setw(10)<<stard[i][j];
cout<<endl;}
cout<<endl;
float stard_transpose[5][m];
for (int i = 0;i <m; i++)
{for (int j = 0; j <5; j++)                   // stard matrix calculations
{stard_transpose[j][i]=stard[i][j];	
}
}cout<<endl;

cout<<"stard_transpose matrix"<<endl;
for(int i=0;i<5;i++)
{for (int j=0;j<m;j++){
cout<<setw(10)<<stard_transpose[i][j];}
cout<<endl;}
cout<<endl;

float xx[l][m];
cout<<"xx matrix"<<endl;
for(int i=0;i<l;i++)
{for(int j=0;j<m;j++){
xx[i][j]=0;
for(int k=0;k<5;k++)
xx[i][j]=xx[i][j]+inr_transpose[i][k]*stard_transpose[k][j];
}}
{for(int i=0;i<l;i++){
for(int j=0;j<m;j++)
cout<<setw(10)<<xx[i][j];
cout<<endl;
}}
cout<<endl;
cout<<"dv matrix"<<endl;
for(int i=0;i<l;i++)
{for(int j=0;j<m;j++)                                               //dv matrix calculation
dv[i][j]=a*dv[i][j]+e*xx[i][j];
}
for(int i=0;i<l;i++){
for(int j=0;j<m;j++)
{cout<<setw(5)<<dv[i][j];

}cout<<endl;}

cout<<endl;
cout<<" updated v matrix"<<endl;
for(int i=0;i<l;i++){
for(int j=0;j<m;j++)
{v[i][j]=v[i][j]+dv[i][j];                               // update v 
}}
for(int i=0;i<l;i++){
for(int j=0;j<m;j++)
{cout<<setw(10)<<v[i][j];
}cout<<endl;}
cout<<endl;

cout<<"updated w matrix"<<endl;
for(int i=0;i<m;i++){
for(int j=0;j<n;j++)                                      //update w
{w[i][j]=w[i][j]+dw[i][j];
}
}
for(int i=0;i<m;i++){
for(int j=0;j<n;j++)
{cout<<setw(10)<<w[i][j];}
cout<<endl;}
cout<<endl;
float sum =0;
float ep11[n][5];
for(int i=0;i<n;i++)
{for(int j=0;j<5;j++)                                             // error rate calculations
ep11[i][j]=((T[i][j]-oo[i][j])*(T[i][j]-oo[i][j]));
}

for(int i=0;i<n;i++)
{for(int j=0;j<5;j++)
sum=sum+ep11[i][j];
} iteration=iteration+1;
error_rate=sum/5.0;
cout<<"error rate  "<<error_rate<<endl;

}                                                                    //while loop end
return 0;
                                      
}










