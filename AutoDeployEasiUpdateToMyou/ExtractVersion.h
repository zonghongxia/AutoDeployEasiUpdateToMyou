#ifndef _EXTRACTVERSION_H
#define _EXTRACTVERSION_H

#include <string>
#include <iostream>

class ExtractVersion
{
public:
	void GetVersion(const std::string &path, std::string &version);
};

#endif
