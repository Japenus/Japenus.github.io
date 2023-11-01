// GammaTransform.cpp: 实现文件
//

#include "pch.h"
#include "ImgSystem.h"
#include "afxdialogex.h"
#include "GammaTransform.h"


// GammaTransform 对话框

IMPLEMENT_DYNAMIC(GammaTransform, CDialogEx)

GammaTransform::GammaTransform(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GammaTransformDlg, pParent)
	, m_g(0)
{

}

GammaTransform::~GammaTransform()
{
}

void GammaTransform::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_g);
}


BEGIN_MESSAGE_MAP(GammaTransform, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &GammaTransform::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &GammaTransform::OnBnClickedOk)
END_MESSAGE_MAP()


// GammaTransform 消息处理程序


void GammaTransform::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}


void GammaTransform::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
