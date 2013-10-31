// ChatSocket.cpp : implementation file
//

#include "stdafx.h"
#include "Skyeye3.h"
#include "ChatSocket.h"
#include "Skyeye3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatSocket

CChatSocket::CChatSocket(CWnd* pWnd)
{
	m_pParentWnd = pWnd;
}

CChatSocket::~CChatSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CChatSocket, CSocket)
	//{{AFX_MSG_MAP(CChatSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CChatSocket member functions

void CChatSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	((CSkyeye3Dlg*)m_pParentWnd)->RecMsg(this);     //将接收消息的函数放进主窗口的类中

	CSocket::OnReceive(nErrorCode);
}

void CChatSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	((CSkyeye3Dlg*)m_pParentWnd)->DelMessage(this); 

	CSocket::OnClose(nErrorCode);
}
