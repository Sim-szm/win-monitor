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
�������ƣ�OnInitDialog()
������������ʼ��helloworld����
���ߣ�	  ����
����ʱ�䣺2013-08-31
����˵������
�� �� ֵ��bool

*********************************************************************/
BOOL ChelloDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetTimer(1,3000,NULL);      //���õȴ�ʱ��
	// TODO: Add extra initialization here

//	ChelloDlg dlgHello;         //��ʼ��helloworld����
//	dlgHello.DoModal();    
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



/*********************************************************************
�������ƣ�OnTimer()
��������������ʵ�ֶ�ʱ���ƹ���
���ߣ�	  ����
����ʱ�䣺2013-08-31
����˵����UINT nIDEvent
�� �� ֵ��void

*********************************************************************/

void ChelloDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnCancel();                         //�˳�
	CDialog::OnTimer(nIDEvent);
}



/*********************************************************************
�������ƣ�OnPaint()
��������������helloworld�����λͼ
���ߣ�	  ����
����ʱ�䣺2013-08-31
����˵������
�� �� ֵ����

*********************************************************************/   


void ChelloDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CBitmap bitmap;                              //����λͼ
	bitmap.LoadBitmap(IDB_BITMAP_START1);
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);

	CDC dcCompatible;                            //�ü���dc�󶨵�ǰdc�����ҽ�λͼ�󶨽�����dc
	dcCompatible.CreateCompatibleDC(&dc);
	dcCompatible.SelectObject(&bitmap);

	CRect rect;                                 //��ô��ڵĵ�ǰ�Ŀͻ���
	GetClientRect(&rect);

	dc.SetStretchBltMode(STRETCH_HALFTONE);     //������dc���ص�����ʾ�Ľ���  
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}
