#ifndef _CONNECTSQL_H_
#define _CONNECTSQL_H_

#include <Windows.h>
#include <sqlext.h>
#include <cstdio>
#include <string>


class ConnectSql {
private:
	SQLHENV     henv;
	SQLHDBC     hdbc;
public:
	SQLHSTMT connectSql(std::string);
	~ConnectSql();

};


#endif // _CONNECTSQL_H_
