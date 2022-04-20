// dg.h : main header file for the DG application
//

#if !defined(AFX_DG_H__980E4B53_6A09_47CE_819A_BF2A1DAD10A4__INCLUDED_)
#define AFX_DG_H__980E4B53_6A09_47CE_819A_BF2A1DAD10A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDgApp:
// See dg.cpp for the implementation of this class
//

class CDgApp : public CWinApp
{
public:
	CDgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DG_H__980E4B53_6A09_47CE_819A_BF2A1DAD10A4__INCLUDED_)
