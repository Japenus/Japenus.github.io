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
	m_md = 0;
	m_n = 0;
	m_t = 0;
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
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDgDlg, CDialog)
	//{{AFX_MSG_MAP(CDgDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDgDlg message handlers

BOOL CDgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
::SetWindowPos(this->m_hWnd,HWND_BOTTOM,0,0,600,400,SWP_NOZORDER);
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
int **a,**b,**c,mat,i,j,k,n,m;
int *x,*y; 
char bm[10];
int begin,end;
begin=clock();
UpdateData(true);
m=m_md;
n=m_n;
UpdateData(false);
if(m<2)
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
fp=fopen("dg.xls","w");
fprintf(fp,"%d\t%d\t\n",m,n);
for(i=0;i<n;i++) 
{for(j=0;j<n;j++)
fprintf(fp,"%d\t ",a[i][j]);
fprintf(fp,"\n");}
fclose(fp);
re_verse("dg.xls");
fp=fopen("redg.xls","r");
fscanf(fp,"%d%d",&m,&n);
for(i=0;i<n;i++) 
for(j=0;j<n;j++)
fscanf(fp,"%d",&b[i][j]);
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
MessageBox("互逆矩阵成功生成");
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
for(i=0;i<n;i++) 
{   sprintf(bm,"第%d列",i+1);
	m_list1.InsertColumn(i,bm,LVCFMT_LEFT,50,i);
}
for(i=0;i<n;i++)
{ m_list1.InsertItem(i,"");
	for(j=0;j<n;j++)
	{
	 sprintf(bm,"%-d",a[i][j]);
	 m_list1.SetItemText(i,j,bm);
	}
}
m_list.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
for(i=0;i<n;i++) 
{   sprintf(bm,"第%d列",i+1);
	m_list.InsertColumn(i,bm,LVCFMT_LEFT,50,i);
}
for(i=0;i<n;i++)
{ m_list.InsertItem(i,"");
	for(j=0;j<n;j++)
	{
	 sprintf(bm,"%-d",b[i][j]);
	 m_list.SetItemText(i,j,bm);
	}
}
for(i=0;i<n;i++)
   free(a[i]);
   free(a);
for(i=0;i<n;i++)
   free(b[i]);
   free(b);
for(i=0;i<n;i++)
   free(c[i]);
   free(c);
   free(x);
   free(y);
   free(table);
}
