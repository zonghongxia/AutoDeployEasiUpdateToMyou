#include "Postpackage.h"

PostPackage::PostPackage(const std::string &path, const std::string &appkey)
{
	m_path = path;
	m_appkey = appkey;
}
void PostPackage::PostToWeb()
{
	std::string url = myouurl;
	size_t tnum = url.find(myouappkey);
	const_cast<std::string &>(url).replace(tnum, myouappkey.size(), m_appkey);

	//std::string appkey = "cf167a622948a3b42a7d7aacfcf3dd64f6e4d81b";
	//获取当前目录下的最新版本
	//std::string tp("D://myouexefile/6.0/SeewoService");
	GetRecentExeFile getfilename(m_path);
	std::string str;
	getfilename.GetFilename(str);
	std::cout << str << std::endl;

	//从路径中提取版本号
	std::string version;
	ExtractVersion ver;
	ver.GetVersion(str, version);
	std::cout << "version:" << version << std::endl;

	//更改json文件中的版本号
	Json::Value tmp;
	ChangeJson json(jsonpath, tmp);
	if (json.WillChange(versionname, version))
	{
		std::cout << "json ok" << std::endl;
	}

	//静默安装
	StringNode node = { str,str2,str3,str4,str5 };
	SilentInstallation nnode(&node);
	std::string installationpath;
	nnode.Run(installationpath);
	std::cout << "静默安装的路径=" << installationpath << std::endl;

	//复制json文件到安装目录下
	std::string sour = jsonpath;
	std::cout << "sour=" << sour << std::endl;
	std::string des = installationpath;
	des += "\\";
	des += jsonpath;
	std::cout << "des=" << des << std::endl;
	CopyJsonFile copyfile(sour, des);
	if (copyfile.Copy())
	{
		std::cout << "ok" << std::endl;
	}

	//压缩
	Drive dr;
	std::string drive;
	dr.GetDrive(drive);//获取盘符
	if (drive.empty())
	{
		std::cout << "用户没有合适的盘符" << std::endl;
		return ;
	}
	std::string zippath = drive+ myzipname;
	//std::string zippath = "D://SeewoService";
	zippath += version;
	zippath += ".zip";
	ZIP zip(installationpath, zippath);
	zip.CreateMyZip();

	//计算MD5值
	const std::string exepath = str;
	std::cout << "exepath=" << exepath << std::endl;
	MD5_CTX mdexe;
	char buf[MY_BUFSIZE] = { 0 };
	mdexe.GetFileMd5(buf, exepath.c_str());
	const std::string exemd5 = buf;
	std::cout << exemd5 << std::endl;

	const std::string _zippath = zippath;
	//std::cout << "_zippath=" << _zippath << std::endl;
	MD5_CTX mdzip;
	char buf2[MY_BUFSIZE] = { 0 };
	mdzip.GetFileMd5(buf2, _zippath.c_str());
	const std::string zipmd5 = buf2;
	std::cout << zipmd5 << std::endl;

	//上传


	GetCookie  gcookie(getcookieurl, userpassword, contenttype);
	std::string cookie = gcookie.GetCookies();
	std::cout << cookie << std::endl;

	std::cout << "上传开始" << std::endl;
	Post_Node postnode = { url ,cookie ,zipfilename ,zippath ,exefilename ,str ,exemd5 ,zipmd5 };
	PostFiletoWeb web(&postnode);
	web.PostToWeb();
 	std::cout << "上传完毕" << std::endl;


	//删除产生的zip文件
	DeleteFolderorFile deletefolder(zippath);
	deletefolder.DeleteDir();
}

	