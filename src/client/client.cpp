#include <iostream>
#include <afx.h>
#include "headfile.h"
//#pragma   comment(linker,   "/subsystem:\"windows\"   /entry:\"mainCRTStartup\""   )
/************************************************
 * Function name: main(int argc,char *argv[],char*envp[])
 * Create by:������
 * CreateDate:2013-08-21
 * Explain:�ͻ���ִ����ں���
 * Change by: 2013-08-21 by
************************************************/
int main(int argc, char * argv[],char*envp[]){  
	class CClient_Control SIM;
	SIM.Init_MainMessage_Part();
	return 0;  
}  