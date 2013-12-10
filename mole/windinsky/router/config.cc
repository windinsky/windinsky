#ifndef __windinsky__router__config__
#define __windinsky__router__config__

#include <map>
#include <string>
#include "fcgio.h"
#include "../../interface/interface.all"
using namespace std;

typedef string (*func_pointer)(FCGX_Request*);

std::map<std::string,func_pointer> cfg;

void register_routers()
{
	cfg.insert(std::make_pair("/test/",&(user::index)));
}


#endif