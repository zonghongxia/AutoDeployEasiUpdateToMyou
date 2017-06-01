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

int main()
{
	//��ȡ��ǰĿ¼�µ����°汾
	std::string tp("D://myouexefile/6.0/SeewoService");
	GetRecentExeFile getfilename(tp);
	std::string str;
	getfilename.GetFilename(str);
	std::cout << str << std::endl;

	//��·������ȡ�汾��
	std::string version;
	ExtractVersion ver;
	ver.GetVersion(str, version);
	std::cout << "version:" << version << std::endl;

	//����json�ļ��еİ汾��
	Json::Value tmp;
	ChangeJson json(jsonpath, tmp);
	if (json.WillChange(versionname, version))
	{
		std::cout << "ok" << std::endl;
	}

	//��Ĭ��װ
	StringNode node = { str,str2,str3,str4,str5 };
	SilentInstallation nnode(&node);
	std::string installationpath;
	nnode.Run(installationpath);
	std::cout <<"��Ĭ��װ��·��="<< installationpath << std::endl;

	//����json�ļ�����װĿ¼��
	std::string sour = jsonpath;
	std::cout << "sour=" << sour << std::endl;
	std::string des = installationpath;
	des += "\\";
	des += jsonpath;
	std::cout << "des=" << des << std::endl;
	CopyJsonFile copyfile(sour,des);
	if (copyfile.Copy())
	{
		std::cout << "ok" << std::endl;
	}

	//ѹ��
	std::string zippath = "D://SeewoService";
	zippath += version;
	zippath += ".zip";
	ZIP zip(installationpath,zippath);
	zip.CreateMyZip();

	//����MD5ֵ
	//std::string str("D://myouexefile/6.0/SeewoService/SeewoServiceSetup_6.1.3.2590.exe");
	//std::string zippath("D://SeewoService6.1.3.2590.zip");

	const std::string exepath = str;
	std::cout << "exepath="<<exepath << std::endl;
	MD5_CTX mdexe;
	char buf[MY_BUFSIZE] = { 0 };
	mdexe.GetFileMd5(buf, exepath.c_str());
	const std::string exemd5 = buf;
	std::cout << exemd5 << std::endl;

	const std::string _zippath = zippath;
	std::cout << "_zippath=" << _zippath << std::endl;
	MD5_CTX mdzip;
	char buf2[MY_BUFSIZE] = { 0 };
	mdzip.GetFileMd5(buf2, _zippath.c_str());
	const std::string zipmd5 = buf2;
	std::cout << zipmd5 << std::endl;

	//�ϴ�
	GetCookie  gcookie(getcookieurl, userpassword, contenttype);
	std::string cookie = gcookie.GetCookies();
	std::cout << cookie << std::endl;

	Post_Node postnode = { cvte_url ,cookie ,zipfilename ,zippath ,exefilename ,str ,exemd5 ,zipmd5 };
	PostFiletoWeb web(&postnode);
	web.PostToWeb();

	//ɾ��������zip�ļ�
	DeleteFolderorFile deletefolder(zippath);
	deletefolder.DeleteDir();

	return 0;
}