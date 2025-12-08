#include "SelectSzYt.h"

SelectSzYt::SelectSzYt(std::string strOneMonthBefore, 
                       std::string strTwoMonthsAfter)
{
    this-> strOneMonthBefore = strOneMonthBefore;
    this-> strTwoMonthsAfter = strTwoMonthsAfter;
}


void SelectSzYt::ExecuteStatement(
	std::vector<std::vector<std::string>>* mtx)
{
	//TCHAR     szBuf[1024];
	TCHAR     szCol1[25]{};
	TCHAR     szCol2[25]{};
	TCHAR     szCol3[25]{};
	TCHAR     szCol4[25]{};
	TCHAR     szCol5[25]{};
	SQLLEN    nColLen1 = 0;
	SQLLEN    nColLen2 = 0;
	SQLLEN    nColLen3 = 0;
	SQLLEN    nColLen4 = 0;
	SQLLEN    nColLen5 = 0;
	SQLRETURN nResult;

	//strOneMonthBefore, strTwoMonthsAfterをchar[]に変換
	char c_omb[15]; 
	strcpy_s(c_omb, strOneMonthBefore.size() + 1, strOneMonthBefore.c_str());
	char c_tma[15]; 
	strcpy_s(c_tma, strTwoMonthsAfter.size() + 1, strTwoMonthsAfter.c_str());

	//sprintf_sを使って、文字と変数(fromDay, tillDay)を結合させたいので
	//char型にする
	char moji[254];
	sprintf_s(moji,
		"SELECT SZ_YT_DT, SZ_KBN, KT_KBN, ITEM_ID, NNSK_KBN"
		" FROM TF_SZ_YT"
        " WHERE DEL_FLG <> '1'"
        " AND SZ_YT_DT >= '%s'"
        " AND SZ_YT_DT <= '%s'"
        " ORDER BY SZ_YT_DT", c_omb, c_tma);

		//SQLExecDirectに渡すのに、wchar_t(TCHAR)型にしないといけないから
		//mbstowcsを使って変換する。visual studioのプロパティの設定で
		//SDLチェックを「いいえ」にしないと使えない(mbstowcs_s)が推奨されて
		//いるが、使い方がわからないから
	TCHAR wmoji[256]{};
	mbstowcs_s(NULL, wmoji, (sizeof wmoji) / sizeof(TCHAR), moji, _TRUNCATE);


	ConnectSql* conSql = new ConnectSql();

	SQLHSTMT hstmt = conSql->connectSql("SelectSzYt");
	//nResult = SQLExecDirect(hstmt, (SQLTCHAR*)TEXT(
	nResult = SQLExecDirect(hstmt, (SQLTCHAR*)wmoji, SQL_NTS);


	SQLBindCol(hstmt, 1, SQL_C_TCHAR, szCol1, sizeof(szCol1), &nColLen1);
	SQLBindCol(hstmt, 2, SQL_C_TCHAR, szCol2, sizeof(szCol2), &nColLen2);
	SQLBindCol(hstmt, 3, SQL_C_TCHAR, szCol3, sizeof(szCol3), &nColLen3);
	SQLBindCol(hstmt, 4, SQL_C_TCHAR, szCol4, sizeof(szCol4), &nColLen4);
	SQLBindCol(hstmt, 5, SQL_C_TCHAR, szCol5, sizeof(szCol5), &nColLen5);


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

			std::string strCol3;
			if (nColLen3 == SQL_NULL_DATA) {
				strCol3 = "NULL";
			}
			else {
				char buf3[255];
				WideCharToMultiByte(932, 0, szCol3, -1, buf3, sizeof(buf3), NULL, NULL);
				strCol3 = buf3;
			}

			std::string strCol4;
			if (nColLen4 == SQL_NULL_DATA) {
				strCol4 = "NULL";
			}
			else {
				char buf4[255];
				WideCharToMultiByte(932, 0, szCol4, -1, buf4, sizeof(buf4), NULL, NULL);
				strCol4 = buf4;
			}

			std::string strCol5;
			if (nColLen5 == SQL_NULL_DATA) {
				strCol5 = "NULL";
			}
			else {
				char buf5[255];
				WideCharToMultiByte(932, 0, szCol5, -1, buf5, sizeof(buf5), NULL, NULL);
				strCol5 = buf5;
			}

			line.push_back(strCol1);
			line.push_back(strCol2);
			line.push_back(strCol3);
			line.push_back(strCol4);
			line.push_back(strCol5);
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
