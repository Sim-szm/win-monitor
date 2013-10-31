#if !defined(AFX_LOGINDLG_H__1626089F_6844_49D8_9D74_4CD3E1F11D90__INCLUDED_)
#define AFX_LOGINDLG_H__1626089F_6844_49D8_9D74_4CD3E1F11D90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// loginDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CloginDlg dialog

class CloginDlg : public CDialog
{
// Construction
public:
	CloginDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CloginDlg)
	enum { IDD = IDD_DLOGINDIALOG };
	CButton	m_login;
	CButton	m_quit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CloginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CloginDlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnLogin();
	afx_msg void OnQuit();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CFont m_editFont;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDLG_H__1626089F_6844_49D8_9D74_4CD3E1F11D90__INCLUDED_)
