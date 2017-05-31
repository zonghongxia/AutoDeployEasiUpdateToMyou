#include<windows.h> 
#include <iostream>  
#include <direct.h>
#include <string>
#include <string.h>
#include <atlstr.h>

#include "SilentInstallation.h"
#include "GetExeFile.h"
#include "ExtractVersion.h"
#include  "Changejson.h"
#include "CopyFile.h"
#include "myzip.h"


int main()
{
	//��ȡ��ǰĿ¼�µ����°汾
	std::string tp("D://myouexefile/6.0/SeewoService");
	GetRecentExeFile getfilename(tp);
	std::string str;
	getfilename.GetFilename(str);
	std::cout << str << std::endl;

	//��·������ȡ�汾��
	std::string version;
	ExtractVersion ver;
	ver.GetVersion(str, version);
	std::cout << "version:" << version << std::endl;

	//����json�ļ��еİ汾��
	Json::Value tmp;
	ChangeJson json(jsonpath, tmp);
	if (json.WillChange(versionname, version))
	{
		std::cout << "ok" << std::endl;
	}

	//��Ĭ��װ
	StringNode node = { str,str2,str3,str4,str5 };
	SilentInstallation nnode(&node);
	std::string installationpath;
	nnode.Run(installationpath);
	std::cout <<"��Ĭ��װ��·��"<< installationpath << std::endl;

	//����json�ļ�����װĿ¼��
	std::string sour = jsonpath;
	std::cout << "sour=" << sour << std::endl;
	std::string des = installationpath;
	des += "\\";
	des += jsonpath;
	std::cout << "des=" << des << std::endl;
	CopyJsonFile copyfile(sour,des);
	if (copyfile.Copy())
	{
		std::cout << "ok" << std::endl;
	}

	//ѹ��
	std::string zippath = installationpath;
	zippath += version;
	zippath += ".zip";
	ZIP zip(installationpath,zippath);
	zip.CreateMyZip();

	//�ϴ�

	return 0;
}


//�첽����
//cout << ShellExecute(0, (LPCWSTR)L"open", (LPCWSTR)L"D:\\myouexefile\\6.0\\SeewoService\\SeewoServiceSetup_6.1.2.5533.exe", (LPCWSTR)L"/S ", (LPCWSTR)(NULL), SW_SHOWNOACTIVATE) << endl;

//��Ĭ��װ�Ĳ���
//const std::string str = "D:\\myouexefile\\6.0\\SeewoService\\SeewoServiceSetup_6.1.2.5533.exe";
//CString temp = str.c_str();
//LPCWSTR path = (LPCWSTR)(temp.AllocSysString());

//const std::string str2 = "/S";
//CString temp2 = str2.c_str();
//LPCWSTR parameters = (LPCWSTR)(temp2.AllocSysString());

//const std::string str3 = "open";
//CString temp3 = str3.c_str();
//LPCWSTR verb = (LPCWSTR)(temp3.AllocSysString());

////����·����ѯ�Ĳ���
//const std::string str4 = "SOFTWARE\\Seewo\\SeewoService";
//CString temp4 = str4.c_str();
//LPCWSTR keyvalue = (LPCWSTR)(temp4.AllocSysString());

//const std::string str5 = "path";
//CString temp5 = str5.c_str();
//LPCWSTR pathvalue = (LPCWSTR)(temp5.AllocSysString()); 

//const std::string str6 = "version";
//CString temp6 = str6.c_str();
//LPCWSTR versionvalue = (LPCWSTR)(temp6.AllocSysString()); 



////��Ĭ��װ
//SHELLEXECUTEINFO sei;
//ZeroMemory(&sei, sizeof(SHELLEXECUTEINFO));

//sei.cbSize = sizeof(SHELLEXECUTEINFO);
//sei.lpFile = path;
//sei.lpParameters = parameters;
//sei.nShow = SW_SHOW;
//sei.lpVerb = verb;
//sei.fMask = SEE_MASK_NOCLOSEPROCESS;
////���о�Ĭ��װ
////ShellExecuteEx(&sei);
//cout << sei.hInstApp << endl;
////�ȴ���ǰ���̵Ľ���
////WaitForSingleObject(sei.hProcess, INFINITE);

////��װ·�����汾�ŵĲ�ѯ
//HKEY hKey;

//WCHAR szProductType2[MY_BUFSIZE];
//memset(szProductType2, 0, sizeof(szProductType2));

//WCHAR szProductType3[MY_BUFSIZE];
//memset(szProductType3, 0, sizeof(szProductType3));

//DWORD dwBufLen = MY_BUFSIZE;
//LONG lRet;
//// �����Ǵ�ע���, ֻ�д򿪺��������������  
//lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, keyvalue,
//	0, KEY_QUERY_VALUE, &hKey);
//if (lRet != ERROR_SUCCESS)   // �ж��Ƿ�򿪳ɹ�   
//	return 1;
////���濪ʼ��ѯ   

//lRet = RegQueryValueEx(hKey, pathvalue, NULL, NULL,
//	(LPBYTE)szProductType2, &dwBufLen);
//if (lRet != ERROR_SUCCESS)  // �ж��Ƿ��ѯ�ɹ�
//{
//	return 1;
//}

//lRet = RegQueryValueEx(hKey, versionvalue, NULL, NULL,
//	(LPBYTE)szProductType3, &dwBufLen);
//if (lRet != ERROR_SUCCESS)  // �ж��Ƿ��ѯ�ɹ�
//{
//	return 1;
//}
//RegCloseKey(hKey);

////��ȡע����еľ�Ĭ��װ��path
//char ansipath[MY_BUFSIZE];
//WideCharToMultiByte(CP_ACP, 0, szProductType2, -1, ansipath, sizeof(ansipath), NULL, NULL);
//cout << ansipath <<endl;

////��ȡע����еľ�Ĭ��װ��version
//char ansiversion[MY_BUFSIZE];
//WideCharToMultiByte(CP_ACP, 0, szProductType3, -1, ansiversion, sizeof(ansiversion), NULL, NULL);
//cout << ansiversion <<endl;

