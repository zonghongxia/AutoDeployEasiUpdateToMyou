#include "Getdrive.h"


Drive::Drive()
{

}
void Drive::GetDrive(std::string &drive)
{
	DWORD dwLen = GetLogicalDriveStrings(0, NULL);//��ȡϵͳ�̷��ַ�������  
	char *pszDriver = new char[dwLen];//�����ַ�����  

	WCHAR wszClassName[256];
	memset(wszClassName, 0, sizeof(wszClassName));
	MultiByteToWideChar(CP_ACP, 0, pszDriver, strlen(pszDriver) + 1, wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));

	GetLogicalDriveStrings(dwLen, wszClassName);//��ȡϵͳ�̷��ַ���  

	char tmp[234] = { 0 };
	for (int i = 0; i < 20; ++i)
	{
		tmp[i] = wszClassName[i];
	}

	char* pDriver = tmp;
	char tmp2[10] = { 0 };
	while (*pDriver != '\0')
	{
		if (*pDriver != 'C')
		{
			strcpy(tmp2, pDriver);
			break;
		}
		pDriver += strlen(pDriver) + 1;//��λ����һ���ַ�������1��Ϊ������\0�ַ�  
	}
	if (tmp2 == NULL || *tmp2 == NULL)
	{
		std::cout << "drive error" << std::endl;
	}
	drive = tmp2;
	delete[] pszDriver;
}