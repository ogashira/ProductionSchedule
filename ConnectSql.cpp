#include "ConnectSql.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <stdexcept>
#include <windows.h>
#include "StringUtils.h"


SQLHSTMT ConnectSql::connectSql(std::string dataName)
{
	SQLHSTMT    hstmt;
	SQLRETURN   nResult;
	SQLSMALLINT nSize;
	TCHAR       szState[6]{};
	TCHAR       szErrorMsg[1024]{};
	SQLINTEGER  nErrorCode;
	SQLTCHAR    szConnStrOut[1024]{};
	SQLSMALLINT cchConnStrOut = 0;

	nResult = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &this->henv);
	if (nResult != SQL_SUCCESS && nResult != SQL_SUCCESS_WITH_INFO)
		return 0;

	nResult = SQLSetEnvAttr(this->henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	if (nResult != SQL_SUCCESS && nResult != SQL_SUCCESS_WITH_INFO) {
		SQLFreeHandle(SQL_HANDLE_ENV, this->henv);
		return 0;
	}

	nResult = SQLAllocHandle(SQL_HANDLE_DBC, this->henv, &this->hdbc);
	if (nResult != SQL_SUCCESS && nResult != SQL_SUCCESS_WITH_INFO) {
		SQLFreeHandle(SQL_HANDLE_ENV, this->henv);
		return 0;
	}
	

	//--- Read connection string from file ---
	// The file path contains Japanese characters, so we use a wide string.
    std::wstring pass_path = L"//192.168.1.247/‹¤—L/‹Zp‰ÛÌ«ÙÀÞ/Ï¸Û/init/ConnectSqlCpp_TSS_pass.txt";
	
    std::ifstream ifs(pass_path);
    if (!ifs.is_open()) {
        // For the error message, we convert the wide path back to a string for the exception.
        std::string pass_path_s = WideToCp932(pass_path);
        std::string err_msg = "Could not open connection string file: " + pass_path_s;
        throw std::runtime_error(err_msg);
    }

    std::string line; 
    std::getline(ifs, line);
    ifs.close();

    // Convert the connection string (assumed to be CP932/Shift_JIS) to a wstring (UTF-16) for the ODBC driver
    std::wstring w_line = Cp932ToWide(line);

	nResult = SQLDriverConnect(this->hdbc, NULL, (SQLTCHAR*)w_line.c_str(),
		SQL_NTS,(SQLTCHAR*)szConnStrOut,sizeof(szConnStrOut)/sizeof(SQLTCHAR), &nSize, SQL_DRIVER_NOPROMPT);

	if (nResult != SQL_SUCCESS && nResult != SQL_SUCCESS_WITH_INFO) {
		SQLGetDiagRec(SQL_HANDLE_DBC, this->hdbc, 1, (SQLTCHAR*)szState, &nErrorCode, (SQLTCHAR*)szErrorMsg, sizeof(szErrorMsg) / sizeof(TCHAR), &nSize);
		MessageBox(NULL, szErrorMsg, NULL, MB_ICONWARNING);
		SQLFreeHandle(SQL_HANDLE_DBC, this->hdbc);
		SQLFreeHandle(SQL_HANDLE_ENV, this->henv);
		std::cout << dataName << "Ú‘±Ž¸”s" << std::endl;
		return 0;
	}
	else {
		std::cout << dataName << "Ú‘±¬Œ÷" << std::endl;
	}

	nResult = SQLAllocHandle(SQL_HANDLE_STMT, this->hdbc, &hstmt);
	if (nResult != SQL_SUCCESS && nResult != SQL_SUCCESS_WITH_INFO) {
		SQLFreeHandle(SQL_HANDLE_DBC, this->hdbc);
		SQLFreeHandle(SQL_HANDLE_ENV, this->henv);
		return 0;
	}

	return hstmt;

}

ConnectSql::~ConnectSql() {
	if (hdbc != SQL_NULL_HDBC) {
		SQLDisconnect(hdbc);
		SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
	}
	if (henv != SQL_NULL_HENV) {
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
	}
}
