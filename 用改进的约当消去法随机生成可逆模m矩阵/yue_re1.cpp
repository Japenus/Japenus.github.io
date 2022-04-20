#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"string.h"
#include"time.h"
int mod(int c,int m)
{ if(c>=0)return c%m;
  else if(c%m==0)
	  return 0;
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
int *table;
void ini(int m)
{ int i,j;
  table=(int *)calloc(m,sizeof(int));
  table[0]=0;
  table[1]=1;
  for(i=2;i<m;i++)
  { for(j=1;j<m;j++)
  if(mod(i*j,m)==1)break;
     table[i]=j;
  }
}
void re_verse(char *filename)
{ FILE *fp;
  
  int n,i,j,h,k;
int **a,**b,temp,m;
 
  fp=fopen(filename,"rb");
  if(fp==NULL)
  { printf("模m矩阵文件%s不存在.\n",filename);
    system("pause");
	exit(-1);
  }
  fread(&m,sizeof(int),1,fp);
  fread(&n,sizeof(int),1,fp);
  a=(int**)calloc(n,sizeof(int*));
  for(i=0;i<n;i++)
	  a[i]=(int *)calloc(n,sizeof(int));
  b=(int **)calloc(n,sizeof(int*));
  for(i=0;i<n;i++)
	  b[i]=(int*)calloc(n,sizeof(int));
  for(i=0;i<n;i++)
 fread(a[i],sizeof(int),n,fp);
          fclose(fp);
    for(i=0;i<n;i++)
      for(j=0;j<n;j++)
		 if(i==j)b[i][j]=1;
		 else b[i][j]=0;
for(i=0;i<n;i++)
{
	h=i;
	for(j=i;j<n;j++)
		if(gcd(a[j][i],m)==1){h=j;
		break;}
    if(h>i)
	for(j=0;j<n;j++)
		  { temp=a[i][j];
		    a[i][j]=a[h][j];
			a[h][j]=temp;
            temp=b[i][j];
		    b[i][j]=b[h][j];
			b[h][j]=temp;
		  }
if(a[i][i]==0)
{ printf("a[%d][%d]=%d",i,i,a[i][i]);
return;
}
	for(j=i+1;j<n;j++)
	a[i][j]=mod(a[i][j]*table[a[i][i]],m);
    for(j=0;j<n;j++)
	b[i][j]=mod(b[i][j]*table[a[i][i]],m);
		for(j=0;j<n;j++)
		{for(k=i+1;k<n;k++)
			    if(j!=i)
				a[j][k]=mod(a[j][k]-a[j][i]*a[i][k],m);
               for(k=0;k<n;k++)
			    if(j!=i)
				 b[j][k]=mod(b[j][k]-b[i][k]*a[j][i],m);
			 a[j][i]=0;
			}
a[i][i]=1;

  }
fp=fopen("redg.xls","wb");
fwrite(&m,sizeof(int),1,fp);
fwrite(&n,sizeof(int),1,fp);
for(i=0;i<n;i++)
fwrite(b[i],sizeof(int),n,fp);
fclose(fp);
for(i=0;i<n;i++)
      {free(a[i]);
       free(b[i]);
       }
   free(a);
   free(b);
}
int hls(int m,int n, int **a) 
{ 
int s=1; 
int i,j,h,k;
int temp;
int **b;
b=(int **)calloc(n,sizeof(int *));
for(i=0;i<n;i++)
b[i]=(int *)calloc(n,sizeof(int));
for(i=0;i<n;i++)
for(j=0;j<n;j++)
b[i][j]=a[i][j];
for(i=0;i<n;i++)
{
	h=i;
	for(j=i;j<n;j++)
		if(gcd(b[j][i],m)==1){h=j;
		break;}
if(j==n)return 0;
    if(h>i)
	for(j=0;j<n;j++)
		  { temp=b[i][j];
		    b[i][j]=b[h][j];
			b[h][j]=temp;
		  }
	for(j=i+1;j<n;j++)
	b[i][j]=mod(b[i][j]*table[b[i][i]],m);
		for(j=0;j<n;j++)
		{for(k=i+1;k<n;k++)
			    if(j!=i)
				b[j][k]=mod(b[j][k]-b[j][i]*b[i][k],m);
			 if(j!=i)b[j][i]=0;
			}

}
for(i=0;i<n;i++)
{s*=b[i][i];
s=mod(s,m);}
for(i=0;i<n;i++)
       free(b[i]);
   free(b);
return s; 
} 
void main()
{
FILE *fp;
int **a,**b,**c,mat,i,j,k,n,m;
int *x,*y; 
printf("请输入模m的值:");
scanf("%d",&m);
srand(time(0));
printf("请输入阶数:");  
scanf("%d",&n);
if(m<2)
{ printf("模不能小于2");
  return;
}
if(n<1)
{ printf("阶数不能小于1");
  return;
}
a=(int **)calloc(n,sizeof(int *));
for(i=0;i<n;i++)
a[i]=(int *)calloc(n,sizeof(int));
b=(int **)calloc(n,sizeof(int *));
for(i=0;i<n;i++)
b[i]=(int *)calloc(n,sizeof(int));
c=(int **)calloc(n,sizeof(int *));
for(i=0;i<n;i++)
c[i]=(int *)calloc(n,sizeof(int));
table=(int *)calloc(m,sizeof(int));
x=(int *)calloc(n,sizeof(int));
y=(int *)calloc(n,sizeof(int));
for(i=0;i<n;i++)
x[i]=i;
for(i=0;i<n;i++) 
for(j=0;j<n;j++)
a[i][j]=rand()%m; 
ini(m);
mat=hls(m,n,a);
for(;;)
{ 
  if(mat!=0&&gcd(mat,m)==1)break;
for(i=0;i<n;i++) 
for(j=0;j<n;j++)
a[i][j]=rand()%m; 
mat=hls(m,n,a);
}
fp=fopen("dg.xls","wb");
fwrite(&m,sizeof(int),1,fp);
fwrite(&n,sizeof(int),1,fp);
for(i=0;i<n;i++)
fwrite(a[i],sizeof(int),n,fp);
fclose(fp);
ini(m);
re_verse("dg.xls");
fp=fopen("redg.xls","rb");
fread(&m,sizeof(int),1,fp);
fread(&n,sizeof(int),1,fp);
for(i=0;i<n;i++) 
fread(b[i],sizeof(int),n,fp);
fclose(fp);
for(i=0;i<n;i++)
      for(j=0;j<n;j++)
            { c[i][j]=0;
              for(k=0;k<n;k++)
                 { c[i][j]+=a[i][k]*b[k][j];
                   c[i][j]=mod(c[i][j],m);
                  }
            }
for(i=0;i<n;i++)
     if(c[i][i]!=1)break;
if(i<n)
     {printf("不是互逆矩阵");
  return;
      }
for(i=0;i<n;i++)
      for(j=0;j<n;j++)
            if(i!=j&&c[i][j]!=0)
                        break;
  if(i<n&&j<n)
  { printf("不是互逆矩阵");
  return;
      }
printf("互逆矩阵成功生成");
for(i=0;i<n;i++)
   free(a[i]);
   free(a);
   free(x);
   free(y);
   free(table);
}
 
