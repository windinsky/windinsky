#include "request.h"
#include <iostream>
#include "../lib/string_utils.cc"


using namespace std;

HttpRequest::HttpRequest(string http)
{
	string body_delimiters = "\r\n\r\n";
	string http_header_delimiter = "\r\n";
	string http_line_delimiter = " ";

	std::vector<string> arr = split(http,body_delimiters);

	string before_body = *(arr.begin());
	// vector<string> headers = split(before_body,http_header_delimiter);

	size_t temp = before_body.find(http_header_delimiter);
	
	string request_line = before_body.substr(0,temp);
	string http_header = before_body.substr(temp+http_header_delimiter.length(),string::npos);
	
	vector<string> http_info = split(request_line,http_line_delimiter);

	std::vector<string>::iterator it = http_info.begin();

	method = *it;
	it++;
	uri = *it;
	it++;
	http_version = *it;

	header = new HttpHeader(http_header);
	cookie = new HttpCookie(header->get("Cookie"));


	map<string,string> cookies = cookie->cookies();
	for(map<string,string>::iterator it = cookies.begin();it!=cookies.end();it++)
	{
		cout << it->first << "," << it->second << endl;
	}
}

HttpRequest::~HttpRequest()
{

}