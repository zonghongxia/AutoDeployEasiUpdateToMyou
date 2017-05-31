#ifndef _LIST_EXEFILE_H
#define _LIST_EXEFILE_H

#include <stdlib.h>  
#include <direct.h>
#include <string.h>  
#include <string>  
#include <io.h>
#include <stdio.h>   
#include <vector>  
#include <iostream>
#include "GetDiffHour.h"

class CExeFile
{
private:
	std::string m_szInitDir;
	std::string m_cdir;
public:
	CExeFile(const std::string &initdir);
	bool SetInitDir(const  std::string &dir);
	void BeginBrowseFilenames(const std::string &filespec, std::string &filename);
private:
	void GetDirFilenames(const std::string &dir, const std::string &filespec, std::string &filename);
};

#endif



