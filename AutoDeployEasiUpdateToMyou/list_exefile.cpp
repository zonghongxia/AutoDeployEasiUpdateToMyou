#include "list_exefile.h"

CExeFile::CExeFile(const std::string &initdir)
{
	m_szInitDir = initdir;
	int len = m_szInitDir.size();
	if (m_szInitDir[len - 1] != '/')
	{
		m_szInitDir += "/";
	}
}

bool CExeFile::SetInitDir(const  std::string &dir)
{
	if (_fullpath(const_cast<char *>(m_szInitDir.c_str()), dir.c_str(), _MAX_PATH) == NULL)
	{
		return false;
	}
	std::string cdirtp = _getcwd(NULL,0);
	//std::cout << cdirtp << std::endl;
	m_cdir = cdirtp;
	if (_chdir(m_szInitDir.c_str()) != 0)
	{
		return false;
	}

	int len = m_szInitDir.size();
	if (m_szInitDir[len - 1] != '\\')
	{
		m_szInitDir += "\\";
	}

	return true;
}

void CExeFile::BeginBrowseFilenames(const std::string &filespec, std::string &filename)
{
	return GetDirFilenames(m_szInitDir, filespec, filename);
}

void CExeFile::GetDirFilenames(const std::string &dir, const std::string &filespec, std::string &filename)
{
	GetDiffHour pathdiff(dir);
	double minmin = pathdiff.GetPathDiffHour();

	//_chdir(dir.c_str());

	long l_hFile;
	_finddata_t l_fileinfo;
	if ((l_hFile = _findfirst(filespec.c_str(), &l_fileinfo)) != -1)
	{
		do
		{
			if (!(l_fileinfo.attrib & _A_SUBDIR))
			{
				char l_filename[_MAX_PATH];
				strcpy(l_filename, dir.c_str());
				strcat(l_filename, "\\");
				strcat(l_filename, l_fileinfo.name);
				GetDiffHour pathdiff(l_filename);
				double p = pathdiff.GetPathDiffHour();
				if (p <= minmin)
				{
					minmin = p;
					filename = l_filename;
				}
			}
		} while (_findnext(l_hFile, &l_fileinfo) == 0);
		_findclose(l_hFile);
	}
	_chdir(m_cdir.c_str());
	//_findclose(l_hFile);
}