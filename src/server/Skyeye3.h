// Skyeye3.h : main header file for the SKYEYE3 application
//

#if !defined(AFX_SKYEYE3_H__BFF45DF1_B866_46DF_9C74_C47993252184__INCLUDED_)
#define AFX_SKYEYE3_H__BFF45DF1_B866_46DF_9C74_C47993252184__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSkyeye3App:
// See Skyeye3.cpp for the implementation of this class
//

class CSkyeye3App : public CWinApp
{
public:
	CSkyeye3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkyeye3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSkyeye3App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKYEYE3_H__BFF45DF1_B866_46DF_9C74_C47993252184__INCLUDED_)
