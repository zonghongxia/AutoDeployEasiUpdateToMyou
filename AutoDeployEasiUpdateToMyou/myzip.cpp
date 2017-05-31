#include "myzip.h"


const int ZIP::GLOBAL_LENSZIP = 4;

const int ZIP::GLOBAL_TMP_LENGTH = 128;


void ZIP::GetSubStr(const std::string &path, std::string &subtmp)
{
	if (path.empty())
	{
		return;
	}
	int i = path.size() - 1;
	bool btag = true;
	while (i >= 0 && path[i] != '/')
	{
		btag = false;
		--i;
	}
	if (!btag)
	{
		std::string tmp = path;
		subtmp = tmp.assign(tmp, i + 1, tmp.size());
	}
}

void ZIP::GetZipNameFromPath(const std::vector<std::string> &ve, const std::string path, std::vector<std::string> &zipvector)//���ļ�������·��ve�а���Ҫѹ�����ļ�����Ϣ��ȡ����
{
	if (ve.empty() || path.empty())
	{
		return;
	}

	std::string l_subtmp;
	GetSubStr(path, l_subtmp);//l_subtmp = "SeewoService"

	std::string tmp = path;
	int i = tmp.size()+1;


	for (std::vector<std::string>::const_iterator it = ve.begin(); it != ve.end(); ++it)
	{
		std::string l_tmp;
		l_tmp = (*it).substr(i, (*it).size() - i);
		zipvector.push_back(l_tmp);
	}
}

ZIP::ZIP(const std::string &ppath, std::string &pzipfilename)//����һ��·������Ҫѹ�����ļ���·��
{
	if (ppath.empty() && pzipfilename.empty())
	{
		std::cout << "·������Ϊ��" << std::endl;
		return;
	}
	m_path = ppath;
	m_zipfilename = pzipfilename;
}


void ZIP::CreateMyZip()
{
	if (IsFolder())
	{
		ZipFolder();
	}
	else
	{
		ZipFile();
	}
}

ZIP::~ZIP()
{
}

void ZIP::ChangeSuffix(std::string &path, const std::string &suffix)//�ı��׺��
{
	char l_tmp[GLOBAL_TMP_LENGTH] = { 0 };
	int j = 0;
	for (int i = 0; i < path.size(); ++i)
	{
		if (path[i] != '.')
		{
			l_tmp[j] += path[i];
			j++;
		}
		else
		{
			break;
		}
	}
	strcat(l_tmp, suffix.c_str());
	path = l_tmp;
}

bool ZIP::IsFolder()//�ж��Ƿ�Ϊ�ļ���
{
	_chdir(m_path.c_str());
	long hFile;
	_finddata_t fileinfo;
	if ((hFile = _findfirst("*.*", &fileinfo)) != -1)
	{
		do
		{
			//����ǲ���Ŀ¼������Ƿ����棬������ļ����ؼ�
			if ((fileinfo.attrib & _A_SUBDIR) && (strcmp(fileinfo.name, ".") != 0) && (strcmp(fileinfo.name, "..") != 0)
				&& (strcmp(fileinfo.name, "Debug")))
			{
				return true;
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	return false;
}

void ZIP::ZipFolder()
{
	CStatDir statdir;
	if (!statdir.SetInitDir(m_path.c_str()))
	{
		puts("Ŀ¼�����ڡ�");
		return;
	}
	/////////////////////////////////////////////////////****************************%%%%%%%%%%%%%%%%%%%
	//const std::string str3 = "open";
	CString temp3 = m_zipfilename.c_str();
	LPCWSTR verb = (LPCWSTR)(temp3.AllocSysString());

	HZIP hz;
	hz = CreateZip(verb, (char *)0);

	std::vector<std::string> file_vec = statdir.BeginBrowseFilenames("*.*");
	std::vector<std::string>  zipnamevector;
	GetZipNameFromPath(file_vec, m_path, zipnamevector);
	std::vector<std::string>::iterator zt = zipnamevector.begin();
	int zi = 0;
	double numitems = file_vec.size() + 1;
	std::cout << "ѹ����ʼ" << std::endl;
	for (std::vector<std::string>::iterator it = file_vec.begin(); it < file_vec.end() && zt != zipnamevector.end(); ++it, ++zt)//�����ļ����е��ļ�
	{

		char *path = const_cast<char *>((*it).c_str());
		char *zippath = const_cast<char *>((*zt).c_str());

		/////////////////////////////////////////////////////****************************%%%%%%%%%%%%%%%%%%%
		CString temp3 = zippath;
		LPCWSTR zp = (LPCWSTR)(temp3.AllocSysString());

		CString temp = path;
		LPCWSTR pa = (LPCWSTR)(temp.AllocSysString());

		ZipAdd(hz, zp, pa);

		zi++;
		if (zi == numitems - 1)
		{
			zi += 1;
		}

		MoveCursor movecursor;
		COORD coord = movecursor.getxy();
		double tmpnum = (static_cast<double>(zi) / (static_cast<double>(numitems))) * 100;
		char input[10] = { 0 };
		sprintf(input, "%0.1f", tmpnum);
		strcat(input, "%");
		std::cout << input << "  ";
		if (zi == numitems - 1)
		{
			continue;
		}
		else
		{
			movecursor.gotoxy(coord.X, coord.Y);//�̶�����ȡ�Ĺ���λ��
		}
	}
	std::cout << std::endl;
	std::cout << "ѹ�����" << std::endl;
	CloseZip(hz);
}

void ZIP::ZipFile()
{
	HZIP hz;
	/////////////////////////////////////////////////////****************************%%%%%%%%%%%%%%%%%%%
	CString temp3 = m_zipfilename.c_str();
	LPCWSTR name = (LPCWSTR)(temp3.AllocSysString());

	hz = CreateZip(name, (char *)0);

	std::string subtmp;
	GetSubStr(m_path, subtmp);//��ȡ��Ҫѹ�����ļ���
	char *tmp = const_cast<char *>(subtmp.c_str());
	CString temp4 = tmp;
	LPCWSTR name1 = (LPCWSTR)(temp4.AllocSysString());

	CString temp = m_path.c_str();
	LPCWSTR pa = (LPCWSTR)(temp.AllocSysString());

	ZipAdd(hz, name1, pa);
	CloseZip(hz);
}


