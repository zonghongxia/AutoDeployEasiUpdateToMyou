#ifndef _CHANGEJSON_H
#define _CHANGEJSON_H

#include <iostream>
#include <string>
#include <fstream>

#include <json/autolink.h>  
#include <json/config.h>
#include <json/features.h>  
#include <json/forwards.h>
#include <json/json.h>   
#include <json/reader.h>  
#include <json/value.h>
#include <json/writer.h>  

class ChangeJson
{
public:
	ChangeJson(const std::string &jsonfile, Json::Value &tmp);

	bool WillChange(const std::string &versionname, const std::string &versionnum);
private:
	bool write_jscon();

	bool read_json();

	std::string m_jsonfile;
	Json::Value m_mp;
};

#endif
