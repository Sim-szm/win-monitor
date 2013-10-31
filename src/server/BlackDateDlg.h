#if !defined(AFX_BLACKDATEDLG_H__472F5401_AE2A_4152_B259_70A5EA811272__INCLUDED_)
#define AFX_BLACKDATEDLG_H__472F5401_AE2A_4152_B259_70A5EA811272__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
#include <fstream>
#include <Afxtempl.h>
// BlackDateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBlackDateDlg dialog

class CBlackDateDlg : public CDialog
{
// Construction
public:
	CBlackDateDlg(CWnd* pParent = NULL);   // standard constructor
	CList<std::string,std::string&> m_blacklist;

// Dialog Data
	//{{AFX_DATA(CBlackDateDlg)
	enum { IDD = IDD_BLACKDATEDIALOG };
	CButton	m_add;
	CButton	m_sure;
	CButton	m_del;
	CListCtrl	m_BlackListCards;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlackDateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBlackDateDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddbutton();
	afx_msg void OnDeletebutton();
	afx_msg void OnOkbutton();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int InitBlackList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLACKDATEDLG_H__472F5401_AE2A_4152_B259_70A5EA811272__INCLUDED_)
