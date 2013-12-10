#ifndef __windinsky__response__
#define __windinsky__response__

#include <string>
#include <map>
#include "header.cc"
#include "cookie.cc"

using namespace std;

class HttpResponse
{
public:
	HttpResponse();
	~HttpResponse();

	string http_version;

	HttpHeader* header;
	HttpCookie* cookie;
	// string serialize();
	string serialize(string code, string reason, string _body = "");
	void set_header(string key,string val);
};

#endif