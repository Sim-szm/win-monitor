#if !defined(AFX_SYSINFODLG_H__58911B60_6E6B_436E_A1F7_EA2C92E74D09__INCLUDED_)
#define AFX_SYSINFODLG_H__58911B60_6E6B_436E_A1F7_EA2C92E74D09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SysinfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSysinfoDlg dialog

class CSysinfoDlg : public CDialog
{
// Construction
public:
	CSysinfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSysinfoDlg)
	enum { IDD = IDD_SYSINFODIALOG };
	CListCtrl	m_sysinfolist;
	CButton	m_deleteall;
	CButton	m_curtain;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysinfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSysinfoDlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnDeleteall();
	afx_msg void OnCurtain();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSINFODLG_H__58911B60_6E6B_436E_A1F7_EA2C92E74D09__INCLUDED_)
