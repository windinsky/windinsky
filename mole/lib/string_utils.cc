#ifndef __windinsky__string__utils__
#define __windinsky__string__utils__

#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

vector<string> split(string str,string delimiters)
{
	size_t start = 0;
	size_t end = 0;
	size_t len = str.length();

	std::vector<string> res;
	while( start < len )
	{
		end = str.find ( delimiters , start );
		if (end == string::npos)
		{
			res.push_back(str.substr(start,len-start));
			break;
		}
		res.push_back(str.substr(start,end-start));
		start = end + string(delimiters).length();
	}
	return res;
}

string join(vector<string> arr, string delimiters)
{
	string result = "";
	size_t i = 0;
	for (std::vector<string>::iterator it = arr.begin() ; it != arr.end() ; it ++)
	{
		result += *it;
		i++;
		if (i != arr.size())
		{
			result += delimiters;
		}
	}
	return result;
}

#endif