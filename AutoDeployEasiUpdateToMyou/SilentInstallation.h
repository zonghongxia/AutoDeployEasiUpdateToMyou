#ifndef SILENTINSTALLATION_H
#define SILENTINSTALLATION_H

#include<windows.h> 
#include <iostream>  
#include <direct.h>
#include <string>
#include <string.h>
#include <atlstr.h>
//#include "Constant.h"

const int  MY_BUFSIZE = 256;

typedef struct StringNode
{
	std::string m_strpath;
	std::string m_strparameters;
	std::string m_strverb;
	std::string m_strkeyvalue;
	std::string m_strpathvalue;
}StringNode, *pStringNode;

typedef struct SilentNode
{
	LPCWSTR m_path;
	LPCWSTR m_parameters;
	LPCWSTR m_verb;
	LPCWSTR m_keyvalue;
	LPCWSTR m_pathvalue;
}SilentNode,*pSilentNode;

class SilentInstallation
{
public:
	SilentInstallation(const pStringNode const node);
	void Run(std::string &installationpath);
private:
	void Conversion(const pStringNode const node);
	SilentNode m_node;
};

#endif
