// BlackDateDlg.cpp : implementation file
//
#include <iostream>
#include <fstream>
#include <string>
#include "stdafx.h"
#include "Skyeye3.h"
#include "BlackDateDlg.h"
#include "AddblackDlg.h"
#include <Afxtempl.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlackDateDlg dialog


CBlackDateDlg::CBlackDateDlg(CWnd* pParent /*=NULL*/)
: CDialog(CBlackDateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBlackDateDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBlackDateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBlackDateDlg)
	DDX_Control(pDX, IDC_ADDBUTTON, m_add);
	DDX_Control(pDX, IDC_OKBUTTON, m_sure);
	DDX_Control(pDX, IDC_DELETEBUTTON, m_del);
	DDX_Control(pDX, IDC_BLACKLIST, m_BlackListCards);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBlackDateDlg, CDialog)
//{{AFX_MSG_MAP(CBlackDateDlg)
ON_BN_CLICKED(IDC_ADDBUTTON, OnAddbutton)
ON_BN_CLICKED(IDC_DELETEBUTTON, OnDeletebutton)
ON_BN_CLICKED(IDC_OKBUTTON, OnOkbutton)
ON_WM_PAINT()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlackDateDlg message handlers

int CBlackDateDlg::InitBlackList()
{
	//获取ListCtrl的宽度
	CRect rect;
	m_BlackListCards.GetClientRect(&rect);
	int nColInterval = rect.Width();
	
	//设置ListCtrl的样式
	m_BlackListCards.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT  );
	m_BlackListCards.InsertColumn(0, _T("黑名单信息"), LVCFMT_RIGHT, int(nColInterval));
	return 0;
}

BOOL CBlackDateDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	InitBlackList();
	std::string lines;
	std::fstream inout;
	inout.open("black.txt",std::ios::in|std::ios::out|std::ios::app);
	while(std::getline(inout,lines))
	{
		m_blacklist.AddTail(lines);
	}
	inout.close();
	POSITION pPos = m_blacklist.GetHeadPosition();
	while(pPos)
	{
		std::string pCur = m_blacklist.GetAt(pPos);
		int iItemCount = m_BlackListCards.GetItemCount();
		m_BlackListCards.InsertItem(iItemCount,"");
		m_BlackListCards.SetItemText(iItemCount,0, pCur.c_str());
		
		
		m_blacklist.GetNext(pPos);
	}
	HINSTANCE hInstance;
	HBITMAP hBitmap;
	hInstance   =   ::AfxGetInstanceHandle();
	hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_DELETELIST) );//删除
	m_del.SetBitmap(hBitmap);
	
	hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_SURE) );//确定
	m_sure.SetBitmap(hBitmap);
	
	hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_ADD) );//添加
	m_add.SetBitmap(hBitmap);
	
	//	::MessageBox(NULL,pCur.c_str(),"skyeye",MB_OK);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CBlackDateDlg::OnAddbutton() 
{
	// TODO: Add your control notification handler code here
	CAddblackDlg addDlg;
	addDlg.DoModal();
	m_BlackListCards.DeleteAllItems();
	m_blacklist.RemoveAll();
	std::string lines;
	std::fstream inout;
	inout.open("black.txt",std::ios::in|std::ios::out|std::ios::app);

	while(std::getline(inout,lines))
	{
		m_blacklist.AddTail(lines);
		int iItemCount = m_BlackListCards.GetItemCount();
		m_BlackListCards.InsertItem(iItemCount,"");
		m_BlackListCards.SetItemText(iItemCount,0, lines.c_str());
	}
	inout.close();
}

void CBlackDateDlg::OnDeletebutton() 
{
	// TODO: Add your control notification handler code here
	std::string lines;
	
	for(int i=0; i < m_BlackListCards.GetItemCount(); i++)
	{
		if(m_BlackListCards.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			int n_icount = 0;
			POSITION pPos = m_blacklist.GetHeadPosition();
			while (pPos)
			{
				if(n_icount == i)
				{ 
					
					std::string pCur = m_blacklist.GetAt(pPos);
					std::fstream historylist;
					historylist.open("history.txt",std::ios::out|std::ios::app);
					
					SYSTEMTIME Time={0};
					GetLocalTime(&Time);//获得当前本地时间
					historylist<<Time.wYear<<"."<<Time.wMonth<<"."<<Time.wDay<<" ";
					historylist<<Time.wHour<<":"<<Time.wMinute<<":"<<Time.wSecond;
					lines = "将"+pCur+"移除黑名单\n";
					historylist<<lines.c_str();
					historylist.close();
					
					m_blacklist.RemoveAt(pPos);
					
					
					break;
				}
				m_blacklist.GetNext(pPos);
				n_icount++;
			}
		}
	}
	std::fstream inout;
	inout.open("black.txt",std::ios::out);
	POSITION pPos = m_blacklist.GetHeadPosition();
	while (pPos)
	{
		std::string pCur = m_blacklist.GetAt(pPos);
		inout<<pCur+"\n";
		m_blacklist.GetNext(pPos);
	}
	inout.close();
	m_BlackListCards.DeleteAllItems();
	pPos = m_blacklist.GetHeadPosition();
	while(pPos)
	{
		std::string pCur = m_blacklist.GetAt(pPos);
		int iItemCount = m_BlackListCards.GetItemCount();
		m_BlackListCards.InsertItem(iItemCount,"");
		m_BlackListCards.SetItemText(iItemCount,0, pCur.c_str());
		
		
		m_blacklist.GetNext(pPos);
	}
}

void CBlackDateDlg::OnOkbutton() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK(); 
}

void CBlackDateDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	CBitmap bitmap;                              //加载位图
	bitmap.LoadBitmap(IDB_BLACKDATE);
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);
	
	CDC dcCompatible;                            //用兼容dc绑定当前dc，并且将位图绑定进兼容dc
	dcCompatible.CreateCompatibleDC(&dc);
	dcCompatible.SelectObject(&bitmap);
	
	CRect rect;                                 //获得窗口的当前的客户区
	GetClientRect(&rect);
	
	dc.SetStretchBltMode(STRETCH_HALFTONE);     //将兼容dc加载到所显示的界面  
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	// Do not call CDialog::OnPaint() for painting messages
}
