// AboutUsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Skyeye3.h"
#include "AboutUsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutUsDlg dialog


CAboutUsDlg::CAboutUsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutUsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutUsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAboutUsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutUsDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutUsDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutUsDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutUsDlg message handlers
