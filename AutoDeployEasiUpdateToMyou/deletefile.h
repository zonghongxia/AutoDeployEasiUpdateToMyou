#ifndef _DELETEFILE_H_
#define _DELETEFILE_H_

#include <Windows.h>
#include <tchar.h>
#include <cstring>
#include <string.h>
#include <wchar.h>
#include <tchar.h>
#include <shellapi.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <string>
#include <iostream>
#include <atlstr.h>

class DeleteFolderorFile
{
public:
	DeleteFolderorFile(std::string &path);
	bool DeleteDir();
private:
	bool DeleteDirectory(LPCTSTR lpszDir, bool noRecycleBin = true);
	std::string m_pDir;
};

#endif
