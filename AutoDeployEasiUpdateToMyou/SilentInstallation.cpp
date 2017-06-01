#include "SilentInstallation.h"

SilentInstallation::SilentInstallation(const pStringNode const node)
{
	Conversion(node);//进行类型的转换
}

void SilentInstallation::Conversion(const pStringNode const node)
{
	CString temp = node->m_strpath.c_str();
	m_node.m_path = (LPCWSTR)(temp.AllocSysString());

	CString temp2 = node->m_strparameters.c_str();
	m_node.m_parameters = (LPCWSTR)(temp2.AllocSysString());

	CString temp3 = node->m_strverb.c_str();
	m_node.m_verb = (LPCWSTR)(temp3.AllocSysString());

	//进行路径查询的参数
	CString temp4 = node->m_strkeyvalue.c_str();
	m_node.m_keyvalue = (LPCWSTR)(temp4.AllocSysString());

	CString temp5 = node->m_strpathvalue.c_str();
	m_node.m_pathvalue = (LPCWSTR)(temp5.AllocSysString());
}

void SilentInstallation::Run(std::string &installationpath)
{
	SHELLEXECUTEINFO sei;
	ZeroMemory(&sei, sizeof(SHELLEXECUTEINFO));

	sei.cbSize = sizeof(SHELLEXECUTEINFO);
	sei.lpFile = m_node.m_path;
	sei.lpParameters = m_node.m_parameters;
	sei.nShow = SW_SHOW;
	sei.lpVerb = m_node.m_verb;
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	//进行静默安装
	ShellExecuteEx(&sei);
	std::cout << sei.hInstApp << std::endl;
	//等待当前进程的结束
	WaitForSingleObject(sei.hProcess, INFINITE);

	//安装路径、版本号的查询
	HKEY hKey;

	WCHAR szProductType2[MY_BUFSIZE];
	memset(szProductType2, 0, sizeof(szProductType2));

	DWORD dwBufLen = MY_BUFSIZE;
	LONG lRet;
	// 下面是打开注册表, 只有打开后才能做其他操作  
	lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, m_node.m_keyvalue,
		0, KEY_QUERY_VALUE, &hKey);
	if (lRet != ERROR_SUCCESS)   // 判断是否打开成功   
		return ;
	//下面开始查询   

	lRet = RegQueryValueEx(hKey, m_node.m_pathvalue, NULL, NULL,
		(LPBYTE)szProductType2, &dwBufLen);
	if (lRet != ERROR_SUCCESS)  // 判断是否查询成功
	{
		return ;
	}

	RegCloseKey(hKey);

	//读取注册表中的静默安装的path
	char ansipath[MY_BUFSIZE];
	WideCharToMultiByte(CP_ACP, 0, szProductType2, -1,ansipath, sizeof(ansipath), NULL, NULL);
	//std::cout << ansipath << std::endl;
	installationpath = ansipath;
}