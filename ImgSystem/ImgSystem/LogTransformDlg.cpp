// LogTransformDlg.cpp: 实现文件
//

#include "pch.h"
#include "ImgSystem.h"
#include "afxdialogex.h"
#include "LogTransformDlg.h"


// LogTransformDlg 对话框

IMPLEMENT_DYNAMIC(LogTransformDlg, CDialogEx)

LogTransformDlg::LogTransformDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LogTransformDlg, pParent)
	, m_c(0)
{

}

LogTransformDlg::~LogTransformDlg()
{
}

void LogTransformDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_c);
}


BEGIN_MESSAGE_MAP(LogTransformDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &LogTransformDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// LogTransformDlg 消息处理程序

void LogTransformDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
