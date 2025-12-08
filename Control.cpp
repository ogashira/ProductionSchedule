#include "Control.h"
#include "UserInterface.h"
#include "SelectSzYt.h"
#include "CalcDateSingleton.h"
#include "Printer.h"
#include "CreateCsv.h"
#include "Excel.h"
#include "SelectTmKj.h"
#include "VecToUnMap.h"
#include "SelectHsFormat.h"
#include "CreateScheduleForTantou.h"
#include "GetCsv.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cstdio> // For sscanf
#include <unordered_map>


int Control::start() {
    /*
     * 製造予定データは今日の1ヵ月前から2ヵ月後までを取得する。
     * 休日データから今日の2日前から14日後までの稼働日データを作る
     * 製造予定データから稼働日データの範囲の担当ID製品を抽出
     * 製品がAB試験の時はvecMatomeから最後に登録したLotが何回目のA試験かを
     * 求める。 'S4-SR001A-U...3'などと表記する
    */
    // 今日と1ヵ月前と２ヵ月後を求める 
	CalcDateSingleton *singleton = CalcDateSingleton::getInstance();
	std::string strToday = singleton->returnStrToday(); //strToday= "20251128"
    std::string year = strToday.substr(0,4);
    std::string month = strToday.substr(4,2);
    std::string day = strToday.substr(6,2);
    std::string y_m_d = year + "/" + month + "/" + day; // y_m_d = "2025/11/28"
    std::string strOneMonthBefore = singleton->getOneMonthBefore(y_m_d);
    std::string strTwoMonthsAfter = singleton->getTwoMonthsAfter(y_m_d);

    // Get 担当者姓 
    std::string tantouSei;
    UserInterface ui;
	try {
		ui.startChat();
        tantouSei = ui.getTantouSei();
	}
	catch(const char* s){
		std::cout << s << std::endl;
		delete singleton;
        std::cout << "An error occurred. Terminating." << std::endl;
		return 0;
	}

    // 製造予定データ取得
	std::vector<std::vector<std::string>> vecSzYt;
	IFSelectSql* szYt = new SelectSzYt(strOneMonthBefore, strTwoMonthsAfter);
	szYt->ExecuteStatement(&vecSzYt);
	delete szYt;

    // Open Excel file
    std::vector<std::vector<std::string>> hinbantaiou{};
    std::unordered_map<std::string, std::string> uMapHinbanBTest{};
    std::vector<std::vector<std::string>> matome{};
    Excel excel;
    excel.readExcelHinbantaiouToVec(&hinbantaiou);
    excel.readExcelMatomeToVec(&matome);
    //Vecをunordered_mapに変換
    //uMapHinbanBTest = {'S6-UV305-U': 'UV-305',......}
    VecToUnMap* vecToMap = new VecToUnMap();
    vecToMap-> vecToUnMap(&hinbantaiou, &uMapHinbanBTest);

    //kensa_nissuu.csvデータを取得してunMapに変換する
    //uMapHinbanTantouSei = {'S3-N404K2-U':'髙橋',......}
    std::vector<std::vector<std::string>> vecKensaNissuu{};
    std::unordered_map<std::string, std::string> uMapHinbanTantouSei{};
    std::string path = 
        "//192.168.1.247/共有/技術課ﾌｫﾙﾀﾞ/200. effit_data/ﾏｽﾀ/kensa_nissuu.csv";
    GetCsv* csv = new GetCsv();
    csv-> getCsv(&vecKensaNissuu, path, ',');
    int key = 0;
    int value = 2;
    vecToMap-> vecToUnMap(&vecKensaNissuu, &uMapHinbanTantouSei, key, value);
    //0 = keyの列No、2= valueの列No
    delete csv;

    

    // Get holiday data tmKj->tmkyuujitu
    // vecHolyday = [['20251206', '土'],['2025/12/07', '日'],....]
    std::vector<std::vector<std::string>> vecHolyday = {};
    IFSelectSql* tmKj = new SelectTmKj(strOneMonthBefore, strTwoMonthsAfter);
    tmKj->ExecuteStatement(&vecHolyday);
    
    delete tmKj;

    //workingDays 今日の2日前から14日後まで
    std::vector<std::string> workingDays = singleton->createWorkingDays(vecHolyday, y_m_d);

    //担当idの予定をまとめる
    std::vector<std::vector<std::string>> scheduleForTantouSei = {};
    CreateScheduleForTantou* createSchedule = new CreateScheduleForTantou
        (
         &tantouSei,
         &y_m_d,
         &vecSzYt,
         &uMapHinbanTantouSei,
         &workingDays,
         &matome,
         &uMapHinbanBTest
        );
    createSchedule-> createScheduleForTantou(&scheduleForTantouSei);

    delete createSchedule;

	Printer printer;
    printer.printfScreen(&scheduleForTantouSei);

    CreateCsv toCsv;
    std::string col = "年月日(曜日),1,2,3,4,5,6,7";
    std::string csvPath = "./ProductionSchedule.csv";
    toCsv.toCsv(&scheduleForTantouSei, &col, &csvPath);


    delete vecToMap;
	delete singleton;

	return 0;
}
