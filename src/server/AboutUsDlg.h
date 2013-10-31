#if !defined(AFX_ABOUTUSDLG_H__A257482E_1A2E_49DF_8694_51FBA69D3C71__INCLUDED_)
#define AFX_ABOUTUSDLG_H__A257482E_1A2E_49DF_8694_51FBA69D3C71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AboutUsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAboutUsDlg dialog

class CAboutUsDlg : public CDialog
{
// Construction
public:
	CAboutUsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAboutUsDlg)
	enum { IDD = IDD_ABOUTUSDIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutUsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAboutUsDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUTUSDLG_H__A257482E_1A2E_49DF_8694_51FBA69D3C71__INCLUDED_)
