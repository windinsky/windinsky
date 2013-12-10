#ifndef __windinsky__http__header__
#define __windinsky__http__header__


#include <map>
#include <string>

using namespace std;

class HttpHeader
{
public:
	HttpHeader(string header = "");
	~HttpHeader();

	bool set(string key,string val);
	string get(string key);
	string serialize();
private:
	
	void _set(string key,string val);
	string _get(string key);

	map<string,string> m_header;
};

#endif