#ifndef __windinsky__http__header__cc__
#define __windinsky__http__header__cc__

#include "header.h"
#include <iostream>
#include <vector>
#include "../lib/string_utils.cc"
using namespace std;

HttpHeader::HttpHeader(string header)
{
	int p = 0;
	int s = 0;
	string key = "";
	string val = "";

	std::vector<string> arr = split(header,"\r\n");
	std::vector<string>::iterator it = arr.begin();
	for(;it != arr.end();it++)
	{
		std::vector<string> pair = split(*it,": ");
		std::vector<string>::iterator _it = pair.begin();
		key = *_it;
		_it++;
		val = *_it;
		_set(key,val);
	}
	
	// map<string,string>::iterator it = m_header.begin();
	// for(;it != m_header.end();it++)
	// {
	// 	cout << it->first << "=" << it->second << endl;
	// }
}

HttpHeader::~HttpHeader()
{

}

bool HttpHeader::set(string key,string val)
{
	map<string,string>::iterator it = m_header.find(key);
	if (it != m_header.end())
	{
		m_header[key] = val;
		return false;
	}
	else
	{
		m_header.insert(pair<string,string>(key,val));
		return true;
	}
}

void HttpHeader::_set(string key,string val)
{
	// cout << key << "=" << val << endl;
	m_header.insert(pair<string,string>(key,val));
}

string HttpHeader::get(string key)
{
	map<string,string>::iterator it = m_header.find(key);
	if (it != m_header.end())
	{
		return m_header[key.c_str()];
	}
	else
	{
		return "";
	}
}

string HttpHeader::_get(string key)
{
	return m_header[key.c_str()];
}

string HttpHeader::serialize()
{
	string result = "";
	map<string,string>::iterator it = m_header.begin();
	size_t i = 0;
	for(;it != m_header.end();it++,i++)
	{
		result += it->first + ": " + it->second;
		if (i != m_header.size() - 1)
		{
			result += "\n\r";
		}
	}
	return result;
}

#endif