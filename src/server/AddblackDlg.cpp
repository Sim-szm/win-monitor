// AddblackDlg.cpp : implementation file
//
#include <iostream>
#include "stdafx.h"
#include "Skyeye3.h"
#include "AddblackDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddblackDlg dialog


CAddblackDlg::CAddblackDlg(CWnd* pParent /*=NULL*/)
: CDialog(CAddblackDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddblackDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAddblackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddblackDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddblackDlg, CDialog)
//{{AFX_MSG_MAP(CAddblackDlg)
ON_BN_CLICKED(IDC_OKBUTTON, OnOkbutton)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddblackDlg message handlers

void CAddblackDlg::OnOkbutton() 
{
	// TODO: Add your control notification handler code here
	CString str,str2;

	GetDlgItem(IDC_NEWBLACK)->GetWindowText(str);
	if(str !="")
	{
		std::fstream historylist;
		historylist.open("history.txt",std::ios::out|std::ios::app);

		SYSTEMTIME Time={0};
		GetLocalTime(&Time);//获得当前本地时间
		historylist<<Time.wYear<<"."<<Time.wMonth<<"."<<Time.wDay<<" ";
		historylist<<Time.wHour<<":"<<Time.wMinute<<":"<<Time.wSecond;

		str2 = "将"+str+"加入黑名单\n";
		historylist<<(LPSTR)(LPCSTR)str2;
		historylist.close();
		
		str=str+"\n";
		std::fstream inout;
		inout.open("black.txt",std::ios::in|std::ios::out|std::ios::app);
		inout<<(LPSTR)(LPCSTR)str;
		inout.close();
	}
	CDialog::OnOK(); 
	
	
}
