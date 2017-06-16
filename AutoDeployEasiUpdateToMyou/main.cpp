#include <iostream>  
#include <string>

#include "Postpackage.h"
#include "Constant.h"

int main(int argc,char **argv)//appkey,path
{
	/*std::string appkey = "cf167a622948a3b42a7d7aacfcf3dd64f6e4d81b";
	std::string path("D://myouexefile/6.0/SeewoService");
*/
	std::string appkey;
	std::string path;

	for (int i = 1; i < argc; ++i)
	{
		if (i == 1)
		{
			appkey = argv[i];
		}
		else if (i == 2)
		{
			path = argv[i];
		}
	}
	
	if (appkey.empty() || path.empty())
	{
		std::cout << "Please Enter again" << std::endl;
		return 0;
	}
	/*std::cout << path << std::endl;
	std::cout << appkey << std::endl;*/
	PostPackage pack(path,appkey); 
	pack.PostToWeb();

	return 0;
}