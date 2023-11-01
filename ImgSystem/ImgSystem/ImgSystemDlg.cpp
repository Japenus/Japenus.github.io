
// ImgSystemDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ImgSystem.h"
#include "ImgSystemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CImgSystemDlg 对话框



CImgSystemDlg::CImgSystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMGSYSTEM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImgSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_pic1, m_p1);
	DDX_Control(pDX, IDC_pic2, m_p2);
}

BEGIN_MESSAGE_MAP(CImgSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CImgSystemDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CImgSystemDlg::OnBnClickedButton1)
	ON_COMMAND(ID_32771, &CImgSystemDlg::OnRGB_to_Gray)
	ON_BN_CLICKED(IDC_BUTTON4, &CImgSystemDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CImgSystemDlg::OnBnClickedButton5)
	ON_COMMAND(ID_32772, &CImgSystemDlg::OnEqualHist)
	ON_COMMAND(ID_32785, &CImgSystemDlg::OnLinearTransform)
	ON_COMMAND(ID_32786, &CImgSystemDlg::OnLogTransform)
	ON_COMMAND(ID_32787, &CImgSystemDlg::OnGammaTransform)
	ON_COMMAND(ID_32788, &CImgSystemDlg::OnImgErosion)
	ON_COMMAND(ID_32789, &CImgSystemDlg::OnDilation)
	ON_COMMAND(ID_32793, &CImgSystemDlg::OnThresholding)
	ON_COMMAND(ID_32794, &CImgSystemDlg::OnAdaptiveThresholding)
	ON_COMMAND(ID_32791, &CImgSystemDlg::OnRegionGrowing)
	ON_COMMAND(ID_32795, &CImgSystemDlg::OnEdgeDetectSobel)
	ON_COMMAND(ID_32796, &CImgSystemDlg::OnEdgeDetectCanny)
	ON_COMMAND(ID_32797, &CImgSystemDlg::OnMeanFiltering)
	ON_COMMAND(ID_32798, &CImgSystemDlg::OnMediumFilter)
	ON_COMMAND(ID_32799, &CImgSystemDlg::OnGaussFilter)
	ON_COMMAND(ID_32800, &CImgSystemDlg::OnDetectFace)
	ON_BN_CLICKED(IDC_BUTTON2, &CImgSystemDlg::OnBnClickedButton2)
END_MESSAGE_MAP()
// CImgSystemDlg 消息处理程序

BOOL CImgSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CImgSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CImgSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CImgSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CImgSystemDlg::OnBnClickedButton3()
{
	//退出系统事件处理函数
	UINT s;
	s = MessageBox(_T("确定要退出吗？"), _T("提示"), MB_YESNO | MB_ICONQUESTION);
	if (s == IDYES) {
		exit(0);
	}
}

void CImgSystemDlg::OnBnClickedButton1()
{
	//按下打开图片按钮时的消息处理函数
	CString path;
	TCHAR szFilter[] = _T("JPEG文件(*.jpg)|*.jpg|png文件(*.png)|*.png|bmp文件(*.bmp)|*.bmp||");
	CFileDialog fileDlg(TRUE, _T("jpg"), NULL, 0, szFilter, this);
	if (fileDlg.DoModal() != IDOK) {
		return;
	}
	path = fileDlg.GetPathName();
	CImage img;
	img.Load(path);
	CRect rectControl;
	m_p1.GetClientRect(rectControl);
	CDC* pDc = m_p1.GetDC();
	img.Draw(pDc->m_hDC, rectControl);
	img.Destroy();
	m_p1.ReleaseDC(pDc);
	src=imread(path.GetBuffer());
}
void CImgSystemDlg::OnBnClickedButton4()
{
	// 显示原图像灰度直方图
	CIP.ShowHistogram(src);
}

void CImgSystemDlg::OnBnClickedButton5()
{
	//显示处理后的图像灰度直方图
	dst = imread("output.png");
	CIP.ShowHistogram(dst);
	ShowDst();
}
void CImgSystemDlg::OnRGB_to_Gray()
{
	// 触发灰度化处理函数输出图像并显示
	dst = CIP.RGB_to_Gray(src);
	imwrite("output.png", dst);
	ShowDst();
}

void CImgSystemDlg::OnEqualHist()
{
	// 均衡化消息处理函数
	dst = CIP.HistEqual(src);
	imwrite("output.png", dst);
	ShowDst();
}

void CImgSystemDlg::OnLinearTransform()
{
	// 灰度变换-线性变换
	dst = CIP.linearTransform(src);
	imwrite("output.png", dst);
	ShowDst();
}

void CImgSystemDlg::ShowDst()
{
	//处理后的图像进行展示
	CImage img;
	img.Load(TEXT("output.png"));
	CRect rectControl;
	m_p2.GetClientRect(rectControl);
	CDC* pDc = m_p2.GetDC();
	img.Draw(pDc->m_hDC, rectControl);
	img.Destroy();
	m_p2.ReleaseDC(pDc);
}

void CImgSystemDlg::OnLogTransform()
{
	//对数变换，弹出缩放参数对话框
	double c=30.5;
	LogTransformDlg LTD;
	LTD.m_c = c;
	if (LTD.DoModal() == IDOK) {
		c = LTD.m_c;
	}
	dst = CIP.logTransform(src,c);
	imwrite("output.png", dst);
	ShowDst();
}

void CImgSystemDlg::OnGammaTransform()
{
	// TODO: 在此添加命令处理程序代码
	float k = 0.9;
	GammaTransform GTH;
	GTH.m_g = k;
	if (GTH.DoModal() == IDOK) {
		k = GTH.m_g;
	}
	dst = CIP.gammaTransform(src,k);
	imwrite("output.png", dst);
	ShowDst();
}

void CImgSystemDlg::OnImgErosion()
{
	// TODO: 在此添加命令处理程序代码
	dst = SP.Imgerosion(src);
	imwrite("output.png", dst);
	ShowDst();
}

void CImgSystemDlg::OnDilation()
{
	// TODO: 在此添加命令处理程序代码
	dst = SP.dilation(src);
	imwrite("output.png", dst);
	ShowDst();
}

void CImgSystemDlg::OnThresholding()
{
	// TODO: 在此添加命令处理程序代码
	int para = 50;
	dst = CIP.thresholding(src,para);
	imwrite("output.png", dst);
	ShowDst();
}

void CImgSystemDlg::OnAdaptiveThresholding()
{
	// TODO: 在此添加命令处理程序代码
	int blocksize = 15;
	double c=2.0;
	dst = CIP.adaptiveThresholding(src,blocksize,c);
	imwrite("output.png", dst);
	ShowDst();
}

void CImgSystemDlg::OnRegionGrowing()
{
	//图像区域生长
	Mat region = Mat::zeros(src.size(), CV_8UC1);
	int seedX = 100;
	int seedY = 100;
	int threshold = 70;
	CIP.regionGrowing(src,region,seedX,seedY,threshold);
	imwrite("output.png", region);
	ShowDst();
}


void CImgSystemDlg::OnEdgeDetectSobel()
{
	// TODO: 在此添加命令处理程序代码
	dst = CIP.EdgeDetectSobel(src);
	imwrite("output.png", dst);
	ShowDst();
}


void CImgSystemDlg::OnEdgeDetectCanny()
{
	dst = CIP.EdgeDetectCanny(src);
	imwrite("output.png", dst);
	ShowDst();
}


void CImgSystemDlg::OnMeanFiltering()
{
	// TODO: 在此添加命令处理程序代码
	dst = CIP.MeanFiltering(src);
	imwrite("output.png", dst);
	ShowDst();
}


void CImgSystemDlg::OnMediumFilter()
{
	// TODO: 在此添加命令处理程序代码
	dst = CIP.MediumFilter(src);
	imwrite("output.png", dst);
	ShowDst();
}


void CImgSystemDlg::OnGaussFilter()
{
	// TODO: 在此添加命令处理程序代码
	dst = CIP.GaussFilter(src);
	imwrite("output.png", dst);
	ShowDst();
}


void CImgSystemDlg::OnDetectFace()
{
	// TODO: 在此添加命令处理程序代码
	CIP.DetectFace();
}


void CImgSystemDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//保存picture control控件的图片,   参数ID是picture control控件ID号
		CWnd* bmpShow = GetDlgItem(IDC_pic2);
		CDC* pdc = bmpShow->GetDC();
		CImage  imag;
		CRect rect;

		GetClientRect(&rect);        //获取画布大小
		bmpShow->GetWindowRect(&rect);
		imag.Create(rect.Width(), rect.Height(), 32);
		::BitBlt(imag.GetDC(), 0, 0, rect.Width(), rect.Height(), pdc->m_hDC, 0, 0, SRCCOPY);

		TCHAR szFilter[] = _T("jpg file(*.jpg)|*.jpg|bmp file(*.bmp)|*.bmp|所有文件(*.*)|*.*||");  //文件格式过滤
		// 构造保存文件对话框    
		CFileDialog fileDlg(FALSE, _T("jpg"), _T("*.jpg"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
		fileDlg.m_ofn.lpstrTitle = _T("保存直方图");  //保存对话窗口标题名
		CString picturePath;
		if (IDOK == fileDlg.DoModal())  //按下确认键
		{
			picturePath = fileDlg.GetPathName();  //文件路径
		}

		HRESULT hResult = imag.Save(picturePath); //保存图片
		ReleaseDC(pdc);
		imag.ReleaseDC();
}
