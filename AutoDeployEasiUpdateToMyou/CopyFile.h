#ifndef _COPYFILE_H
#define _COPYFILE_H

#include <windows.h>
#include <string>
#include <atlstr.h>
#include <iostream>

class CopyJsonFile
{
public:
	CopyJsonFile(const std::string &source,const std::string &destination);

	bool Copy();
private:
	std::string m_source;
	std::string m_destination;
};

#endif
