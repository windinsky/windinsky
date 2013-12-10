#ifndef __windinsky__controller__user__
#define __windinsky__controller__user__

#include "fcgio.h"
#include <string>
#include "../lib/fcgi_utils.cc"
#include "mysql/mysql.h"
using namespace std;

namespace user
{
	string index(FCGX_Request* request)
	{
		MYSQL mysql;
		mysql_init(&mysql);
		mysql_real_connect(&mysql, "127.0.0.1", "root", "root", "test", 3306, NULL, 0);

		string url = fcgi_utils::get_param("URL_PARA",request);
		char response[1024];
		sprintf(
			response,
			"Content-type: application/json\r\n"\
	        "\r\n"\
	        "{\"a\":1}\n"
        );
        return response;
	}
	string add()
	{
		return "";
	}
};

#endif