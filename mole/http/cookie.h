/*
	Author: ningbowang
	Date: 2013/11/30
*/

#ifndef __windinsky__http__cookie__
#define __windinsky__http__cookie__

#include <iostream>

/*
	Notes: 
		Max-Age: deault 0, milisecods(unsigned int), indicate how long the cookie will be expired after response
			* Max-Age is not supported in IE8 & older. So if you want your cookie expires as expected in those browsers, use Expires

		Expires: default "", GMT format string, indicate when will the cookie expired

		Domain: default "", string, if you set the domain as "www.yourhost.com", then only the request with "Host: www.yourhost.com" can access this cookie.
				however if you set it as ".yourhost.com",then all "whatever.yourhost.com" can access it

		Path: default "", string, if you set it as "/", then every folder under your host can access it, otherwise only the path you signed can access.

		HttpOnly:default false, bool, if you don't want the browser scrpits access it, use it.

		Secure: default false, bool, you cookie will be only transfered in https protocal
*/


#include <string>
#include <map>

using namespace std;

class HttpCookie
{
public:
	
	HttpCookie(string cookie = "");
	~HttpCookie();

	string get(string key);

	/*
		set a cookie's value, only used in http response

		Example:
			set(
				"cookie_name",
				"cookie_value",
				25292000000,
				".windinsky.com",
				"/",
				"Sat, 30 Nov 2013 04:31:24 GMT",
				true,
				true
			)
		This will generate a map<string,string> type cookie instance into m_cookie like this:
		<"cookie_name","cookie_value; Max-Age=25292000000; Domain=.windinsky.com; Path=/; expires=Sat, Sat, 30 Nov 2013 04:31:24 GMT; HttpOnly; Secure">
		After you send this back to browser, it will create a cookie named cookie_name, values cookie_value, expires at the earlier one between 
		Sat, Sat, 30 Nov 2013 04:31:24 GMT and your current time add 25292000000 milisecods, can accessed by <whatever>.weillyer.com,it can't accessed by
		client scripts. and only transfered in https protocal
	*/
	bool set(
		string key,
		string val,
		unsigned int max_age = 0,
		string domain="",
		string path="/",
		string expires="",
		bool http_only=false,
		bool secure=false
	);
	/* 
		format the cookie infomation into string.
		serialize_value(
			"cookie_value",
			25292000000,
			".windinsky.com",
			"/",
			"Sat, 30 Nov 2013 04:31:24 GMT",
			true,
			true
		)
		//=> "cookie_value; Max-Age=25292000000; Domain=.windinsky.com; Path=/; expires=Sat, Sat, 30 Nov 2013 04:31:24 GMT; HttpOnly; Secure"
	*/
	string serialize_value(
		string val,
		unsigned int max_age = 0,
		string domain="",
		string path="/",
		string expires="",
		bool http_only=false,
		bool secure=false
	);
	//return all cookies
	map<string,string> cookies();
	// string serialize();
	
private:
	map<string,string> m_cookie;
};


#endif
