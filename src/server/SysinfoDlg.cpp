// SysinfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Skyeye3.h"
#include "SysinfoDlg.h"
#include "fstream"
#include "string"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSysinfoDlg dialog


CSysinfoDlg::CSysinfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSysinfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSysinfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSysinfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysinfoDlg)
	DDX_Control(pDX, IDC_SYSINFOLIST, m_sysinfolist);
	DDX_Control(pDX, IDC_DELETEALL, m_deleteall);
	DDX_Control(pDX, IDC_CURTAIN, m_curtain);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSysinfoDlg, CDialog)
	//{{AFX_MSG_MAP(CSysinfoDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_DELETEALL, OnDeleteall)
	ON_BN_CLICKED(IDC_CURTAIN, OnCurtain)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSysinfoDlg message handlers

void CSysinfoDlg::OnPaint() 
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

BOOL CSysinfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	 HINSTANCE hInstance;
     HBITMAP hBitmap;
     hInstance   =   ::AfxGetInstanceHandle();
     hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_DELETEALL) );//ɾ��
     m_deleteall.SetBitmap(hBitmap);

	 hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_SURE) );//ɾ��
     m_curtain.SetBitmap(hBitmap);

	 CRect rect;                                                                       //��ȡListCtrl�Ŀ��
	 m_sysinfolist.GetClientRect(&rect);
	 int nColInterval = rect.Width();
	
	 m_sysinfolist.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT  );    //����ListCtrl����ʽ
	
	
	 m_sysinfolist.InsertColumn(0, _T("��ʷ��¼"), LVCFMT_RIGHT, int(nColInterval));//�������������������е����ָ�ʽ���п�


	 std::string lines;
	 std::fstream inout;
   	 inout.open("history.txt",std::ios::in);
	 while(std::getline(inout,lines))
	 {
		int iItemCount = m_sysinfolist.GetItemCount();
		m_sysinfolist.InsertItem(iItemCount,"");
		m_sysinfolist.SetItemText(iItemCount,0, lines.c_str());
	 }
	 inout.close();
	 return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSysinfoDlg::OnDeleteall() 
{
	// TODO: Add your control notification handler code here
	std::fstream historylist;
	historylist.open("history.txt",std::ios::out);
	historylist.close();
	m_sysinfolist.DeleteAllItems();
}

void CSysinfoDlg::OnCurtain() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK(); 
}
