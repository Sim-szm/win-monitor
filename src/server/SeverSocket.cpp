// SeverSocket.cpp : implementation file
//

#include "stdafx.h"
#include "Skyeye3.h"
#include "SeverSocket.h"
#include "Skyeye3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeverSocket

CSeverSocket::CSeverSocket(CWnd* pWnd,int ix)
{
	m_pParentWnd = pWnd;
	m_idisting = ix;
}

CSeverSocket::~CSeverSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSeverSocket, CSocket)
	//{{AFX_MSG_MAP(CSeverSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSeverSocket member functions

void CSeverSocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	((CSkyeye3Dlg*)m_pParentWnd)->AddClient(m_idisting);    //将接收socket的函数放进主窗口的类中
	CSocket::OnAccept(nErrorCode);
}
