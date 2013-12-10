#ifndef __windinsky__core__
#define __windinsky__core__
#include "fcgio.h"
#include "./router/router.cc"

class Windinsky
{
public:
	Windinsky();
	~Windinsky();
	string process(FCGX_Request* request);
	Router* m_router;
};

Windinsky::Windinsky()
{
	m_router = new Router();
}

Windinsky::~Windinsky()
{
	// m_router = null;
	delete m_router;
}

string Windinsky::process(FCGX_Request* request)
{
	return m_router->process(request);
}

#endif