
// ImgSystemDlg.h: 头文件
//
#include"CImgProcessing.h"
#include"LogTransformDlg.h"
#include"GammaTransform.h"
#include"ShapeProcess.h"
#pragma once
// CImgSystemDlg 对话框
class CImgSystemDlg : public CDialogEx
{
// 构造
public:
	CImgSystemDlg(CWnd* pParent = nullptr);	// 标准构造函数
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMGSYSTEM_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_p1;
	CStatic m_p2;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	Mat src, dst;
	CImgProcessing CIP;
	ShapeProcess SP;
	afx_msg void OnRGB_to_Gray();
	void ShowDst();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnEqualHist();
	afx_msg void OnLinearTransform();
	afx_msg void OnLogTransform();
	afx_msg void OnGammaTransform();
	afx_msg void OnImgErosion();
	afx_msg void OnDilation();
	afx_msg void OnThresholding();
	afx_msg void OnAdaptiveThresholding();
	afx_msg void OnRegionGrowing();
	afx_msg void OnEdgeDetectSobel();
	afx_msg void OnEdgeDetectCanny();
	afx_msg void OnMeanFiltering();
	afx_msg void OnMediumFilter();
	afx_msg void OnGaussFilter();
	afx_msg void OnDetectFace();
	afx_msg void OnBnClickedButton2();
};