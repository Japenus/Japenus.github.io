#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"string.h"
#include"time.h"
int mod(int c,int m)
{ if(c>=0)return c%m;
   else return m+c%m;
}
void main()
{
FILE *fp;
int **a,i,j,m,n,*x,*y; 
char bm[10];
fp=fopen("dg.xls","rb");
fread(&m,sizeof(int),1,fp);
fread(&n,sizeof(int),1,fp);
a=(int **)calloc(n,sizeof(int *));
for(i=0;i<n;i++)
a[i]=(int *)calloc(n,sizeof(int));
x=(int *)calloc(n,sizeof(int));
y=(int *)calloc(n,sizeof(int));
for(i=0;i<n;i++) 
fread(a[i],sizeof(int),n,fp);
fclose(fp);
srand(time(0));
printf("加密测试:\n");
printf("明文:");
for(i=0;i<n;i++)
x[i]=rand()%m;
for(i=0;i<n;i++)
printf("%-8d",x[i]);
printf("\n");
for(i=0;i<n;i++)
{
	y[i]=0;
	for(j=0;j<n;j++)
	{y[i]+=a[i][j]*x[j];
	y[i]=mod(y[i],m);}
}
printf("密文:");
for(i=0;i<n;i++)
printf("%-8d",y[i]);
printf("\n");
fp=fopen("mingwen.xls","w");
for(i=0;i<n;i++)
fprintf(fp,"%d\t",x[i]);
fprintf(fp,"\n");
fclose(fp);
fp=fopen("miwen.xls","w");
for(i=0;i<n;i++)
fprintf(fp,"%d\t",y[i]);
fprintf(fp,"\n");
fclose(fp);
for(i=0;i<n;i++)
free(a[i]);
free(a);
free(x);
free(y);	
}