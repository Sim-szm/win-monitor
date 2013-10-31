// helloDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Skyeye3.h"
#include "helloDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ChelloDlg dialog


ChelloDlg::ChelloDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ChelloDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ChelloDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ChelloDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ChelloDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ChelloDlg, CDialog)
	//{{AFX_MSG_MAP(ChelloDlg)
	ON_WM_TIMER()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ChelloDlg message handlers
/*********************************************************************
函数名称：OnInitDialog()
功能描述：初始化helloworld界面
作者：	  王睿琛
创建时间：2013-08-31
参数说明：无
返 回 值：bool

*********************************************************************/
BOOL ChelloDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetTimer(1,3000,NULL);      //设置等待时间
	// TODO: Add extra initialization here

//	ChelloDlg dlgHello;         //初始化helloworld界面
//	dlgHello.DoModal();    
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



/*********************************************************************
函数名称：OnTimer()
功能描述：用于实现定时控制功能
作者：	  王睿琛
创建时间：2013-08-31
参数说明：UINT nIDEvent
返 回 值：void

*********************************************************************/

void ChelloDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnCancel();                         //退出
	CDialog::OnTimer(nIDEvent);
}



/*********************************************************************
函数名称：OnPaint()
功能描述：加载helloworld界面的位图
作者：	  王睿琛
创建时间：2013-08-31
参数说明：无
返 回 值：无

*********************************************************************/   


void ChelloDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CBitmap bitmap;                              //加载位图
	bitmap.LoadBitmap(IDB_BITMAP_START1);
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);

	CDC dcCompatible;                            //用兼容dc绑定当前dc，并且将位图绑定进兼容dc
	dcCompatible.CreateCompatibleDC(&dc);
	dcCompatible.SelectObject(&bitmap);

	CRect rect;                                 //获得窗口的当前的客户区
	GetClientRect(&rect);

	dc.SetStretchBltMode(STRETCH_HALFTONE);     //将兼容dc加载到所显示的界面  
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}
