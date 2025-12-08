#include "CreateScheduleForTantou.h"
#include <ctime>
#include <cstdio>
#include <iostream>


CreateScheduleForTantou::CreateScheduleForTantou(
        std::string* tantouSei,
        std::string* todaySlash, 
        std::vector<std::vector<std::string>>* vecSzYt,
        std::unordered_map<std::string, std::string>* uMapHinbanTantouSei,
        std::vector<std::string>* workingDays,
        std::vector<std::vector<std::string>>* matome,
        std::unordered_map<std::string, std::string>* uMapHinbanBTest
        )
{
    this->tantouSei = tantouSei;
    this->todaySlash = todaySlash; // 2025/11/28
    this->vecSzYt = vecSzYt;
    this->uMapHinbanTantouSei = uMapHinbanTantouSei;
    this->workingDays = workingDays;
    this->matome = matome;
    this->uMapHinbanBTest = uMapHinbanBTest;
}

// Helper function to get the day of the week from a "YYYY/mm/dd" string
// Returns 0 for Sunday, 1 for Monday, ..., 6 for Saturday.
std::string getDayOfWeek(const std::string& dateStr) {
    std::unordered_map<int, std::string> weekdays =
    { {0,"日"}, {1,"月"}, {2,"火"}, {3,"水"}, {4,"木"}, {5,"金"}, {6,"土"}};
    int year, month, day;
    // Parse the date string "YYYY/mm/dd"
    sscanf(dateStr.c_str(), "%d/%d/%d", &year, &month, &day);

    tm date = {};
    date.tm_year = year - 1900; // tm_year is years since 1900
    date.tm_mon = month - 1;   // tm_mon is months since January (0-11)
    date.tm_mday = day;        // tm_mday is day of the month (1-31)

    // Set time components to 0 and tm_isdst to -1 to let mktime determine DST
    date.tm_hour = 0;
    date.tm_min = 0;
    date.tm_sec = 0;
    date.tm_isdst = -1; //サマータイムの設定はOSに任せる 

    // Normalize the tm struct. mktime will fill in tm_wday.
    mktime(&date);

    return weekdays[date.tm_wday];
}


int CreateScheduleForTantou::addAsterForThaistanley(
                               std::string* hinban, std::string nonyusaki)
{
// SR001でタイスタ向けだったら*を付ける
    if ( nonyusaki != "09"){return 0;}

    if ( !(*hinban == "S4-SR001A-U-R-EX" || *hinban == "S4-SR001B-U-R-EX"))
    {
        return 0;
    }

    *hinban = "* " + (*hinban);
    return 0;
}


int CreateScheduleForTantou::addCountForKoitAB(std::string* hinban){
// 小糸AB試験なら回数を付ける
    // uMapHinbanBTestにhinbanが存在しなければreturn
    if (uMapHinbanBTest->count(*hinban) == 0) { return 0;}
    
    // 品番の列を求める
    std::string name = (*uMapHinbanBTest)[*hinban]; // name == "UV-305"
    int cols = 0;
    for (std::string row4 : (*matome)[4]){ //4行目の各要素
        if(row4 == name){break;}
        cols ++;
    }
    // 求めた列の最終行(599)からデクリメントして空文字でない行を求める
    const int lastRow = 599; 
    std::string testCount = ""; 
    for (int i = lastRow; i > 4; i--){   // A試験回数の始まりは4行目からのため
        if( (*matome)[i][cols] == "" ){ continue;}

        testCount = (*matome)[i][0];
        break;
    }

    // その行の0列目がcountとなっている(1~5の数値) それをhinnbanにaddする
    *hinban = (*hinban) + ".." + testCount;
    
    return 0;
}


void CreateScheduleForTantou::createScheduleForTantou(
        std::vector<std::vector<std::string>>* vec2)
{
    int i;
    for (std::string workingDay: *workingDays){
        std::vector<std::string> vec1; //vec1を用意して月日と曜日を入れる 当日なら<-を付ける
        std::string dayDate = workingDay + " (" + getDayOfWeek(workingDay) + ")";
        if (workingDay == *todaySlash){ dayDate = dayDate + " <-"; }
        vec1.push_back(dayDate);
        i = 0;
        while ( i < vecSzYt->size() ){
            if ( workingDay == (*vecSzYt)[i][0]){
                while (i < vecSzYt->size() && workingDay == (*vecSzYt)[i][0] ){
                    if ((*uMapHinbanTantouSei)[(*vecSzYt)[i][3]] == *tantouSei &&
                        ((*vecSzYt)[i][2]== "02" || (*vecSzYt)[i][2]== "03") && //工程区分S又はSR
                        ((*vecSzYt)[i][1]== "01" || (*vecSzYt)[i][1]== "02"))//製造区分 製造または詰め替え
                    {
                        std::string hinban = (*vecSzYt)[i][3];
                        // SR001でタイスタ向けだったら*を付ける
                        addAsterForThaistanley(&hinban, (*vecSzYt)[i][4]);
                        // 小糸AB試験なら回数を付ける
                        addCountForKoitAB(&hinban);
                        vec1.push_back(hinban);
                    }
                    i++;
                }
            }
            i++;
        }
        vec2-> push_back(vec1);
    }
}
        
