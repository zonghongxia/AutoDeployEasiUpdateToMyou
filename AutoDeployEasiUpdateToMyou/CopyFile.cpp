#include "CopyFile.h"

CopyJsonFile::CopyJsonFile(const std::string &source, const std::string &destination)
{
	m_source = source;
	m_destination = destination;
}

bool CopyJsonFile::Copy()
{
	CString temp = m_source.c_str();
	LPCWSTR source1 = (LPCWSTR)(temp.AllocSysString());

	CString tmp = m_destination.c_str();
	LPCWSTR destination2 = (LPCWSTR)(tmp.AllocSysString());

	if (CopyFile(source1, destination2, false))//false´ú±í¸²¸Ç£¬true²»¸²¸Ç
	{
		return true;
	}
	return false;
}