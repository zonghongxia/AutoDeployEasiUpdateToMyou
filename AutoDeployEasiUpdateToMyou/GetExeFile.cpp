#include "GetExeFile.h"

GetRecentExeFile::GetRecentExeFile(const std::string &path)
{
	m_path = path;
}

void GetRecentExeFile::GetFilename(std::string &filename)
{
	CExeFile statdir(m_path);
	if (!statdir.SetInitDir(m_path))
	{
		puts("Ä¿Â¼²»´æÔÚ¡£");
		return;
	}

	statdir.BeginBrowseFilenames("*.*", filename);
}