#ifndef __windinsky__request__
#define __windinsky__request__


#include <string>
#include <map>
#include "header.cc"
#include "cookie.cc"
using namespace std;

class HttpRequest
{
public:
	HttpRequest(string http);
	~HttpRequest();

	// http request line
	string uri;
	string method;
	string http_version;
	// http header
	HttpHeader* header;
	// cookie
	HttpCookie* cookie;
};

#endif