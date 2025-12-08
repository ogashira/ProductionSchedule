#include "UserInterface.h"
#include "GetCsv.h"
#include "Printer.h"
#include <algorithm>
#include <cstdio>
#include <regex>
#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>


void UserInterface::startChat()
{
    //担当者データ取得
    std::vector<std::vector<std::string>> vecTantou;
    std::string fileName = R"(//192.168.1.247/共有/技術課ﾌｫﾙﾀﾞ)"
            R"(/200. effit_data/ﾏｽﾀ/ProductionSchedule関連/検査担当.csv)";
    GetCsv* getCsv = new GetCsv();
    getCsv -> getCsv(&vecTantou, fileName, ',');
    delete getCsv;


    std::string no;
    for (std::vector<std::string> line: vecTantou){
        std::cout << std::setw(3) << line[0] << " " 
                               << std::setw(8) << line[1] << " " << line[2] << std::endl;
    }

	std::cout << "製造予定を表示したい担当者の番号を入力して下さい" << std::endl;
	std::cout << ": ";
	std::cin >> no;
	//小文字を大文字に変換する
	std::transform(no.cbegin(), no.cend(), no.begin(), toupper);

	if (!std::regex_match(no, std::regex(R"(^[1-9]([0-9]+)?$)"))) {
		throw "入力した文字は数値ではありません";
		//Controller::start()に投げる
	}

    //noがvecTantouの0列に存在するかを検証
    bool isExistsNo = false;
    for (std::vector<std::string> line: vecTantou){
        if (line[0] == no){isExistsNo = true;} 
    }
    if (!isExistsNo){ throw "入力したNoはデータベースにありません";}

    //姓と名を取得
    int num = atoi(no.c_str());
    tantouSei = vecTantou[num][1];
    std::string tantouMei = vecTantou[num][2];

}

std::string UserInterface::getTantouSei(){
    return tantouSei;
}

