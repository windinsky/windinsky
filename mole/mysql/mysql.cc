#ifndef __windinsky__mysql__adapter__
#define __windinsky__mysql__adapter__
#include "mysql/mysql.h"
#include <string>

using namespace std;

class MysqlAdapter
{
public:
	MysqlAdapter();
	~MysqlAdapter();
	bool createTable(string table_name);
	bool dropTable(string table_name);
private:
	MYSQL* m_mysql;
};

MysqlAdapter::MysqlAdapter()
{
	m_mysql = new MYSQL();
	mysql_init(m_mysql);
	mysql_real_connect(&m_mysql, "127.0.0.1", "root", "root", "test", 3306, NULL, 0)
}


#endif