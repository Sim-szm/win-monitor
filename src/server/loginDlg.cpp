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
函数名称：OnPaint()
功能描述：加载login界面的位图
作者：	  王睿琛
创建时间：2013-08-31
参数说明：无
返 回 值：无

*********************************************************************/  
void CloginDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBitmap bitmap;                                    //加载位图
	bitmap.LoadBitmap(IDB_BITMAP_LOGIN); 
	  
	BITMAP bmp;                                       //定义位图结构体   
	bitmap.GetBitmap(&bmp);                           //将bitmap的信息赋值进入结构体

	CDC dcCompatible;                                 //用兼容dc绑定当前dc，并且将位图绑定进兼容dc
	dcCompatible.CreateCompatibleDC(&dc);
	dcCompatible.SelectObject(&bitmap);

	CRect rect;                                       //获得窗口的当前的客户区
	GetClientRect(&rect);
	dc.SetStretchBltMode(STRETCH_HALFTONE);           //将获得信息的位图结构体加载进入指定的客户区
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}



/*********************************************************************
函数名称：OnInitDialog()
功能描述：初始化login界面
作者：	  王睿琛
创建时间：2013-08-31
参数说明：无
返 回 值：bool

*********************************************************************/
 
BOOL CloginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	 ChelloDlg dlgHello;         //初始化helloworld界面
   	 dlgHello.DoModal();   
	 m_editFont.CreatePointFont(180, "宋体");         //将login的输入栏字体进行改变

	 CEdit *m_editPlace=(CEdit *)GetDlgItem(IDC_PASSPORT);
     m_editPlace->SetFont(&m_editFont);

	 CEdit *m_editPlace1=(CEdit *)GetDlgItem(IDC_IDNAME);
     m_editPlace1->SetFont(&m_editFont);


	 HINSTANCE hInstance;
     HBITMAP hBitmap;
     hInstance   =   ::AfxGetInstanceHandle();
     hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_LOGIN) );//登录
     m_login.SetBitmap(hBitmap);

	 hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_QUIT) );//登录
     m_quit.SetBitmap(hBitmap);
	 //TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/*********************************************************************
函数名称：OnLogin()
功能描述：确认用户信息，进入主窗口，cbutton的响应函数
作者：	  王睿琛
创建时间：2013-08-31
参数说明：无
返 回 值：void

*********************************************************************/
void CloginDlg::OnLogin() 
{
	// TODO: Add your control notification handler code here
	CString codestr;
	CString namestr;
	GetDlgItem(IDC_IDNAME)->GetWindowText(namestr);
	GetDlgItem(IDC_PASSPORT)->GetWindowText(codestr);

	if(codestr == "abc"&& namestr == "edward")         //登入
	{
		CDialog::OnOK();
	}
	else
	{
		::MessageBox(NULL,"用户名错误或密码错误","skyeye",MB_OK);
		GetDlgItem(IDC_PASSPORT)->SetWindowText("");

	}
}




/*********************************************************************
函数名称：OnQuit()
功能描述：退出
作者：	  王睿琛
创建时间：2013-08-31
参数说明：无
返 回 值：void

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

