#include <iostream>
#include "SelectTmKj.h"

SelectTmKj::SelectTmKj(std::string beforeToday, 
                       std::string afterToday)
{
    this-> beforeToday = beforeToday;
    this-> afterToday = afterToday;
}

void SelectTmKj::ExecuteStatement(
	std::vector<std::vector<std::string>>* mtx)
{
	//TCHAR     szBuf[1024];
	TCHAR     szCol1[25]{};
	TCHAR     szCol2[25]{};
	SQLLEN    nColLen1 = 0;
	SQLLEN    nColLen2 = 0;
	SQLRETURN nResult;

	//std::string strY = myDate->calcStrFebruaryLastYear();
	char c_bT[15]; 
	strcpy_s(c_bT, beforeToday.size() + 1, beforeToday.c_str());
	char c_aT[15]; 
	strcpy_s(c_aT, afterToday.size() + 1, afterToday.c_str());

	//sprintf_sを使って、文字と変数(fromDay, tillDay)を結合させたいので
	//char型にする
	char moji[254];
	sprintf_s(moji,
		"SELECT KJ_DT, KJ_DATE"
		" FROM TM_KJ"
        " WHERE DEL_FLG <> '1'"
        " AND KJ_DT >= '%s'"
        " AND KJ_DT <= '%s'", c_bT, c_aT);
		//" WHERE BzkYYM = %s" 
		//" AND BzkHinCD <= 'H'" 
		//" AND (BzkBuCD ='S0004' OR BzkBuCD ='S0024')"
		//" GROUP BY BzkHinCD"
		//" ORDER BY BzkHinCD", c_Y);
	/*
	char h1[30] = "20230501";
	char h2[30] = "20240229";
	sprintf_s(moji,
		"SELECT TnkHinCD,TnkAitCD1,TnkDay,TnkTnk"
		" FROM MTANKA"
		" WHERE TnkDay>= %s AND TnkDay<= %s"
		" ORDER BY TnkHinCD,TnkAitCD1,TnkDay", h1, h2);
		*/


		//SQLExecDirectに渡すのに、wchar_t(TCHAR)型にしないといけないから
		//mbstowcsを使って変換する。visual studioのプロパティの設定で
		//SDLチェックを「いいえ」にしないと使えない(mbstowcs_s)が推奨されて
		//いるが、使い方がわからないから
	TCHAR wmoji[256]{};
	mbstowcs_s(NULL, wmoji, (sizeof wmoji) / sizeof(TCHAR), moji, _TRUNCATE);


	ConnectSql* conSql = new ConnectSql();

	SQLHSTMT hstmt = conSql->connectSql("SelectTmKj");
	//nResult = SQLExecDirect(hstmt, (SQLTCHAR*)TEXT(
	nResult = SQLExecDirect(hstmt, (SQLTCHAR*)wmoji, SQL_NTS);

	if (nResult != SQL_SUCCESS) {
		SQLINTEGER      i = 0;
		SQLINTEGER      native;
		SQLTCHAR        state[7];
		SQLTCHAR        text[256];
		SQLSMALLINT     len; // SQLINTEGER から SQLSMALLINT に戻す
		SQLRETURN       ret;
		std::cerr << "エラー: SQLExecDirectが失敗しました。" << std::endl;
		do
		{
			ret = SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, ++i, state, &native, text, sizeof(text) / sizeof(SQLTCHAR), &len); // sizeof(text) を sizeof(text) / sizeof(SQLTCHAR) に変更
			if (SQL_SUCCEEDED(ret)) {
				char text_mb[256];
				WideCharToMultiByte(CP_ACP, 0, text, -1, text_mb, sizeof(text_mb), NULL, NULL);

				char state_mb[7];
				WideCharToMultiByte(CP_ACP, 0, state, -1, state_mb, sizeof(state_mb), NULL, NULL);

				std::cerr << "SQLSTATE: " << state_mb << ", Native Error: " << native << std::endl;
				std::cerr << "Message: " << text_mb << std::endl;
			}
		} while (ret == SQL_SUCCESS);

		SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
		delete conSql; // Ensure ConnectSql object is deleted to free connection
		return;
	}



	SQLBindCol(hstmt, 1, SQL_C_TCHAR, szCol1, sizeof(szCol1), &nColLen1);
	SQLBindCol(hstmt, 2, SQL_C_TCHAR, szCol2, sizeof(szCol2), &nColLen2);


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
