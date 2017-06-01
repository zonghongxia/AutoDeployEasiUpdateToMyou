#ifndef _CONSTANT_H
#define _CONSTANT_H

//const int  MY_BUFSIZE = 256;

//静默安装的参数
const std::string str2 = "/S";//静默安装的命令行参数
const std::string str3 = "runas";//静默安装的打开方式
const std::string str4 = "SOFTWARE\\Seewo\\SeewoService";//打开注册表的子健
const std::string str5 = "path";//获取安装路径

//json文件所在位置
const std::string jsonpath = "VersionConfig.json";//json文件所在目录
const std::string versionname = "version";//所要修改的json文件中的字段的值

//获取cookie时的参数
const std::string getcookieurl = "https://myou.cvte.com/api/in/auth/login";
const std::string userpassword("{\"loginName\":\"iip.fwq\", \"password\":\"11111111\"}");//设置用户名和密码
const std::string contenttype("Content-Type:application/json;charset=UTF-8");//设置头部信息的Content_Type字段

//上传文件时的参数
//const std::string updatename("updateDesc");
//const std::string updatecontent("new version");
//const std::string iskeyname("isKeyVersion");
//const bool biskey = false;
//const std::string headerlistcontent("Content-Type:mutipart/form-data");
//const std::string headerlistcontent2("Accept:application/json");
//const std::string zipfilecontent("application/octet-stream");
//const std::string exefilecontent("application/x-msdownload");
//const std::string zipfilename("zipFile");
//const std::string exefilename("exeFile");
//const std::string zipmd5name("zipMd5");
//const std::string exemd5name("exeMd5");

//const std::string cvte_url = "http://myou.cvte.com/api/in/policy/windowsapp/cf167a622948a3b42a7d7aacfcf3dd64f6e4d81b/version/upload";

#endif
