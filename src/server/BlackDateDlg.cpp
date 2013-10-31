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
	//��ȡListCtrl�Ŀ��
	CRect rect;
	m_BlackListCards.GetClientRect(&rect);
	int nColInterval = rect.Width();
	
	//����ListCtrl����ʽ
	m_BlackListCards.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT  );
	m_BlackListCards.InsertColumn(0, _T("��������Ϣ"), LVCFMT_RIGHT, int(nColInterval));
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
	hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_DELETELIST) );//ɾ��
	m_del.SetBitmap(hBitmap);
	
	hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_SURE) );//ȷ��
	m_sure.SetBitmap(hBitmap);
	
	hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_ADD) );//���
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
					GetLocalTime(&Time);//��õ�ǰ����ʱ��
					historylist<<Time.wYear<<"."<<Time.wMonth<<"."<<Time.wDay<<" ";
					historylist<<Time.wHour<<":"<<Time.wMinute<<":"<<Time.wSecond;
					lines = "��"+pCur+"�Ƴ�������\n";
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
	
	CBitmap bitmap;                              //����λͼ
	bitmap.LoadBitmap(IDB_BLACKDATE);
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);
	
	CDC dcCompatible;                            //�ü���dc�󶨵�ǰdc�����ҽ�λͼ�󶨽�����dc
	dcCompatible.CreateCompatibleDC(&dc);
	dcCompatible.SelectObject(&bitmap);
	
	CRect rect;                                 //��ô��ڵĵ�ǰ�Ŀͻ���
	GetClientRect(&rect);
	
	dc.SetStretchBltMode(STRETCH_HALFTONE);     //������dc���ص�����ʾ�Ľ���  
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	// Do not call CDialog::OnPaint() for painting messages
}
