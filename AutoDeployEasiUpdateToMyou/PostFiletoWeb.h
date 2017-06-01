#ifndef _POSTFILETOWEB_H
#define _POSTFILETOWEB_H

#include <iostream>
#include <curl/curl.h>
#include <string>
#include "Move_Cursor.h"
#include "Constant.h"

typedef struct Post_Node
{
	const std::string m_cvteurl;
	const std::string m_cookie;
	const std::string m_zipfilename;
	const std::string m_zipfilepath;
	const std::string m_exefilename;
	const std::string m_exefilepath;
	const std::string m_exemd5;
	const std::string m_zipmd5;
}Post_Node;

struct myprogress//������
{
	double lastruntime;
	CURL *curl;
};

class PostFiletoWeb
{
public:
	PostFiletoWeb(Post_Node * node);
	~PostFiletoWeb();

	void PostToWeb();

	//static void GetZipPath(std::string &path);
private:
	//static const std::string S_SUFFIX_RENAME;
	static int older_progress(void *p, double dltotal, double dlnow, double ultotal, double ulnow);//�ص�����
	static size_t CallBackWrite(const char *data, size_t size, int nmember, std::string  * strData);//д�����ݵĻص�����
	Post_Node *m_node;
	static bool m_btag;
};

#endif
