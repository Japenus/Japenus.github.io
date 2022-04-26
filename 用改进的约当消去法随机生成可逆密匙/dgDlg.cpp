// dgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dg.h"
#include "dgDlg.h"
#include "yue_re.txt"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDgDlg dialog

CDgDlg::CDgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDgDlg)
	m_md = 2;
	m_n = 2;
	m_t = 0;
	m_s1 = _T("");
	m_s2 = _T("");
	m_s3 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDgDlg)
	DDX_Control(pDX, IDC_LIST2, m_list1);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_md);
	DDX_Text(pDX, IDC_EDIT2, m_n);
	DDX_Text(pDX, IDC_EDIT3, m_t);
	DDX_Text(pDX, IDC_EDIT4, m_s1);
	DDX_Text(pDX, IDC_EDIT5, m_s2);
	DDX_Text(pDX, IDC_EDIT6, m_s3);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDgDlg, CDialog)
	//{{AFX_MSG_MAP(CDgDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDgDlg message handlers

BOOL CDgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
::SetWindowPos(this->m_hWnd,HWND_BOTTOM,0,0,600,460,SWP_NOZORDER);
char bm[100];
m_list1.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
for(int i=0;i<10;i++) 
{   sprintf(bm,"第%d列",i+1);
	m_list1.InsertColumn(i,bm,LVCFMT_LEFT,50,i);
}
m_list.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
for(i=0;i<10;i++) 
{   sprintf(bm,"第%d列",i+1);
	m_list.InsertColumn(i,bm,LVCFMT_LEFT,50,i);
}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDgDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CDgDlg::OnButton1() 
{
FILE *fp;
int N,md; 
int **a,**d,**b,**c,M,i,j,k,m,n; 
char bm[10];
int *x,*y; 
UpdateData(true);
md=m_md;
n=m_n;
m_s1="";
m_s2="";
m_s3="";
UpdateData(false);
N=n;
if(md<2)
{ MessageBox("模不能小于2");
  return;
}
if(n<2)
{ MessageBox("阶数不能小于2");
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
d=(int **)calloc(n,sizeof(int *));
for(i=0;i<n;i++)
d[i]=(int *)calloc(n,sizeof(int));
x=(int *)calloc(n,sizeof(int));
y=(int *)calloc(n,sizeof(int));
for(i=0;i<n;i++)
x[i]=i;
for(i=0;i<n;i++) 
for(j=0;j<n;j++)
a[i][j]=rand()%md; 
ini(md);
int begin,end;
begin=clock();
M=hls(md,n,a);
for(;;)
{ 
  if(M!=0&&gcd(M,md)==1)break;
for(i=0;i<n;i++) 
for(j=0;j<n;j++)
a[i][j]=rand()%md; 
M=hls(md,n,a);
}
fp=fopen("dg.xls","w");
fprintf(fp,"%d\t%d\t\n",md,n);
for(i=0;i<n;i++) 
{for(j=0;j<n;j++)
fprintf(fp,"%d\t ",a[i][j]);
fprintf(fp,"\n");}
fclose(fp);
ini(md);
re_verse("dg.xls");
end=clock();
UpdateData(true);
m_t=end-begin;
UpdateData(false);
m_list.DeleteAllItems();  
int nColumnCount = m_list.GetHeaderCtrl()->GetItemCount();   // Delete all of the columns. 
for (i=0; i < nColumnCount; i++) {    m_list.DeleteColumn(0); }
m_list1.DeleteAllItems(); 
nColumnCount = m_list1.GetHeaderCtrl()->GetItemCount();
for (i=0; i < nColumnCount; i++) {    m_list1.DeleteColumn(0); }
m_list1.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
for(i=0;i<N;i++) 
{   sprintf(bm,"第%d列",i+1);
	m_list1.InsertColumn(i,bm,LVCFMT_LEFT,50,i);
}
for(i=0;i<N;i++)
{ m_list1.InsertItem(i,"");
	for(j=0;j<N;j++)
	{fscanf(fp,"%d",&a[i][j]);
	 sprintf(bm,"%-d",a[i][j]);
	 m_list1.SetItemText(i,j,bm);
	}
}
fclose(fp);
table=(int *)calloc(md,sizeof(int));
ini(md);
re_verse("dg.xls");
m_list.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
for(i=0;i<N;i++) 
{   sprintf(bm,"第%d列",i+1);
	m_list.InsertColumn(i,bm,LVCFMT_LEFT,50,i);
}
fp=fopen("redg.xls","r");
fscanf(fp,"%d%d",&md,&N);
for(i=0;i<N;i++)
{ m_list.InsertItem(i,"");
	for(j=0;j<N;j++)
	{fscanf(fp,"%d",&a[i][j]);
	 sprintf(bm,"%-d",a[i][j]);
	 m_list.SetItemText(i,j,bm);
	}
}
fclose(fp);
fp=fopen("dg.xls","r");
fscanf(fp,"%d%d",&md,&N);
for(i=0;i<N;i++)
	for(j=0;j<N;j++)
	fscanf(fp,"%d",&b[i][j]);
fclose(fp);
m=md;
n=N;
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
     {MessageBox("不是互逆矩阵");
  return;
      }
for(i=0;i<n;i++)
      for(j=0;j<n;j++)
            if(i!=j&&c[i][j]!=0)
                        break;
  if(i<n&&j<n)
  { MessageBox("不是互逆矩阵");
  return;
      }
MessageBox("模矩阵已成功生成");
}

void CDgDlg::OnButton2() 
{
FILE *fp;
int **a,i,j,m,n,*x,*y,sn,t; 
char bm[10],bh[1000];
char *p;
fp=fopen("dg.xls","r");
fscanf(fp,"%d%d",&m,&n);
a=(int **)calloc(n,sizeof(int *));
for(i=0;i<n;i++)
a[i]=(int *)calloc(n,sizeof(int));
x=(int *)calloc(n,sizeof(int));
y=(int *)calloc(n,sizeof(int));
for(i=0;i<n;i++) 
for(j=0;j<n;j++)
fscanf(fp,"%d",&a[i][j]);
fclose(fp);
srand(time(0));
printf("加密测试:\n");
printf("明文:");
UpdateData(true);
if(m_s1=="")
{ MessageBox("你还没有输入明文");
  return;
}
fp=fopen("xy.xls","w");

strcpy(bh,m_s1);
UpdateData(false);
   p = strtok(bh, " ");
   fprintf(fp,"%s\n",p);
 p = strtok(NULL, " ");
 while(p!=NULL)
 {    fprintf(fp,"%s\n",p);
     p = strtok(NULL, " ");
 }
 fclose(fp);
 sn=0;
fp=fopen("xy.xls","r");
fscanf(fp,"%d",&t);
while(!feof(fp))
{   if(t>=m)
{  MessageBox("元素值超出范围");
   return;
}
	x[sn]=t;
  fscanf(fp,"%d",&t);
  sn++;
}
fclose(fp);
if(sn!=n)
{MessageBox("元素个数不对");
   return;
}
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
fp=fopen("mingwen.xls","r");
fscanf(fp,"%s",bm);
UpdateData(true);
m_s1="";
while(!feof(fp))
{  m_s1+=bm;
   m_s1+=" ";
fscanf(fp,"%s",bm);
}
fclose(fp);
UpdateData(false);
fp=fopen("miwen.xls","r");
fscanf(fp,"%s",bm);
UpdateData(true);
m_s2="";
while(!feof(fp))
{  m_s2+=bm;
   m_s2+=" ";
fscanf(fp,"%s",bm);
}
fclose(fp);
UpdateData(false);
	
}

void CDgDlg::OnButton3() 
{
FILE *fp;
int **a,i,j,m,n,*x,*y; 
char bm[10];
fp=fopen("redg.xls","r");
fscanf(fp,"%d%d",&m,&n);
a=(int **)calloc(n,sizeof(int *));
for(i=0;i<n;i++)
a[i]=(int *)calloc(n,sizeof(int));
x=(int *)calloc(n,sizeof(int));
y=(int *)calloc(n,sizeof(int));
for(i=0;i<n;i++) 
for(j=0;j<n;j++)
fscanf(fp,"%d",&a[i][j]);
fclose(fp);
fp=fopen("miwen.xls","r");
for(i=0;i<n;i++) 
fscanf(fp,"%d",&x[i]);
fclose(fp);
printf("加密测试:\n");
printf("密文:");
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
printf("明文:");
for(i=0;i<n;i++)
printf("%-8d",y[i]);
printf("\n");
fp=fopen("mingwen.xls","w");
for(i=0;i<n;i++)
fprintf(fp,"%d\t",y[i]);
fprintf(fp,"\n");
fclose(fp);
for(i=0;i<n;i++)
 free(a[i]);
free(a);
free(x);
free(y);	
fp=fopen("mingwen.xls","r");
fscanf(fp,"%s",bm);
UpdateData(true);
m_s3="";
while(!feof(fp))
{  m_s3+=bm;
   m_s3+=" ";
fscanf(fp,"%s",bm);
}
fclose(fp);
UpdateData(false);	
	
}
