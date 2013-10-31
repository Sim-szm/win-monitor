#ifndef _HEADFILE_H
#define _HEADFILE_H
/////////////////////////////////////////////////

/************************************************
 * Define name:Head_file
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:系统编译所需的头文件
 * Change by: 2013-08-21 by
************************************************/
#include <winbase.h>
#include <tchar.h>
#include <atlbase.h>
#include <tlhelp32.h>
#include <time.h>
#include <string>
#include <assert.h>
#include <Winsock.h>
#include <process.h>
#include <stdlib.h>
#include <conio.h>
#include <stddef.h>
#include <io.h>
#include <sys/stat.h>
#include <malloc.h>
#include <CString>
#include "ipexport.h"
#include "iphlpapi.h"
#include "iptypes.h"
#include "iprtrmib.h"

/************************************************
 * Define name: System macro define 
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:系统所用到的宏值定义
 * Change by: 2013-08-21 by
************************************************/
#define MAX_PROCESS 200
#define MAX_PATHLENGTH 256
#define name_length 30
#define Flush_Rate 5000
#define Kill_Rate 3000
#define MAXPATH 255
#define Computer_Flag 1
#define Process_Flag 2
#define NetFlux_Flag 3
#define Black_Num 30
#pragma   comment(lib, "iphlpapi.lib")
/************************************************
 * Struct name:OS_INFO
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:客户端硬件信息汇总集合结构
 * Change by: 2013-08-21 by
************************************************/
typedef struct Mess_Info{
	int flag;
	char m_stProcessorType[name_length];					//CPU架构类型:m_stProcessorType
	char m_stwProcessorArchitecture[name_length];		//CPU设计架构:m_stwProcessorArchitecture
	DWORD  m_dwOemId;							//OEM ID :sysInfo.dwOemId
	DWORD  m_dwProcessorType;					//处理器的类型
	DWORD  dwNumberOfProcessors;				//处理器个数
	DWORD  dwMaxClockSpeed;						//CPU主频
	char vername[50];							//操作系统名称
	DWORD dwMajorVersion;						//系统主版本号
    DWORD dwMinorVersion; 						// 系统副版本号
	TCHAR szCSDVersion[128];                    //系统server pack 版本
    DWORD dwBuildNumber; 						//系统构建版本号
    DWORD dwPlatformId; 						//系统支持的架构平台 
	char ComputerName[MAX_COMPUTERNAME_LENGTH];	//计算机主机名称
	int memory_already_use;
	long memory_total;							//系统总共的物理内存大小
	long memory_for_free;
	char m_Netowrk_Adapter[2048];				//网卡信息
}OS_INFO;

/************************************************
 * Struct name:PROCESS_INFO
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:客户端进程信息存储结构
 * Change by: 2013-08-21 by
************************************************/

typedef struct process{
	char PROCESS_NAME[name_length];
	unsigned int PROCESS_ID;
}PROCESS_INFO;

/************************************************
 * Struct name:Final_Info
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:客户端进程列表信息存储结构
 * Change by: 2013-08-21 by
************************************************/

typedef struct infor{
	int flag;
	PROCESS_INFO m_pop[MAX_PROCESS];
}Final_Info;

/************************************************
 * Struct name:NetFlux
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:客户端网络流量信息存储结构
 * Change by: 2013-08-21 by
************************************************/

typedef struct Net{
	int flag;
	float m_Final_Send;
	float m_Final_Recv;
}NetFlux;

/************************************************
 * Class name:CClient_Control
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:客户端逻辑结构控制类
 * Change by: 2013-08-21 by
************************************************/

class CClient_Control{
	private:
		OS_INFO *ms;
		Final_Info *ps;
		NetFlux *net;
		CRITICAL_SECTION mylock;
	public:
		CClient_Control(){
			this->ms=(OS_INFO*)malloc(sizeof(OS_INFO));
			this->ps=(Final_Info*)malloc(sizeof(Final_Info));
			this->net=(NetFlux*)malloc(sizeof(NetFlux));
			InitializeCriticalSection(&(this->mylock));
			memset(this->m_Black_List,'\0',Black_Num*name_length);
		}

		~CClient_Control(){
			free(this->ms);
			this->ms=NULL;
			free(this->ps);
			this->ps=NULL;
			free(this->net);
			this->net=NULL;
			DeleteCriticalSection(&(this->mylock));
		}
		void Init_MainMessage_Part();      
		static void Begin_Kill_Part(void *);   
		void Network_Adapter();
		void GetNetSpeed(float *, float *);
		void GetHardwareInfo();
		void os_version();
		void Gethostname();
		void Getmemory_stat();
		int Process_Info();
		void Collect_Info();
		void send_message(SOCKET );
		void Process_And_NetFlux( SOCKET);
		BOOL KillProcess(DWORD);
		void Find_Process_ID(char *);
		void wait_kill_command(SOCKET);
		static void Check_Process_With_BlackList(void *);
	protected:
		char m_Black_List[Black_Num][name_length];

};
/************************************************
 * Function name:CClient_Control::Init_MainMessage_Part()
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:客户端主线程初始化函数
 * Change by: 2013-08-21 by
************************************************/
void CClient_Control::Init_MainMessage_Part(){
	loop:	WSADATA wsaData;  
	SOCKET client;  
	int port;    	
	struct sockaddr_in serv;  
	CString Server_ip="";
	CString m_des="";
	GetCurrentDirectory(MAX_PATHLENGTH,m_des.GetBuffer(MAX_PATHLENGTH));
	m_des.ReleaseBuffer();
	m_des+="\\Init_Info.ini";	
	port=GetPrivateProfileInt("PORT_SET","SERVER_HD_PORT",0,m_des);
	GetPrivateProfileString("IP_SET","Server_ip","",Server_ip.GetBufferSetLength(15),15,m_des);
	
	if (WSAStartup(MAKEWORD( 2,2 ), &wsaData) !=0  ){  
		printf("winsock load failed\n");   
	}  
	
	serv.sin_family = AF_INET;  
	serv.sin_port = htons(port);  
	serv.sin_addr.s_addr = inet_addr(((LPTSTR)(LPCTSTR)Server_ip));  
	
	client = socket(AF_INET, SOCK_STREAM,0);  
	if (client == INVALID_SOCKET){  
		printf("socket failed:%d\n", WSAGetLastError());   
	}  
	if (connect(client, (struct sockaddr*)&serv,sizeof(serv)) == INVALID_SOCKET){  
		std::cout<<"connect failed:"<<WSAGetLastError()<<std::endl<<"Infomation-Part 尝试重新连接服务端"<<std::endl;
		closesocket(client);  
	    WSACleanup();
		Sleep(1000);
		goto loop; 
	}  
	else{  
		_beginthread(CClient_Control::Begin_Kill_Part,0,this);
		std::cout<<"Information Part Connect Success !"<<std::endl;
		this->Network_Adapter();
		this->Collect_Info();
		this->send_message(client);
		this->Process_And_NetFlux(client);
	}
	closesocket(client);  
	WSACleanup();
	_endthread();
}
/************************************************
 * Function name:CClient_Control::Network_Adapter()
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:客户端网卡信息采集函数
 * Change by: 2013-08-21 by
************************************************/
void CClient_Control::Network_Adapter(){
	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapter = NULL;
	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
	pAdapterInfo = (PIP_ADAPTER_INFO)malloc(ulOutBufLen);
	DWORD dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen);
	if (dwRetVal == ERROR_BUFFER_OVERFLOW){
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *) malloc (ulOutBufLen);
		dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen);
	}
	if (dwRetVal == NO_ERROR){
		memset(this->ms->m_Netowrk_Adapter,'\0',2048);
		pAdapter = pAdapterInfo;
		strcat(this->ms->m_Netowrk_Adapter,"网卡信息:\r\n");
		while (pAdapter){
			strcat(this->ms->m_Netowrk_Adapter,"Adapter Name: \t");
			strcat(this->ms->m_Netowrk_Adapter,pAdapter->AdapterName);
			strcat(this->ms->m_Netowrk_Adapter,"\r\n");

			strcat(this->ms->m_Netowrk_Adapter,"Adapter Desc: \t");
			strcat(this->ms->m_Netowrk_Adapter,pAdapter->Description);
			strcat(this->ms->m_Netowrk_Adapter,"\r\n");

			strcat(this->ms->m_Netowrk_Adapter,"IP Address: \t");
			strcat(this->ms->m_Netowrk_Adapter,pAdapter->IpAddressList.IpAddress.String);
			strcat(this->ms->m_Netowrk_Adapter,"\r\n");

			strcat(this->ms->m_Netowrk_Adapter,"IP Mask: \t");
			strcat(this->ms->m_Netowrk_Adapter,pAdapter->IpAddressList.IpMask.String);
			strcat(this->ms->m_Netowrk_Adapter,"\r\n");

			strcat(this->ms->m_Netowrk_Adapter,"Gateway: \t");
			strcat(this->ms->m_Netowrk_Adapter,pAdapter->GatewayList.IpAddress.String);
			strcat(this->ms->m_Netowrk_Adapter,"\r\n");

			pAdapter = pAdapter->Next;
		}
	}
	else{
		printf("Call to GetAdaptersInfo failed.\n");
	}

}
/************************************************
 * Function name:CClient_Control::GetNetSpeed()
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:客户端网络流量信息采集函数
 * Change by: 2013-08-21 by
************************************************/
void CClient_Control::GetNetSpeed(float *TotalSendtemp, float *TotalRecvtemp){
	float TotalRecv = 0, TotalSend = 0;
	MIB_IFTABLE* pIfTable=(MIB_IFTABLE*)malloc(sizeof(MIB_IFTABLE));
	DWORD dwSize = 0;
    DWORD dwRetVal = 0;

    if (GetIfTable(pIfTable, &dwSize, FALSE) == ERROR_INSUFFICIENT_BUFFER) {
        free(pIfTable);
        pIfTable = (MIB_IFTABLE *) malloc(dwSize);
        if (pIfTable == NULL) {
            printf("Calloc memory error !\n");
        }
    }
	int rvalue = GetIfTable(pIfTable, &dwSize, TRUE);

	for(int i = 0; i < pIfTable->dwNumEntries; i++){
		if (pIfTable->table[i].dwType == 6){
			if (pIfTable->table[i].dwInOctets > TotalRecv){
				TotalRecv = pIfTable->table[i].dwInOctets;
			}
			if (pIfTable->table[i].dwOutOctets > TotalSend){
				TotalSend = pIfTable->table[i].dwOutOctets;
			}
		}
	}
	*TotalSendtemp = TotalSend / 1024;
	*TotalRecvtemp = TotalRecv / 1024;

	free(pIfTable);
}

/************************************************
 * Function name:CClient_Control::GetHardwareInfo()
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:客户端CPU信息采集函数
 * Change by: 2013-08-21 by
************************************************/
void CClient_Control::GetHardwareInfo(){
	SYSTEM_INFO sysInfo;
	CRegKey regkey;
	LONG lResult;
	DWORD dwValue;
	std::string strPath="HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0";
	lResult=regkey.Open(HKEY_LOCAL_MACHINE,LPCTSTR(strPath.c_str()),KEY_ALL_ACCESS);
	GetSystemInfo(&sysInfo);
	memset(this->ms->m_stProcessorType,'\0',name_length);
	memset(this->ms->m_stwProcessorArchitecture,'\0',name_length);
	if (sysInfo.dwProcessorType  == PROCESSOR_INTEL_386) {
		strcpy(this->ms->m_stProcessorType,"Intel 386");
	}
	else if (sysInfo.dwProcessorType  == PROCESSOR_INTEL_486) {
		strcpy(this->ms->m_stProcessorType,"Intel 486");
	}
	else if (sysInfo.dwProcessorType  == PROCESSOR_INTEL_PENTIUM) {
		strcpy(this->ms->m_stProcessorType,"Intel Pentium架构");
	}
	else {
		strcpy(this->ms->m_stProcessorType,"Unknown");
	}
	if(sysInfo.wProcessorArchitecture==9){
		strcpy(this->ms->m_stwProcessorArchitecture,"x64 (AMD or Intel)");
	}else if(sysInfo.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_IA64){
		strcpy(this->ms->m_stwProcessorArchitecture,"Intel Itanium Processor Family (IPF)");
	}else if(sysInfo.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_INTEL){
		strcpy(this->ms->m_stwProcessorArchitecture," x86");
	}else if(sysInfo.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_UNKNOWN){
		strcpy(this->ms->m_stwProcessorArchitecture,"Unknown processor");
	}
	
	this->ms->m_dwOemId=sysInfo.dwOemId;
	this->ms->dwNumberOfProcessors=sysInfo.dwNumberOfProcessors;
	this->ms->m_dwProcessorType=sysInfo.dwProcessorType;
	if (ERROR_SUCCESS == regkey.QueryValue(dwValue,"MHz")){  
        this->ms->dwMaxClockSpeed = dwValue;
    }  
	regkey.Close();	
}

/************************************************
 * Function name:CClient_Control::os_version()
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:客户端操作系统信息采集函数
 * Change by: 2013-08-21 by
************************************************/
void CClient_Control::os_version(){
	OSVERSIONINFOEX osVersionInfoEx;
	osVersionInfoEx.dwOSVersionInfoSize=sizeof(osVersionInfoEx); 	
	if(! GetVersionEx((LPOSVERSIONINFO)&osVersionInfoEx)){
		strcpy(this->ms->vername,"GetVersionEx(LPOSVERSIONINFO osVersionInfoEx) return FALSE");
		std::cout<<this->ms->vername<<std::endl;
	}
	else{
		strcpy(this->ms->vername,"操作系统信息:");
		switch(osVersionInfoEx.dwPlatformId){
		case VER_PLATFORM_WIN32_NT:
			if(osVersionInfoEx.dwMajorVersion==6 && osVersionInfoEx.dwMinorVersion==0)
				strcat(this->ms->vername,"Microsoft Windows Vista");
			if(osVersionInfoEx.dwMajorVersion==6 && osVersionInfoEx.dwMinorVersion==1)
				strcat(this->ms->vername,"Microsoft Windows 7");
			else if(osVersionInfoEx.dwMajorVersion==5 && osVersionInfoEx.dwMinorVersion==0)
				strcat(this->ms->vername,"Microsoft Windows 2000");
			else if(osVersionInfoEx.dwMajorVersion==5 && osVersionInfoEx.dwMinorVersion==1)
				strcat(this->ms->vername,"Microsoft Windows XP");
			else if(osVersionInfoEx.dwMajorVersion==4 && osVersionInfoEx.dwMinorVersion==0)
				strcat(this->ms->vername,"Microsoft Windows NT");
			break;
		case VER_PLATFORM_WIN32_WINDOWS:
			if(osVersionInfoEx.dwMajorVersion==4 && osVersionInfoEx.dwMinorVersion==10)
				strcat(this->ms->vername,"Microsoft Windows 98");
			else if(osVersionInfoEx.dwMajorVersion==4 && osVersionInfoEx.dwMinorVersion==90)
				strcat(this->ms->vername,"Microsoft Windows ME");
			else
				strcat(this->ms->vername,"Microsoft Windows 95");
			break;
		default:
			break;
		}
	}
	strcpy(this->ms->szCSDVersion,osVersionInfoEx.szCSDVersion);
	this->ms->dwMajorVersion=osVersionInfoEx.dwMajorVersion;
	this->ms->dwMinorVersion=osVersionInfoEx.dwMinorVersion;
	this->ms->dwBuildNumber=osVersionInfoEx.dwBuildNumber;
	this->ms->dwPlatformId=osVersionInfoEx.dwPlatformId;
}
/************************************************
 * Function name:CClient_Control::Gethostname()
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:客户端主机名信息采集函数
 * Change by: 2013-08-21 by
************************************************/
void CClient_Control::Gethostname(){	
	DWORD MaxComputerlenth = MAX_COMPUTERNAME_LENGTH;
	GetComputerName(this->ms->ComputerName, &MaxComputerlenth); 
}
/************************************************
 * Function name:CClient_Control::Getmemory_stat()
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:客户端主机名信息采集函数
 * Change by: 2013-08-21 by
************************************************/
void CClient_Control::Getmemory_stat(){	
	MEMORYSTATUS stat;
	GlobalMemoryStatus(&stat);
	this->ms->memory_already_use=stat.dwMemoryLoad;	
	this->ms->memory_total=stat.dwTotalPhys/1024;   
	this->ms->memory_for_free=stat.dwAvailPhys/1024;	
}

/************************************************
 * Function name:CClient_Control::Process_Info()
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:客户端进程信息采集函数
 * Change by: 2013-08-21 by
************************************************/
int CClient_Control::Process_Info(){
	PROCESSENTRY32 pe32;
	Final_Info *pi=this->ps;
	int i=0;
	pi->flag=Process_Flag;
	pe32.dwSize = sizeof(pe32);
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if (hProcessSnap == INVALID_HANDLE_VALUE){
		printf("CreateToolhelp32Snapshot 调用失败.\n");
		return -1;
	}
	BOOL bMore = ::Process32First(hProcessSnap,&pe32);
	while (bMore){
		(pi->m_pop[i]).PROCESS_ID=pe32.th32ProcessID;
		strcpy((pi->m_pop[i]).PROCESS_NAME,pe32.szExeFile);
		i++;
		bMore = ::Process32Next(hProcessSnap,&pe32);
	}
	pi=NULL;
	::CloseHandle(hProcessSnap);
	return 0;
}
void CClient_Control::Collect_Info(){
	this->ms->flag=Computer_Flag;
	this->Gethostname();
	this->GetHardwareInfo();
	this->os_version();
	this->Getmemory_stat();
}

/************************************************
 * Function name:CClient_Control::send_message()
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:客户端硬件信息发送函数采集函数
 * Change by: 2013-08-21 by
************************************************/
void CClient_Control::send_message(SOCKET client){	
	char Send_len[sizeof(OS_INFO)];
	memset(Send_len,'\0',sizeof(OS_INFO));
	memcpy(Send_len,this->ms,sizeof(OS_INFO));
	int iv=send(client,Send_len,sizeof(OS_INFO),0);
	if(iv<0){
			CClient_Control Second;
			Second.Init_MainMessage_Part();
			this->~CClient_Control();
			free(this);
	}
	std::cout<<"hardware send over !"<<std::endl;
	memset(Send_len,'\0',sizeof(OS_INFO));
}

/************************************************
 * Function name:CClient_Control::Process_And_NetFlux()
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:客户端进程和流速信息发送函数采集函数
 * Change by: 2013-08-21 by
************************************************/
void CClient_Control::Process_And_NetFlux( SOCKET point){
	char Send_buf[sizeof(Final_Info)];
	char Net_buf[sizeof(NetFlux)];
	int i;
	while(1){
		float TotalSend[2], TotalRecv[2];
		net->flag=NetFlux_Flag;
		memset(Send_buf,'\0',sizeof(Final_Info));
		memset(Net_buf,'\0',sizeof(NetFlux));
		for(i=0;i<MAX_PROCESS;i++){
			memset(this->ps->m_pop[i].PROCESS_NAME,'\0',name_length);
		}
		this->Process_Info();
		memcpy(Send_buf,this->ps,sizeof(Final_Info));
		if(send(point,Send_buf,sizeof(Final_Info),0)>0){
			std::cout<<"process_info send success !"<<std::endl;
		}
		else{	
			CClient_Control Second;
			Second.Init_MainMessage_Part();
			this->~CClient_Control();
			free(this);
			break;

		}
		GetNetSpeed(&TotalSend[0], &TotalRecv[0]);
		Sleep(Flush_Rate);
		GetNetSpeed(&TotalSend[1], &TotalRecv[1]);
		this->net->m_Final_Send = (TotalSend[1] - TotalSend[0]) / 5;
		this->net->m_Final_Recv = (TotalRecv[1] - TotalRecv[0]) / 5;
		memcpy(Net_buf,this->net,sizeof(NetFlux));
		if(send(point,Net_buf,sizeof(NetFlux),0)>0){
			std::cout<<"Net info send success !"<<std::endl;
		}else{
			CClient_Control Second;
			Second.Init_MainMessage_Part();
			this->~CClient_Control();
			free(this);
			break;

		}
		Sleep(1000);
	}
}

/************************************************
 * Function name:CClient_Control::KillProcess()
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:客户端查杀非法进程主函数
 * Change by: 2013-08-21 by
************************************************/
BOOL CClient_Control::KillProcess(DWORD ProcessId){
    HANDLE hProcess=OpenProcess(PROCESS_TERMINATE,FALSE,ProcessId);
    if(hProcess==NULL)
        return FALSE;
    if(!TerminateProcess(hProcess,0))
        return FALSE;
    return TRUE;
}

/************************************************
 * Function name:CClient_Control::Find_Process_ID()
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:客户端查找非法进程并执行查杀函数
 * Change by: 2013-08-21 by
************************************************/
void CClient_Control::Find_Process_ID(char *process_name){
	int tip;
	Final_Info *check_id=this->ps;
	EnterCriticalSection(&(this->mylock));
	for(tip=0;tip<MAX_PROCESS;tip++){
		if(strcmp(check_id->m_pop[tip].PROCESS_NAME,process_name)==0){
			if(KillProcess(check_id->m_pop[tip].PROCESS_ID)){
				std::cout<<"【"<<check_id->m_pop[tip].PROCESS_NAME<<"】"<<"Being killed !"<<std::endl;
			}
		}
	}
	LeaveCriticalSection(&(this->mylock));
}

/************************************************
 * Function name:CClient_Control::wait_kill_command()
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:客户端监听服务端查杀命令函数
 * Change by: 2013-08-21 by
************************************************/
void CClient_Control::wait_kill_command(SOCKET kill_command){
	int irecv=0;
	char m_Recv_Name[name_length*Black_Num];
	char process_name[name_length];
	std::cout<<"Kill-Part waitting command !"<<std::endl;
	memset(process_name,'\0',name_length);
	irecv=recv(kill_command,process_name,name_length,0);
	std::cout<<"Flush thread recv: "<<process_name<<std::endl;
	if(irecv<0){
		std::cout<<"server crush !"<<std::endl;
			_endthread();
	}
	if(strncmp(process_name,"change",6)==0){
		EnterCriticalSection(&(this->mylock));
		memset(this->m_Black_List,'\0',sizeof(this->m_Black_List));
		memset(m_Recv_Name,'\0',name_length*Black_Num);
		Sleep(1000);
		int m_Recv=recv(kill_command,m_Recv_Name,name_length*Black_Num,0);
		if(m_Recv>0){
			std::cout<<"【"<<"recv 'change' and BlackList flush over"<<"】"<<std::endl;
		}
		memcpy(this->m_Black_List,m_Recv_Name,name_length*Black_Num);
		LeaveCriticalSection(&(this->mylock));
	}else{
		Find_Process_ID(process_name); 
	}
}
/************************************************
 * Function name:CClient_Control::Check_Process_With_BlackList
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:客户端根据黑名单查杀进程函数
 * Change by: 2013-08-21 by
************************************************/
void CClient_Control::Check_Process_With_BlackList(void *sim){
	int i,j;
	std::cout<<"【"<<"BlackList-Check-Part Start !"<<"】"<<std::endl;
	while(1){
		//EnterCriticalSection(&(((CClient_Control*)sim)->mylock)); 
		for(i=0;i<Black_Num;i++){
			for(j=0;j<MAX_PROCESS;j++){
				if(strcmp(((CClient_Control*)sim)->m_Black_List[i],(((CClient_Control*)sim)->ps)->m_pop[j].PROCESS_NAME)==0){
					((CClient_Control*)sim)->KillProcess((((CClient_Control*)sim)->ps)->m_pop[j].PROCESS_ID);
				}
			}
		}
	//	LeaveCriticalSection(&(((CClient_Control*)sim)->mylock)); 
		Sleep(Kill_Rate);
	}
	_endthread();
}
/************************************************
 * Function name:CClient_Control::Begin_Kill_Part
 * Create by:沈昭萌
 * CreateDate:2013-08-21
 * Explain:客户端查杀线程初始化函数
 * Change by: 2013-08-21 by
************************************************/
void CClient_Control::Begin_Kill_Part(void *p){
koop:	WSADATA m_wsaData;  
	SOCKET sockfd;
	struct sockaddr_in server_addr;
	char m_Recv_Name[name_length*Black_Num];
	CString server_ip="";
	CString des="";
	GetCurrentDirectory(MAX_PATHLENGTH,des.GetBuffer(MAX_PATHLENGTH));
	des.ReleaseBuffer();
	des+="\\Init_Info.ini";
	int port_id;
	port_id=GetPrivateProfileInt("PORT_SET","SERVER_Kill_PORT",0,des);
	GetPrivateProfileString("IP_SET","SERVER_IP","",server_ip.GetBufferSetLength(15),15,des);
	if (WSAStartup(MAKEWORD( 2,2 ), &m_wsaData) !=0  ){  
		printf("winsock load failed\n");   
	}  
	server_addr.sin_family = AF_INET;  
	server_addr.sin_port = htons(port_id);  
	server_addr.sin_addr.s_addr = inet_addr(((LPTSTR)(LPCTSTR)server_ip));  
	
	sockfd = socket(AF_INET, SOCK_STREAM,0);   
	if (sockfd == INVALID_SOCKET)  {  
		printf("socket failed:%d\n", WSAGetLastError());   
	}
	if(connect(sockfd, (struct sockaddr*)&server_addr,sizeof(server_addr)) == INVALID_SOCKET){
		std::cout<<"connect failed:"<<WSAGetLastError()<<std::endl<<"Kill-Part 尝试重新连接服务端"<<std::endl;
		closesocket(sockfd);  
	    WSACleanup();
		Sleep(1000);
		goto koop;
	}
	else {  
		std::cout<<"Kill-Part Connect Success !"<<std::endl;
		EnterCriticalSection(&(((CClient_Control*)p)->mylock));
		memset(((CClient_Control*)p)->m_Black_List,'\0',sizeof(((CClient_Control*)p)->m_Black_List));
		memset(m_Recv_Name,'\0',name_length*Black_Num);
		int P_recv=recv(sockfd,m_Recv_Name,name_length*Black_Num,0);
		memcpy(((CClient_Control*)p)->m_Black_List,m_Recv_Name,name_length*Black_Num);
		LeaveCriticalSection(&(((CClient_Control*)p)->mylock));
		_beginthread(((CClient_Control*)p)->Check_Process_With_BlackList,0,(CClient_Control*)p);
		while(1){		
			((CClient_Control*)p)->wait_kill_command(sockfd);
			Sleep(1000);
		}
	}
	closesocket(sockfd);  
	WSACleanup();  
	_endthread();
}
////////////////////////////////////////////////
#endif