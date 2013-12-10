#ifndef __windinsky_migration__
#define __windinsky_migration__

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <fstream>
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
	ifstream file;
	file.open("config/sql.in");
	string buffer = "";
	string line = "";
	while(getline(file,line))
	{
		// cout << line << endl;
		if (line == "")
		{
			sqls.push_back(buffer);
		}
		else
		{
			buffer += line;
		}
	}
	sqls.push_back(buffer);
	return sqls.size() ? true : false;
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