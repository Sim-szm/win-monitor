// Skyeye3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include <windows.h>
#include "Skyeye3.h"
#include "Skyeye3Dlg.h"
#include "ChatSocket.h"
#include "SeverSocket.h"
#include "BlackDateDlg.h"
#include "SysinfoDlg.h"
#include "AboutUsDlg.h"
#include "fstream"
#include "string"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkyeye3Dlg dialog

CSkyeye3Dlg::CSkyeye3Dlg(CWnd* pParent /*=NULL*/)
: CDialog(CSkyeye3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSkyeye3Dlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pSeverSocket = NULL;
	m_pSeverlistSocket = NULL;
}

void CSkyeye3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkyeye3Dlg)
	DDX_Control(pDX, IDC_MINI, m_mini);
	DDX_Control(pDX, IDC_CLOSE, m_close);
	DDX_Control(pDX, IDC_DELETE, m_delete);
	DDX_Control(pDX, IDC_ABOUT_US, m_about_us);
	DDX_Control(pDX, IDC_BLACKDATE, m_blackdate);
	DDX_Control(pDX, IDC_SYSDATE, m_sysdate);
	DDX_Control(pDX, IDC_INFO, m_info);
	DDX_Control(pDX, IDC_TITLE, m_title);
	DDX_Control(pDX, IDC_PROCLIST, m_listActiveCards);
	DDX_Control(pDX, IDC_INFOTREE, m_treeCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSkyeye3Dlg, CDialog)
//{{AFX_MSG_MAP(CSkyeye3Dlg)
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_CLOSE, OnClose)
ON_BN_CLICKED(IDC_MINI, OnMini)
ON_WM_LBUTTONDOWN()
ON_WM_CTLCOLOR()
ON_NOTIFY(NM_CLICK, IDC_INFOTREE, OnClickInfotree)
ON_BN_CLICKED(IDC_ABOUT_US, OnAboutUs)
ON_BN_CLICKED(IDC_INFO, OnInfo)
ON_BN_CLICKED(IDC_DELETE, OnDelete)
ON_BN_CLICKED(IDC_BLACKDATE, OnBlackdate)
ON_BN_CLICKED(IDC_TITLE, OnTitle)
ON_BN_CLICKED(IDC_SYSDATE, OnSysdate)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkyeye3Dlg message handlers

BOOL CSkyeye3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	
	
	CWnd *pWnd;
	pWnd  =  GetDlgItem(IDC_INFOTREE);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_PROCLIST);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_IPNAME);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_IP);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_USER);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_CPUINFO);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_CPU);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_SYSINFO);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_SYS);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_USERNAME);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_DELETE);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_NETWORK);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_NET);
	pWnd->ShowWindow(SW_HIDE);
	if(NULL == m_pSeverSocket)                          //  �������ܿͻ��˵�socket
		m_pSeverSocket = new CSeverSocket(this,1);  
	m_pSeverSocket->Create(1234);                       //�����˿�
	if(!m_pSeverSocket->Listen(10))                     //���� 
		::AfxMessageBox("����ʧ�ܣ�");
	
	
	InitListCtrlStyle();	//��ʼ��ListCtrl����ʽ
	//	RefreshListCtrlData(TOTAL_INFO pCur);
	
	if(  NULL == m_pSeverlistSocket )                   //  �������ܿͻ��˵�socket
		m_pSeverlistSocket = new CSeverSocket(this,2); 
	
	if(  m_pSeverlistSocket->Create(8000) == NULL  )    //�����˿�
	{ 
		delete m_pSeverlistSocket;
		m_pSeverlistSocket = NULL;
		::AfxMessageBox("��ʧ��!");
	}
	
	if(!m_pSeverlistSocket->Listen(10))                 //����
		::AfxMessageBox("����ʧ�ܣ�");
	
	
	HINSTANCE hInstance;
	HBITMAP hBitmap;
	hInstance   =   ::AfxGetInstanceHandle();
	hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_TITLEBITMAP) );//��ҳ
	m_title.SetBitmap(hBitmap);
	
	hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_INFOBITMAP) );//�û�
	m_info.SetBitmap(hBitmap);
	
	hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_SYSDATE) );  //ϵͳ��־
	m_sysdate.SetBitmap(hBitmap);
	
	
	hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BLACK) );  //ϵͳ��־
	m_blackdate.SetBitmap(hBitmap);
	
	hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_ABOUT_US) );  //ϵͳ��־
	m_about_us.SetBitmap(hBitmap);
	
	hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_DELETPROCBITMAP) );  //ϵͳ��־
	m_delete.SetBitmap(hBitmap);
	
	
	hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_CLOSEBITMAP) );  //�ر�
	m_close.SetBitmap(hBitmap);
	
	hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_MINIBITMAP) );  //�ر�
	m_mini.SetBitmap(hBitmap);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSkyeye3Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_MAJORBITMAP);
		BITMAP bmp;
		bitmap.GetBitmap(&bmp);
		
		CDC dcCompatible;
		dcCompatible.CreateCompatibleDC(&dc);
		dcCompatible.SelectObject(&bitmap);
		CRect rect;
		GetClientRect(&rect);
		dc.SetStretchBltMode(STRETCH_HALFTONE);
		dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSkyeye3Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


/*********************************************************************
�������ƣ�OnClose()
�����������˳�����
���ߣ�	  ����
����ʱ�䣺2013-08-31
����˵������
�� �� ֵ����

*********************************************************************/  
void CSkyeye3Dlg::OnClose() 
{
	// TODO: Add your control notification handler code here
	//DestroyWindow();
	CDialog::OnOK(); 
}



/*********************************************************************
�������ƣ�OnMini()
������������С��
���ߣ�	  ����
����ʱ�䣺2013-08-31
����˵������
�� �� ֵ����

*********************************************************************/
void CSkyeye3Dlg::OnMini() 
{
	// TODO: Add your control notification handler code here
	CloseWindow();
}
/*********************************************************************
�������ƣ�OnLButtonDown
������������С��
���ߣ�	  ����
����ʱ�䣺2013-08-31
����˵����UINT nFlags, CPoint point
�� �� ֵ����

*********************************************************************/
void CSkyeye3Dlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x, point.y));
	CDialog::OnLButtonDown(nFlags, point);
}



/*********************************************************************
�������ƣ�AddClient
�����������������ӿͻ���
���ߣ�	  ����
����ʱ�䣺2013-08-31
����˵����int ix
�� �� ֵ����

*********************************************************************/
void CSkyeye3Dlg::AddClient(int ix)
{
	UINT nPort,nPort1;
	CString szIP,szIP1;
    if(ix == 1)
	{
		m_pChatSocket = new CChatSocket(this);
		m_pSeverSocket->Accept(*m_pChatSocket);
		m_pChatSocket->GetPeerName(szIP, nPort);//��ȡ�ͻ��˵�IP,�˿�
		if(m_peopInfo.GetCount() != 0)
		{
			POSITION pPos = m_peopInfo.GetHeadPosition();
			
			int socket_flag = 0;
			while(pPos)
			{
				TOTAL_INFO pCur = m_peopInfo.GetAt(pPos);
				if(pCur.peop_Ip == szIP)
				{
					socket_flag = 1;
					
					::MessageBox(NULL,"can not two windows","ak",MB_OK);
					break;
				}
				m_peopInfo.GetNext(pPos);
			}
			if(socket_flag == 0)
			{
				m_pepIP_Info.m_Socket = m_pChatSocket;//��socket����Ip_port�ṹ����
				m_pepIP_Info.peop_Ip = szIP;
				m_peopInfo.AddTail(m_pepIP_Info);
				
			}
		}
		else 
		{
			m_pepIP_Info.m_Socket = m_pChatSocket;//��socket����Ip_port�ṹ����
			m_pepIP_Info.peop_Ip = szIP;
			//POSITION pPos = m_peopInfo.GetHeadPosition();
			m_peopInfo.AddTail(m_pepIP_Info);
		}
	}
	
	if(ix == 2)
	{
		m_pChatListScoket = new CChatSocket(this);
		m_pSeverlistSocket->Accept(*m_pChatListScoket);
		m_pChatListScoket->GetPeerName(szIP1,nPort1);
		POSITION pPos = m_peopInfo.GetHeadPosition();
		while(pPos)
		{
			TOTAL_INFO pCur = m_peopInfo.GetAt(pPos);
			if(pCur.peop_Ip == szIP1)
			{
				pCur.m_SSocket = m_pChatListScoket;
				m_peopInfo.SetAt(pPos,pCur);
				
				
				
				char cblack_date[30][30];
				int i = 0;
				memset(cblack_date,'\0',30*30);
				std::string lines;
				std::fstream outsend;
				outsend.open("black.txt",std::ios::in);
				while(std::getline(outsend,lines))
				{
					strcpy(cblack_date[i],lines.c_str());
				}
				char c_sendmassage[900];
				memset(c_sendmassage,'\0',900);
				memcpy(c_sendmassage,cblack_date,sizeof(c_sendmassage));
				(pCur.m_SSocket)->Send(c_sendmassage,900);
				
				break ;
			}
			
			m_peopInfo.GetNext(pPos);
		}
	}
	
}

void CSkyeye3Dlg::RecMsg(CChatSocket* pSocket)
{
	CString cstrIP;
	UINT nPort;
	m_pChatSocket->GetPeerName(cstrIP, nPort);//��ÿͻ��˵�IP�Ͷ˿�
	
	POSITION pPos = m_peopInfo.GetHeadPosition();
	while (pPos)
	{
		TOTAL_INFO pCur = m_peopInfo.GetAt(pPos);
		if (pCur.peop_Ip == cstrIP) 
		{
			
			char str[sizeof(Final_Info)];
			memset(str,'\0',sizeof(Final_Info));
			
			char num[8];
			memset(num,'\0',8);
			
			int lenth = pSocket->Receive(str,sizeof(Final_Info));
			int identify,flag = 1;
			Final_Info pep_proc;
			char info[50];                         //����char���͵ı������洢������¼
			memset(info,'\0',50);
			std::fstream historylist;
			historylist.open("history.txt",std::ios::out|std::ios::app);
			SYSTEMTIME Time={0};
			
			memcpy(&identify,str,4);
			switch(identify) 
			{
			case 1:
				memcpy(&(pCur.pep_Info),str,sizeof(m_pepIP_Info.pep_Info));
				
				
				GetLocalTime(&Time);//��õ�ǰ����ʱ��
				historylist<<Time.wYear<<"."<<Time.wMonth<<"."<<Time.wDay<<" ";
				historylist<<Time.wHour<<":"<<Time.wMinute<<":"<<Time.wSecond;
				strcat(info,pCur.pep_Info.ComputerName);
				strcat(info,"����\n");
				historylist<<info;
				historylist.close();
				flag = 0;
				break;
			case 2:
				memcpy(&pep_proc,str,sizeof(Final_Info));
				memcpy(pCur.pep_proc,pep_proc.m_pop,sizeof(PROCESS_INFO)*200);
				
				break ;
			case 3:
				memcpy(&(pCur.net_stream),str,sizeof(NetFlux));
				
				break;
			}
			m_peopInfo.SetAt(pPos,pCur);
			if(flag = 1)
				historylist.close();
			break;
		}
		else 
		{
			m_peopInfo.GetNext(pPos);
		}
	}
}

HBRUSH CSkyeye3Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if( CTLCOLOR_STATIC  == nCtlColor)
	{
		pDC->SetTextColor(RGB(0,   0,  0));   
        pDC->SetBkMode(TRANSPARENT);
        hbr=(HBRUSH)GetStockObject(NULL_BRUSH);       //��ȡ������ɫ��Ϻ�Ļ��ʣ����͸��
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CSkyeye3Dlg::OnClickInfotree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	CPoint pt = GetCurrentMessage()->pt;                 //��ȡ��ǰ�������Ϣ�������   
	m_treeCtrl.ScreenToClient(&pt);                      //��������Ļ���꣬ת�������οؼ��Ŀͻ�������   
	UINT uFlags = 0;
	int ncouts = 1;
	HTREEITEM hItem = m_treeCtrl.HitTest(pt, &uFlags);   //Ȼ�����������   
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))       //��������λ�����ڽڵ�λ������
	{  
		m_treeCtrl.SelectItem(hItem);  
		
		int nDat = m_treeCtrl.GetItemData(hItem);        //Ȼ����ݲ�ͬ�Ľڵ㣬����ɲ�ͬ�Ķ�������
		POSITION pPos = m_peopInfo.GetHeadPosition();
		while (pPos)
		{
			if(nDat == ncouts)
			{
				TOTAL_INFO pCur = m_peopInfo.GetAt(pPos);
				GetDlgItem(IDC_IP)->SetWindowText(pCur.peop_Ip);
				GetDlgItem(IDC_USER)->SetWindowText((pCur.pep_Info).ComputerName);
				
				char trans[10];                //CPU��Ϣ��ȡ��ʾ
				char usr_cpu[200];                        
				memset(usr_cpu,'\0',200);
				
				strcat(usr_cpu,"CPU�ͺ�");
				strcat(usr_cpu,pCur.pep_Info.m_stProcessorType);
				strcat(usr_cpu,"\r\n");
				
				strcat(usr_cpu,"CPU����ϵ�ṹ");
				strcat(usr_cpu,pCur.pep_Info.m_stwProcessorArchitecture);
				strcat(usr_cpu,"\r\n");
				
				strcat(usr_cpu,"OEM ID");
				itoa(pCur.pep_Info.m_dwOemId,trans,10);
				strcat(usr_cpu,trans);
				strcat(usr_cpu,"\r\n");
				memset(trans,'\0',10);
				
				strcat(usr_cpu,"����������");
				itoa(pCur.pep_Info.m_dwProcessorType,trans,10);
				strcat(usr_cpu,trans);
				strcat(usr_cpu,"\r\n");
				memset(trans,'\0',10);
				
				strcat(usr_cpu,"����������");
				itoa(pCur.pep_Info.dwNumberOfProcessors,trans,10);
				strcat(usr_cpu,trans);
				strcat(usr_cpu,"\r\n");
				memset(trans,'\0',10);
				
				
				
				char opera_info[300];
				char buf[8];
				memset(opera_info,'\0',300);
				
				strcat(opera_info,(pCur.pep_Info).vername);            //ϵͳ��Ϣ��ȡ��ʾ
				strcat(opera_info,"  ");
				strcat(opera_info,"\r\n");
				
				strcat(opera_info,(pCur.pep_Info).szCSDVersion);
				strcat(opera_info,"\r\n");
				
				itoa((pCur.pep_Info).dwMajorVersion,buf,10);
				strcat(opera_info,"ϵͳ���汾��:");
				strcat(opera_info,buf);
				strcat(opera_info,"\r\n");
				memset(buf,'\0',8);
				
				strcat(opera_info,"ϵͳ�ΰ汾��:");
				itoa((pCur.pep_Info).dwMinorVersion,buf,10);
				strcat(opera_info,buf);
				strcat(opera_info,"\r\n");
				memset(buf,'\0',8);
				
				
				strcat(opera_info,"��ǰϵͳ��֧�ֵ�ƽ̨��:");
				itoa((pCur.pep_Info).dwPlatformId,buf,10);
				strcat(opera_info,buf);
				strcat(opera_info,"\r\n");
				
				
				GetDlgItem(IDC_CPU)->SetWindowText(usr_cpu);
				GetDlgItem(IDC_SYS)->SetWindowText(opera_info);

			//	GetDlgItem(IDC_NETWORK)->SetWindowText((pCur.pep_Info).m_Netowrk_Adapter);
				
				m_listActiveCards.DeleteAllItems();
				RefreshListCtrlData(pCur);
				
				break;
			}
			else
			{
				m_peopInfo.GetNext(pPos);
				ncouts++;
			}
			
		}
		*pResult = 0;
	}
}





void CSkyeye3Dlg::OnAboutUs() 
{
	// TODO: Add your control notification handler code here
	CAboutUsDlg aboutus;
	aboutus.DoModal();
}

void CSkyeye3Dlg::OnInfo() 
{
	// TODO: Add your control notification handler code here
	m_treeCtrl.DeleteAllItems();
	
	m_treeCtrl.ModifyStyle(0,TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS);
	
	int icounts = 1;
	HTREEITEM root = m_treeCtrl.InsertItem(_T("��˾"));
	HTREEITEM parent1 = m_treeCtrl.InsertItem(_T("���²�"));
	POSITION pPos = m_peopInfo.GetHeadPosition();
	while (pPos)
	{
		TOTAL_INFO pCur = m_peopInfo.GetAt(pPos);
		HTREEITEM child1 = m_treeCtrl.InsertItem(pCur.peop_Ip,parent1);
		m_treeCtrl.SetItemData(child1, icounts);
		icounts++;
		
		m_peopInfo.GetNext(pPos);
	}
	
	CWnd *pWnd;
	pWnd  =  GetDlgItem(IDC_INFOTREE);
	pWnd->ShowWindow(SW_SHOW);
	
	pWnd  =  GetDlgItem(IDC_PROCLIST);
	pWnd->ShowWindow(SW_SHOW);
	
	pWnd  =  GetDlgItem(IDC_IPNAME);
	pWnd->ShowWindow(SW_SHOW);
	
	pWnd  =  GetDlgItem(IDC_IP);
	pWnd->ShowWindow(SW_SHOW);
	
	pWnd  =  GetDlgItem(IDC_USER);
	pWnd->ShowWindow(SW_SHOW);
	
	pWnd  =  GetDlgItem(IDC_CPUINFO);
	pWnd->ShowWindow(SW_SHOW);
	
	pWnd  =  GetDlgItem(IDC_CPU);
	pWnd->ShowWindow(SW_SHOW);
	
	pWnd  =  GetDlgItem(IDC_SYSINFO);
	pWnd->ShowWindow(SW_SHOW);
	
	pWnd  =  GetDlgItem(IDC_SYS);
	pWnd->ShowWindow(SW_SHOW);
	
	pWnd  =  GetDlgItem(IDC_USERNAME);
	pWnd->ShowWindow(SW_SHOW);
	
	pWnd  =  GetDlgItem(IDC_DELETE);
	pWnd->ShowWindow(SW_SHOW);
	
	pWnd  =  GetDlgItem(IDC_NETWORK);
	pWnd->ShowWindow(SW_SHOW);
	
	pWnd  =  GetDlgItem(IDC_NET);
	pWnd->ShowWindow(SW_SHOW);
}

int CSkyeye3Dlg::InitListCtrlStyle()
{
	CRect rect;                                                                       //��ȡListCtrl�Ŀ��
	m_listActiveCards.GetClientRect(&rect);
	int nColInterval = rect.Width();
	
	m_listActiveCards.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT  );    //����ListCtrl����ʽ
	
	
	m_listActiveCards.InsertColumn(0, _T("������"), LVCFMT_RIGHT, int(nColInterval*0.4));//�������������������е����ָ�ʽ���п�
	m_listActiveCards.InsertColumn(1, _T("����ID"), LVCFMT_LEFT, int(nColInterval*0.6));
	
	return  0;
}

int CSkyeye3Dlg::RefreshListCtrlData(TOTAL_INFO pCur)
{

	//::MessageBox(NULL,(pCur.pep_proc[20]).PROCESS_NAME,"eyelog",MB_OK);
	m_listActiveCards.SetRedraw(FALSE);
	int i = 0;
	while(strcmp((pCur.pep_proc[i]).PROCESS_NAME,"\0"))
	{
		int iItemCount = m_listActiveCards.GetItemCount();
		m_listActiveCards.InsertItem(iItemCount,"");
		m_listActiveCards.SetItemText(iItemCount,0, (pCur.pep_proc[i]).PROCESS_NAME);
		CString strCardID;
		strCardID.Format("%u",(pCur.pep_proc[i]).PROCESS_ID);
		m_listActiveCards.SetItemText(iItemCount,1,strCardID);
		i++;
	}
	
	m_listActiveCards.SetRedraw(TRUE);
	return 0;
}

void CSkyeye3Dlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	CString str;
	for(int i=0; i < m_listActiveCards.GetItemCount(); i++)
	{
		if(m_listActiveCards.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			int n_icount = 0;
			POSITION pPos = m_peopInfo.GetHeadPosition();
			while (pPos)
			{
				TOTAL_INFO pCur = m_peopInfo.GetAt(pPos);
				if(n_icount == i)
				{ 
					pCur.m_SSocket->Send((pCur.pep_proc[i]).PROCESS_NAME,30);
					break;
				}
				else
				{
					m_peopInfo.SetAt(pPos,pCur);
					n_icount++;
				}
			}
			::MessageBox(NULL,"delete is ok","Skyeye",MB_OK);
			break;
			
		}
	}
}

void CSkyeye3Dlg::DelMessage(CChatSocket* pSocket)
{
	CString cstrIP;
	char lines[30];
	memset(lines,'\0',30);
	UINT nPort;
	pSocket->GetPeerName(cstrIP, nPort);//��ÿͻ��˵�IP�Ͷ�
	POSITION pPos = m_peopInfo.GetHeadPosition();
	while (pPos)
	{
		TOTAL_INFO pCur = m_peopInfo.GetAt(pPos);
		if (pCur.peop_Ip == cstrIP) 
		{
			std::fstream historylist;
			historylist.open("history.txt",std::ios::out|std::ios::app);
			
			SYSTEMTIME Time={0};
			GetLocalTime(&Time);//��õ�ǰ����ʱ��
			historylist<<Time.wYear<<"."<<Time.wMonth<<"."<<Time.wDay<<" ";
			historylist<<Time.wHour<<":"<<Time.wMinute<<":"<<Time.wSecond;

			strcat(lines, pCur.pep_Info.ComputerName);
			strcat(lines,"�˳�\n");
			historylist<<lines;
			historylist.close();
			
			m_peopInfo.RemoveAt(pPos);
			m_listActiveCards.DeleteAllItems();
			
			break;
		}
		else
			m_peopInfo.GetNext(pPos);
		
	}
}

void CSkyeye3Dlg::OnBlackdate() 
{
	// TODO: Add your control notification handler code here
	CBlackDateDlg blackDlg;
	blackDlg.DoModal();
	
	
	int i = 0;
	
	std::string lines;
	std::fstream outsend;
	char cblack_date[30][30];		
	memset(cblack_date,'\0',30*30);
	outsend.open("black.txt",std::ios::in);
	while(std::getline(outsend,lines))
	{
		strcpy(cblack_date[i],lines.c_str());
		i++;
	}
	
	
	char c_sendmassage[900];
	memset(c_sendmassage,'\0',900);
	
	memcpy(c_sendmassage,cblack_date,sizeof(c_sendmassage));
	
	
	char buffer[30];
	memset(buffer,'\0',30);
	strcat(buffer,"change");
	POSITION pPos = m_peopInfo.GetHeadPosition();
	while (pPos)
	{
		TOTAL_INFO pCur = m_peopInfo.GetAt(pPos);
		(pCur.m_SSocket)->Send(buffer,30);
		(pCur.m_SSocket)->Send(c_sendmassage,900);
		m_peopInfo.GetNext(pPos);
	}
	
	
	
	
	
}

void CSkyeye3Dlg::OnTitle() 
{
	// TODO: Add your control notification handler code here
	CWnd *pWnd;
	pWnd  =  GetDlgItem(IDC_INFOTREE);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_PROCLIST);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_IPNAME);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_IP);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_USER);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_CPUINFO);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_CPU);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_SYSINFO);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_SYS);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_USERNAME);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_DELETE);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_NETWORK);
	pWnd->ShowWindow(SW_HIDE);
	
	pWnd  =  GetDlgItem(IDC_NET);
	pWnd->ShowWindow(SW_HIDE);
}

void CSkyeye3Dlg::OnSysdate() 
{
	// TODO: Add your control notification handler code here
	CSysinfoDlg sysinfo;
	sysinfo.DoModal();
}
