#include "ExtractVersion.h"

void ExtractVersion::GetVersion(const std::string &path, std::string &version)
{
	if (path.empty())
	{
		std::cout << "path is empty" << std::endl;
		return;
	}
	int firstindex = 0;
	int lastindex = 0;
	bool btag = false;
	for (int i = path.size() - 1; i >= 0; --i)
	{
		if (!btag   &&  path[i] == '.')
		{
			lastindex = i - 1;
			btag = true;
		}
		if (path[i] == '_')
		{
			firstindex = i + 1;
			break;
		}
	}
	std::string tmp = path;
	version = tmp.assign(tmp, firstindex, lastindex - firstindex + 1);
}