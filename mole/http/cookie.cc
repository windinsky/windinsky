#ifndef __windinsky__http__cookie__cc__
#define __windinsky__http__cookie__cc__

#include "cookie.h"
#include "../lib/string_utils.cc"

using namespace std;

HttpCookie::HttpCookie(string cookie)
{
	size_t len = cookie.length();
	string delimiters = ";";
	if (len != 0)
	{
		vector<string> cookies = split(cookie,delimiters);
		vector<string>::iterator it = cookies.begin();
		for(;it != cookies.end() ;it++)
		{
			size_t divider = it->find('=');
			string key = it->substr(0,divider);
			string val = it->substr(divider+1,string::npos);
			set(key,val);
		}
	}
}
HttpCookie::~HttpCookie()
{

}

string HttpCookie::get(string key)
{
	map<string,string>::iterator it = m_cookie.find(key);
	if (it != m_cookie.end())
	{
		return it->second;
	}
	return "";
}

bool HttpCookie::set(
		string key,
		string val,
		unsigned int max_age,
		string domain,
		string path,
		string expires,
		bool http_only,
		bool secure
	)
{
	map<string,string>::iterator it = m_cookie.find(key);
	string _val = serialize_value(val,max_age,domain,path,expires,http_only,secure);
	if (it != m_cookie.end())
	{
		m_cookie[key] = _val;
	}
	else
	{
		m_cookie.insert(pair<string,string>(key,_val));
	}
	return false;
}

string HttpCookie::serialize_value(
		string val,
		unsigned int max_age,
		string domain,
		string path,
		string expires,
		bool http_only,
		bool secure
	)
{
	string result = val;
	if (max_age != 0)
	{
		char buffer[1024];
		sprintf(buffer,"%d",max_age);
		result += "; Max-age=" + string(buffer);
	}
	if (domain != "")
	{
		result += "; Domain=" + domain;
	}
	if (path != "/")
	{
		result += "; Path=" + path;
	}
	if (expires != "")
	{
		result += "; Path=" + path;
	}
	if (http_only)
	{
		result += "; HttpOnly";
	}
	if (secure)
	{
		result += "; Secure";
	}
	return result;
}
map<string,string> HttpCookie::cookies()
{
	return m_cookie;
}

#endif