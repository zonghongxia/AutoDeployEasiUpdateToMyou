#ifndef _GEEXEFILE_H
#define _GEEXEFILE_H

#include <string>
#include <iostream>
#include "list_exefile.h"

class GetRecentExeFile
{
public:
	GetRecentExeFile(const std::string &path);

	void GetFilename(std::string &filename);

private:
	std::string m_path;
};

#endif


