#include "Changejson.h"

ChangeJson::ChangeJson(const std::string &jsonfile, Json::Value &tmp)
{
	m_jsonfile = jsonfile;
	m_mp = tmp;
}

bool ChangeJson::WillChange(const std::string &versionname, const std::string &versionnum)
{
	if (read_json())
	{
		/*std::cout <<m_mp << std::endl;
		std::cout << "ok" << std::endl;*/
	}
	else
	{
		return false;
	}
	m_mp[versionname] = versionnum;
	std::cout << "json�޸ĳɹ�" << std::endl;
	if (write_jscon())
	{
		/*std::cout << m_mp << std::endl;
		std::cout << "ok" << std::endl;*/
	}
	else
	{
		return false;
	}
	std::cout << "json successful" << std::endl;
	return true;
}

bool ChangeJson::write_jscon()
{
	std::cout << "��json����д�뵽json�ļ���" << std::endl;
	if (m_jsonfile.empty())
	{
		return false;
	}

	std::ofstream out_json(m_jsonfile);
	if (!out_json)
	{
		return false;
	}

	Json::StyledStreamWriter writer;
	writer.write(out_json, m_mp);

	out_json.close();
	std::cout << "д�����" << std::endl;
	return true;
}

bool ChangeJson::read_json()
{
	std::cout << "��json�ļ�����json������" << std::endl;
	std::ifstream in_file(m_jsonfile, std::ios::out | std::ios::binary);
	if (m_jsonfile.empty())
	{
		return false;
	}

	if (!Json::Reader().parse(in_file, m_mp))
	{
		in_file.close();
		return false;
	}

	in_file.close();
	std::cout << "�������" << std::endl;
	return true;	
}