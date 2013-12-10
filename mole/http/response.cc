#ifndef __windinsky__response__cc__
#define __windinsky__response__cc__

#include "response.h"
#include <time.h>
#include <stdio.h>

HttpResponse::HttpResponse()
{
	cookie = new HttpCookie();
	header = new HttpHeader();
	http_version = "HTTP/1.1";
}

HttpResponse::~HttpResponse()
{
	cookie = NULL;
	header = NULL;
	delete cookie;
	delete header;
}

string HttpResponse::serialize(string code, string reason, string body)
{
	int content_length = body.length();
	char buffer[1024];
	std::sprintf(buffer,"%d",content_length);
	header->set("Content-Length", string(buffer));
	
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	char t_buf[128];
	std::sprintf (t_buf, "%s", asctime (timeinfo) );
	header->set("Date",string(t_buf));

	header->set("Content-Type","application/json;charset=utf-8");
	
	

	string res = "";
	res += http_version + " ";

	if (code == "")
	{
		res += "200 ";
	}
	else
	{
		res += code + " ";
	}
	
	res += reason + "\n\r";
	res += header->serialize();
	
	map<string,string> cookies = cookie->cookies();
	map<string,string>::iterator it = cookies.begin();
	for(;it != cookies.end();it++)
	{
		res += string("\n\r") + "Set-Cookie: " + it->first + "=" + it->second;
	}
	res += "\n";
	res += body;
	cout << res << endl;
	return res;
}

void HttpResponse::set_header(string key,string val)
{
	header->set(key,val);
}

#endif