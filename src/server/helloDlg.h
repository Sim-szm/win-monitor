#if !defined(AFX_HELLODLG_H__BBE7BFE1_DCB4_45DB_8492_65E5BC1AEB73__INCLUDED_)
#define AFX_HELLODLG_H__BBE7BFE1_DCB4_45DB_8492_65E5BC1AEB73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// helloDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ChelloDlg dialog

class ChelloDlg : public CDialog
{
// Construction
public:
	ChelloDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ChelloDlg)
	enum { IDD = IDD_HELLOWORLDDIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ChelloDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ChelloDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELLODLG_H__BBE7BFE1_DCB4_45DB_8492_65E5BC1AEB73__INCLUDED_)
