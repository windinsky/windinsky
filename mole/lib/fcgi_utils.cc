#ifndef __windinsky__fcgi_utils__
#define __windinsky__fcgi_utils__

#include <string>
#include "fcgio.h"

using namespace std;

namespace fcgi_utils
{
	string get_param(string param_name, FCGX_Request* request)
	{
		char value[1024];
		sprintf(value,"%s",FCGX_GetParam(param_name.c_str(), request->envp));
	    return value;
	}
}


#endif