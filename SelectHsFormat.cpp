#include "SelectHsFormat.h"
#include <windows.h>

void SelectHsFormat::ExecuteStatement(
	std::vector<std::vector<std::string>>* mtx)
{
	//TCHAR     szBuf[1024];
	TCHAR     szCol1[25]{};
	TCHAR     szCol2[25]{};
	SQLLEN    nColLen1 = 0;
	SQLLEN    nColLen2 = 0;
	SQLRETURN nResult;

	//std::string strY = myDate->calcStrFebruaryLastYear();
	//char c_Y[10]; 
	//strcpy_s(c_Y, strY.size() + 1, strY.c_str());

	//sprintf_sを使って、文字と変数(fromDay, tillDay)を結合させたいので
	//char型にする
	char moji[254];
	sprintf_s(moji,
		"SELECT ITEM_ID, KS_TT_USER"
		" FROM TF_HS_FORMAT"
        " WHERE DEL_FLG <> '1'");
		//SQLExecDirectに渡すのに、wchar_t(TCHAR)型にしないといけないから
		//mbstowcsを使って変換する。visual studioのプロパティの設定で
		//SDLチェックを「いいえ」にしないと使えない(mbstowcs_s)が推奨されて
		//いるが、使い方がわからないから
        
	TCHAR wmoji[256]{};
	mbstowcs_s(NULL, wmoji, (sizeof wmoji) / sizeof(TCHAR), moji, _TRUNCATE);


	ConnectSql* conSql = new ConnectSql();

	SQLHSTMT hstmt = conSql->connectSql("SelectHsFormat");
	//nResult = SQLExecDirect(hstmt, (SQLTCHAR*)TEXT(
	nResult = SQLExecDirect(hstmt, (SQLTCHAR*)wmoji, SQL_NTS);


	SQLBindCol(hstmt, 1, SQL_C_TCHAR, szCol1, sizeof(szCol1), &nColLen1);
	SQLBindCol(hstmt, 2, SQL_C_TCHAR, szCol2, sizeof(szCol2), &nColLen2);


    //TCHARからstring型に変換する時にエンコードcp932にする
	int cnt = 0;
	for (;;) {
		nResult = SQLFetch(hstmt);
		if (nResult == SQL_SUCCESS || nResult == SQL_SUCCESS_WITH_INFO) {
			std::vector<std::string> line;
			
			std::string strCol1;
			if (nColLen1 == SQL_NULL_DATA) {
				strCol1 = "NULL";
			}
			else {
				char buf1[255];
				WideCharToMultiByte(932, 0, szCol1, -1, buf1, sizeof(buf1), NULL, NULL);
				strCol1 = buf1;
			}

			std::string strCol2;
			if (nColLen2 == SQL_NULL_DATA) {
				strCol2 = "NULL";
			}
			else {
				char buf2[255];
				WideCharToMultiByte(932, 0, szCol2, -1, buf2, sizeof(buf2), NULL, NULL);
				strCol2 = buf2;
			}

			line.push_back(strCol1);
			line.push_back(strCol2);
			mtx->push_back(line);
			cnt++;
		}
		else
			break;
	}

	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	delete conSql;
	//MessageBox(NULL, szBuf, TEXT("OK"), MB_OK);
}
