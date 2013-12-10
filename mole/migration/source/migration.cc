#ifndef __windinsky_migration__
#define __windinsky_migration__

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
// #include <dir.h>
#include "mysql/mysql.h"



using namespace std;

typedef vector<string> stringVec;

int GetCurrentVersion()
{
	std::vector<char> v;
	if (FILE *fp = fopen("config/version", "r"))
	{
		char buf[1024];
		fread(buf, 1, sizeof(buf), fp);
		return atoi(buf);
	}
	return -1;
}

bool GetSQL(stringVec& sqls)
{
	if (FILE *fp = fopen("config/sql.in", "r"))
	{
		string buffer = "";
		char buf[1];
		bool _break = false;
		while (size_t len = fread(buf, 1, sizeof(buf), fp))
		{
			
			if (strcmp(buf,"\n") == 0)
			{
				// cout << "\\n"<<endl;
				if (_break)
				{
					sqls.insert(sqls.end(),buffer);
					_break = false;
				}
				else
				{
					_break = true;
				}
			}
			else
			{
				// cout << buf << endl;
				_break = false;
				buffer += buf;
			}
		}
		sqls.insert(sqls.end(),buffer);
		fclose(fp);
		return true;
	}
	return false;
}

// string readFile(fileName)
// {

// }



int main()
{
	MYSQL mysql;
	mysql_init(&mysql);
	mysql_real_connect(
		&mysql,
		"localhost",
		"root",
		"",
		"windinsky",
		3306,
		NULL,
		0
	);
	// string sql = "";
	stringVec sqls;
	GetSQL(sqls);
	stringVec::iterator it = sqls.begin();
	for(;it != sqls.end();it++)
	{
		cout << it->c_str() << endl;
		mysql_query(&mysql,it->c_str());
	}
	mysql_close(&mysql);

	
	return 0;
}


#endif