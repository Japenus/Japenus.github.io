// dgDlg.h : header file
//

#if !defined(AFX_DGDLG_H__AD88E1DD_833D_4BED_81F9_3408A012795C__INCLUDED_)
#define AFX_DGDLG_H__AD88E1DD_833D_4BED_81F9_3408A012795C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDgDlg dialog

class CDgDlg : public CDialog
{
// Construction
public:
	CDgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDgDlg)
	enum { IDD = IDD_DG_DIALOG };
	CListCtrl	m_list1;
	CListCtrl	m_list;
	int		m_md;
	int		m_n;
	int		m_t;
	CString	m_s1;
	CString	m_s2;
	CString	m_s3;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DGDLG_H__AD88E1DD_833D_4BED_81F9_3408A012795C__INCLUDED_)
