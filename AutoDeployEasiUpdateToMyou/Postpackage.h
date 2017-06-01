#include<windows.h> 
#include <iostream>  
#include <direct.h>
#include <string>
#include <string.h>
#include <atlstr.h>
#include <direct.h>

#include "PostFiletoWeb.h"
#include "SilentInstallation.h"
#include "GetExeFile.h"
#include "ExtractVersion.h"
#include  "Changejson.h"
#include "CopyFile.h"
#include "myzip.h"
#include "GetCookie.h"
#include "md5.h"
#include "deletefile.h"
#include "Constant.h"

static std::string myouurl = "http://myou.cvte.com/api/in/policy/windowsapp/:appKey/version/upload";
static const std::string myouappkey = ":appKey";


class PostPackage
{
public:
	PostPackage(const std::string &path,const std::string &appkey);
	void PostToWeb();
private:
	std::string m_path;
	std::string m_appkey;
};
