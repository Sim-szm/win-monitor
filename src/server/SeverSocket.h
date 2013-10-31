#if !defined(AFX_SEVERSOCKET_H__2DC1BFC6_9ECE_469A_95BA_A8F56992F8C5__INCLUDED_)
#define AFX_SEVERSOCKET_H__2DC1BFC6_9ECE_469A_95BA_A8F56992F8C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SeverSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CSeverSocket command target

class CSeverSocket : public CSocket
{
// Attributes
public:
    int m_idisting;
// Operations
public:
	CSeverSocket(CWnd* pWnd,int ix);
	virtual ~CSeverSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeverSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSeverSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CWnd* m_pParentWnd;     //CWnd类型的变量，防止头文件互相嵌套
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEVERSOCKET_H__2DC1BFC6_9ECE_469A_95BA_A8F56992F8C5__INCLUDED_)
