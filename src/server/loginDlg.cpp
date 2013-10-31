// loginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Skyeye3.h"
#include "loginDlg.h"
#include "helloDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CloginDlg dialog


CloginDlg::CloginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CloginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CloginDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CloginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CloginDlg)
	DDX_Control(pDX, IDC_LOGIN, m_login);
	DDX_Control(pDX, IDC_QUIT, m_quit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CloginDlg, CDialog)
	//{{AFX_MSG_MAP(CloginDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_LOGIN, OnLogin)
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CloginDlg message handlers




/*********************************************************************
�������ƣ�OnPaint()
��������������login�����λͼ
���ߣ�	  ����
����ʱ�䣺2013-08-31
����˵������
�� �� ֵ����

*********************************************************************/  
void CloginDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBitmap bitmap;                                    //����λͼ
	bitmap.LoadBitmap(IDB_BITMAP_LOGIN); 
	  
	BITMAP bmp;                                       //����λͼ�ṹ��   
	bitmap.GetBitmap(&bmp);                           //��bitmap����Ϣ��ֵ����ṹ��

	CDC dcCompatible;                                 //�ü���dc�󶨵�ǰdc�����ҽ�λͼ�󶨽�����dc
	dcCompatible.CreateCompatibleDC(&dc);
	dcCompatible.SelectObject(&bitmap);

	CRect rect;                                       //��ô��ڵĵ�ǰ�Ŀͻ���
	GetClientRect(&rect);
	dc.SetStretchBltMode(STRETCH_HALFTONE);           //�������Ϣ��λͼ�ṹ����ؽ���ָ���Ŀͻ���
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}



/*********************************************************************
�������ƣ�OnInitDialog()
������������ʼ��login����
���ߣ�	  ����
����ʱ�䣺2013-08-31
����˵������
�� �� ֵ��bool

*********************************************************************/
 
BOOL CloginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	 ChelloDlg dlgHello;         //��ʼ��helloworld����
   	 dlgHello.DoModal();   
	 m_editFont.CreatePointFont(180, "����");         //��login��������������иı�

	 CEdit *m_editPlace=(CEdit *)GetDlgItem(IDC_PASSPORT);
     m_editPlace->SetFont(&m_editFont);

	 CEdit *m_editPlace1=(CEdit *)GetDlgItem(IDC_IDNAME);
     m_editPlace1->SetFont(&m_editFont);


	 HINSTANCE hInstance;
     HBITMAP hBitmap;
     hInstance   =   ::AfxGetInstanceHandle();
     hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_LOGIN) );//��¼
     m_login.SetBitmap(hBitmap);

	 hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_QUIT) );//��¼
     m_quit.SetBitmap(hBitmap);
	 //TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/*********************************************************************
�������ƣ�OnLogin()
����������ȷ���û���Ϣ�����������ڣ�cbutton����Ӧ����
���ߣ�	  ����
����ʱ�䣺2013-08-31
����˵������
�� �� ֵ��void

*********************************************************************/
void CloginDlg::OnLogin() 
{
	// TODO: Add your control notification handler code here
	CString codestr;
	CString namestr;
	GetDlgItem(IDC_IDNAME)->GetWindowText(namestr);
	GetDlgItem(IDC_PASSPORT)->GetWindowText(codestr);

	if(codestr == "abc"&& namestr == "edward")         //����
	{
		CDialog::OnOK();
	}
	else
	{
		::MessageBox(NULL,"�û���������������","skyeye",MB_OK);
		GetDlgItem(IDC_PASSPORT)->SetWindowText("");

	}
}




/*********************************************************************
�������ƣ�OnQuit()
�����������˳�
���ߣ�	  ����
����ʱ�䣺2013-08-31
����˵������
�� �� ֵ��void

*********************************************************************/
void CloginDlg::OnQuit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel(); 
}

void CloginDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x, point.y));
	CDialog::OnLButtonDown(nFlags, point);
}

