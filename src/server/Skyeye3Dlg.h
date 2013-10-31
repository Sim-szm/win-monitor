// Skyeye3Dlg.h : header file
//

#if !defined(AFX_SKYEYE3DLG_H__51ACF41B_BACB_4E53_8214_671256B93080__INCLUDED_)
#define AFX_SKYEYE3DLG_H__51ACF41B_BACB_4E53_8214_671256B93080__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "ChatSocket.h"
#include "SeverSocket.h"
#include <Afxtempl.h>
#include <string>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
// CSkyeye3Dlg dialog



/************************************************

Struct name: Info
Create by：王睿琛
CreateDate：2013-09-01
Explain：硬件信息存储
Change by: 2011-06-03 by 周伟 

************************************************/   
typedef struct Info
{
	int flag ;
	char m_stProcessorType[30];//CPU型号:m_stProcessorType
	char m_stwProcessorArchitecture[30];//CPU的体系结构 :m_stwProcessorArchitecture)
	DWORD  m_dwOemId;//OEM ID :sysInfo.dwOemId
	DWORD  m_dwProcessorType;//process type :sysInfo.dwProcessorType
	DWORD  dwNumberOfProcessors;//number of process :sysInfo.dwNumberOfProcessors
	DWORD  dwMaxClockSpeed;//CPU主频:
	char vername[50];//系统名：vername
	DWORD dwMajorVersion;                 //系统主版本号  
    DWORD dwMinorVersion;                 //系统次版本号 
	TCHAR szCSDVersion[128];
    DWORD dwBuildNumber;                 //系统构建号  
    DWORD dwPlatformId;                  //当前系统的支持的平台号： 
	char ComputerName[MAX_COMPUTERNAME_LENGTH];//计算机名称;
	int memory_already_use;
	long memory_total;
	long memory_for_free;
	char m_Netowrk_Adapter[2048];       //网卡信息
}HARD_INFO;


typedef struct Net{
	int flag;
	float m_Final_Send;
	float m_Final_Recv;
}NetFlux;

typedef struct process{
	char PROCESS_NAME[30];
	unsigned int PROCESS_ID;
}PROCESS_INFO;

typedef struct totalInfo
{
	CString peop_Ip;
	CChatSocket *m_Socket;
	CChatSocket *m_SSocket;
	struct Info pep_Info;
	PROCESS_INFO pep_proc[200];
	NetFlux net_stream;

}TOTAL_INFO;

typedef struct infor{
	int flag;
	PROCESS_INFO m_pop[200];
}Final_Info;






class CSkyeye3Dlg : public CDialog
{
// Construction
public:
	void DelMessage(CChatSocket* pSocket);
	int RefreshListCtrlData(TOTAL_INFO pCur);
	void RecMsg(CChatSocket* pSocket);
	void AddClient(int ix);
	CSkyeye3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSkyeye3Dlg)
	enum { IDD = IDD_SKYEYE3_DIALOG };
	CButton	m_mini;
	CButton	m_close;
	CButton	m_delete;
	CButton	m_about_us;
	CButton	m_blackdate;
	CButton	m_sysdate;
	CButton	m_info;
	CButton	m_title;
	CListCtrl	m_listActiveCards;
	CTreeCtrl	m_treeCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkyeye3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CChatSocket *m_pChatSocket;                         //接受信息的socket
	CChatSocket *m_pChatListScoket;                     //发送信息的socket
	CList<TOTAL_INFO,TOTAL_INFO&> m_peopInfo;           //存取所有用户信息的容器
	TOTAL_INFO m_pepIP_Info;                            //存取单用户的结构体
	CSeverSocket *m_pSeverSocket;                       //监听用户的套接字
	CSeverSocket *m_pSeverlistSocket;                   //监听用户的套接字

	// Generated message map functions
	//{{AFX_MSG(CSkyeye3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnMini();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClickInfotree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAboutUs();
	afx_msg void OnInfo();
	afx_msg void OnDelete();
	afx_msg void OnBlackdate();
	afx_msg void OnTitle();
	afx_msg void OnSysdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int InitListCtrlStyle();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKYEYE3DLG_H__51ACF41B_BACB_4E53_8214_671256B93080__INCLUDED_)
