#if !defined(AFX_ADDBLACKDLG_H__295FB523_6228_461C_B264_9900DF3072A6__INCLUDED_)
#define AFX_ADDBLACKDLG_H__295FB523_6228_461C_B264_9900DF3072A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
#include <fstream>
// AddblackDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddblackDlg dialog

class CAddblackDlg : public CDialog
{
// Construction
public:
	CAddblackDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddblackDlg)
	enum { IDD = IDD_ADDDIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddblackDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddblackDlg)
	afx_msg void OnOkbutton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDBLACKDLG_H__295FB523_6228_461C_B264_9900DF3072A6__INCLUDED_)
