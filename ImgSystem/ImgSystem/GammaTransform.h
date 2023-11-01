#pragma once
#include "afxdialogex.h"


// GammaTransform 对话框

class GammaTransform : public CDialogEx
{
	DECLARE_DYNAMIC(GammaTransform)

public:
	GammaTransform(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~GammaTransform();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GammaTransformDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_g;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
};
