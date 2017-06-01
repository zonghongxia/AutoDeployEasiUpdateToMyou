#include "PostFiletoWeb.h"

bool PostFiletoWeb::m_btag = false;

PostFiletoWeb::PostFiletoWeb(Post_Node * const node)
{
	if (NULL == node)
	{
		std::cout << "Please delivery vaild data" << std::endl;
		exit(1);
	}
	m_node = node;
}

PostFiletoWeb::~PostFiletoWeb()
{
	m_btag = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////

int PostFiletoWeb::older_progress(void *p, double dltotal, double dlnow, double ultotal, double ulnow)
{
	if ((ulnow == ultotal && ulnow == 0) || (dltotal != 0 && dlnow != 0))
	{
		;
	}
	else if (ulnow == ultotal && dltotal == 0 && dlnow == 0 && !m_btag)
	{
		std::cout << std::endl;
		m_btag = true;
	}
	else
	{
		MoveCursor movecursor;
		COORD coord = movecursor.getxy();
		double tmpnum = (ulnow / ultotal) * 100.0;
		char input[10] = { 0 };
		sprintf(input, "%0.1f", tmpnum);
		input[strlen(input)] = '%';
		input[strlen(input)] = '\0';

		/*std::cout << input << std::endl;*/
		std::cout << input << "   ";
		movecursor.gotoxy(coord.X, coord.Y);
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////

size_t PostFiletoWeb::CallBackWrite(const char *data, size_t size, int nmember, std::string  * strData)//写入数据的回调函数
{
	size_t sizes = size * nmember;
	strData->append(data, sizes);
	return sizes;
}
////////////////////////////////////////////////
void PostFiletoWeb::PostToWeb()
{
	CURL* curl;
	struct curl_httppost *formpost = NULL;
	struct curl_httppost *lastptr = NULL;
	struct curl_slist* headerlist = NULL;

	curl_formadd
	(
		&formpost,
		&lastptr,
		CURLFORM_COPYNAME,
		m_node->m_zipfilename.c_str(),
		CURLFORM_FILE,
		m_node->m_zipfilepath.c_str(),
		CURLFORM_CONTENTTYPE, zipfilecontent.c_str(),
		CURLFORM_END
	);

	curl_formadd
	(
		&formpost,
		&lastptr,
		CURLFORM_COPYNAME,
		m_node->m_exefilename.c_str(),
		CURLFORM_FILE,
		m_node->m_exefilepath.c_str(),
		CURLFORM_CONTENTTYPE, exefilecontent.c_str(),
		CURLFORM_END
	);

	curl_formadd
	(
		&formpost,
		&lastptr,
		CURLFORM_COPYNAME,
		exemd5name.c_str(),
		CURLFORM_COPYCONTENTS,
		m_node->m_exemd5.c_str(),
		CURLFORM_END
	);

	curl_formadd
	(
		&formpost,
		&lastptr,
		CURLFORM_COPYNAME,
		zipmd5name.c_str(),
		CURLFORM_COPYCONTENTS,
		m_node->m_zipmd5.c_str(),
		CURLFORM_END
	);

	/*curl_formadd
	(
		&formpost,
		&lastptr,
		CURLFORM_COPYNAME,
		zipmd5name.c_str(),
		CURLFORM_COPYCONTENTS,
		"550e7c643493034189a32a6abd6bfa19",
		CURLFORM_END
	);*/

	curl_formadd
	(
		&formpost,
		&lastptr,
		CURLFORM_COPYNAME,
		updatename.c_str(),
		CURLFORM_COPYCONTENTS,
		updatecontent.c_str(),
		CURLFORM_END
	);

	curl_formadd
	(
		&formpost,
		&lastptr,
		CURLFORM_COPYNAME,
		iskeyname.c_str(),
		CURLFORM_COPYCONTENTS,
		biskey,
		CURLFORM_END
	);

	curl = curl_easy_init();

	std::string strHeader;
	CURLcode res = CURLE_OK;
	if (curl)
	{
		if (res == CURLE_OK) res = curl_easy_setopt(curl, CURLOPT_URL, cvte_url.c_str());
		if (res == CURLE_OK) res = curl_easy_setopt(curl, CURLOPT_COOKIE, m_node->m_cookie.c_str());

		curl_slist_append(headerlist, headerlistcontent.c_str());
		curl_slist_append(headerlist, headerlistcontent2.c_str());
		if (res == CURLE_OK) res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);

		if (res == CURLE_OK) res = curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
		if (res == CURLE_OK) res = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);

		if (res == CURLE_OK) res = curl_easy_setopt(curl, CURLOPT_HEADERDATA, &strHeader);          //将响应头部信息保存到strRecvData
		if (res == CURLE_OK) res = curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, CallBackWrite);

		/****************************************************************************/

		struct myprogress prog;

		prog.lastruntime = 0;
		prog.curl = curl;

		if (res == CURLE_OK) res = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
		if (res == CURLE_OK) res = curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, older_progress);
		if (res == CURLE_OK) res = curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, &prog);

		if (res == CURLE_OK) res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		if (res == CURLE_OK) res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		if (res == CURLE_OK) res = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);

		if (res == CURLE_OK) res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);

		curl_formfree(formpost);
		std::cout << strHeader << std::endl;
	}
}
