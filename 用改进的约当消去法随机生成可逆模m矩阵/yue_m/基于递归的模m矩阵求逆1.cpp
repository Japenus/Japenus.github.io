#include"stdio.h"
#include"stdlib.h"
#include"time.h"
int mod(int c,int m)
{ if(c>=0)return c%m;
   else return m+c%m;
}
int gcd(int a,int m)
{ int r;
  r=1;
 while(r!=0)
 {
   r=mod(a,m);
   a=m;
   m=r; 
 }
 return a;
}
void swap(int j,int n,int **a) 
{ int x,y,b[100][100],i; 
for(y=j;y<n;y++) 
for(x=0;x<=n-1;x++)
a[x][y]=a[x][y+1]; 
} 

int hls(int N, int **a,int md) 
{ 
int x,y,j,s=0,b[100][100],i; 
if(N==2) return a[0][0]*a[1][1]-a[0][1]*a[1][0]; 
for(j=0;j<N;j++) 
{  
for(x=0;x<N;x++) 
for(y=0;y<N;y++) 
b[x][y]=a[x][y]; 
swap(j,N-1,a); 
if((j+N-1)%2) s-=a[N-1][j]*hls(N-1,a,md); 
else s+=a[N-1][j]*hls(N-1,a,md); 
s=mod(s,md);
for(x=0;x<N;x++) 
for(y=0;y<N;y++) 
a[x][y]=b[x][y]; 
}
return mod(s,md); 
}  

main() 
{ FILE *fp;
int N,**a,**b,**c,**d,**e,s,flag,M,odd,i,j,k,t,P,m,n,q,*x,*y,md; 
printf("请输入模m的值:");
scanf("%d",&md);
getchar();
srand(time(0));
//srand(time(0));
printf("请输入阶数:");  
scanf("%d",&N);
a=(int **)calloc(N,sizeof(int *));
for(i=0;i<N;i++)
a[i]=(int *)calloc(N,sizeof(int));
b=(int **)calloc(N,sizeof(int *));
for(i=0;i<N;i++)
b[i]=(int *)calloc(N,sizeof(int));
c=(int **)calloc(N,sizeof(int *));
for(i=0;i<N;i++)
c[i]=(int *)calloc(N,sizeof(int));
d=(int **)calloc(N,sizeof(int *));
for(i=0;i<N;i++)
d[i]=(int *)calloc(N,sizeof(int));
e=(int **)calloc(N,sizeof(int *));
for(i=0;i<N;i++)
e[i]=(int *)calloc(N,sizeof(int));
x=(int *)calloc(N,sizeof(int));
for(i=0;i<N;i++)
x[i]=i;
y=(int *)calloc(N,sizeof(int));
for(i=0;i<N;i++) 
for(j=0;j<N;j++)
{flag=rand()%1000;
 if(rand()%2==0)
a[i][j]=flag;
 else
	 a[i][j]=-flag;
}
for(;;)
{ M=hls(N,a,md);
  if(gcd(M,md)==1)break;
for(i=0;i<N;i++) 
for(j=0;j<N;j++)
a[i][j]=rand()%md;
 
}
for(j=1;j<md;j++)
if(mod(M*j,md)==1)break;
printf("因子=%d\n",j);
printf("\n");
for(m=0;m<N;m++) 
{for(n=0;n<N;n++)
printf("%-8d",a[m][n]);
printf("\n");}
for(m=0;m<N;m++) 
for(n=0;n<N;n++)
if(m!=n)c[m][n]=0;
else c[m][n]=1;
for(m=0;m<N;m++) 
for(n=0;n<N;n++)
b[m][n]=a[m][n];
P=hls(N,a,md);
printf("D=%d\n",P);
for(i=0;i<N;i++)
{ for(k=0;k<N;k++)
{ for(t=0;t<N;t++)
   b[t][k]=c[t][i];

   M=hls(N,b,md);
for(m=0;m<N;m++) 
{for(n=0;n<N;n++)
printf("%-8d",b[m][n]);
printf("\n");}
printf("D%d%d=%d\n",k,i,M);
   d[k][i]=mod(M*j,md);
printf("d[%d][%d]=%d\n",k,i,d[k][i]);
for(t=0;t<N;t++)
   b[t][k]=a[t][k];
}
//system("pause");
}
printf("相应的%d阶解密密匙:\n",N);
for(i=0;i<N;i++) 
{for(j=0;j<N;j++)
printf("%-8d",d[i][j]);
printf("\n");}
printf("加密测试:\n");
printf("明文:");
for(i=0;i<N;i++)
printf("%-8d",x[i]);
printf("\n");
for(i=0;i<N;i++)
{
	y[i]=0;
	for(j=0;j<N;j++)
	{y[i]+=a[i][j]*x[j];
	y[i]=mod(y[i],md);}
}
printf("密文:");
for(i=0;i<N;i++)
printf("%-8d",y[i]);
printf("\n");
for(i=0;i<N;i++)
{
	x[i]=0;
	for(j=0;j<N;j++)
	{x[i]+=d[i][j]*y[j];
	x[i]=mod(x[i],md);}
}
printf("解密测试:\n");
printf("明文:");
for(i=0;i<N;i++)
printf("%-8d",x[i]);
printf("\n");
fp=fopen("out.txt","w");
fprintf(fp,"生成加密密匙:\n");
for(m=0;m<N;m++) 
{for(n=0;n<N;n++)
fprintf(fp,"%-8d",a[m][n]);
fprintf(fp,"\n");}
fprintf(fp,"生成解密密匙:\n");
for(m=0;m<N;m++) 
{for(n=0;n<N;n++)
fprintf(fp,"%-8d",d[m][n]);
fprintf(fp,"\n");}
fclose(fp);
for(i=0;i<N;i++)
{free(b[i]);
 free(a[i]);
 free(c[i]);
 free(d[i]);
 free(e[i]);
}
free(b);
free(x);
free(y);
system("pause");
system("cmd /c start out.txt");
}  
