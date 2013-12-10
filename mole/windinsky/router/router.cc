#ifndef __windinsky__router__
#define __windinsky__router__

#include "fcgio.h"
#include "config.cc"
#include "../../lib/fcgi_utils.cc"
using namespace std;

class Router
{
public:
	Router();
	~Router();
	string process(FCGX_Request* request);
};

Router::Router()
{

}

Router::~Router()
{

}

string Router::process(FCGX_Request* request)
{
	register_routers();
	string url = fcgi_utils::get_param("URL_PARA",request);
	map<string,func_pointer>::iterator it = cfg.find(url);
	if (it == cfg.end())
	{
		return "Status 404 NOT FOUND";
	}
	else
	{
		return it->second(request);
	}
}

#endif