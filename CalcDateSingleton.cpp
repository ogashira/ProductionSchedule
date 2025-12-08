#include "CalcDateSingleton.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <cstdio> // For sscanf

// This line seems to cause build issues sometimes?
CalcDateSingleton* CalcDateSingleton::instance = nullptr;

CalcDateSingleton::CalcDateSingleton() {
	myYear = "0";
	strToday = this->calcStrToday();
	strBefore7day = this->calcStrBefore7day();
	strBefore14day = this->calcStrBefore14day();
	strLastDay = this->calcStrLastDayOfThisMonth();
};

CalcDateSingleton::~CalcDateSingleton() {
};

void CalcDateSingleton::setMyYear(std::string myYear) {
	this->myYear = myYear;
}

//staticMethod
CalcDateSingleton* CalcDateSingleton::getInstance() {
	if (instance == nullptr) {
		instance = new CalcDateSingleton();
	}
	return instance;
}

std::string CalcDateSingleton::returnStrToday() { return strToday; }

std::string CalcDateSingleton::returnStrLastDay() { return strLastDay; }

std::string CalcDateSingleton::calcStrToday() {

	struct mytm {
		int tm_mday;
		int tm_mon;
		int tm_year;
	};

	time_t t = time(nullptr);
	const tm* now = localtime(&t);

	int year = now->tm_year + 1900;
	int month = now->tm_mon + 1;
	int day = now->tm_mday;


	strToday = toStrDate(year, month, day);

	return strToday;
}

std::string CalcDateSingleton::calcStrBefore7day() {
	std::string strYear = strToday.substr(0, 4);
	std::string strMonth = strToday.substr(4, 2);
	std::string strDay = strToday.substr(6, 2);

	int year = std::stoi(strYear);
	int month = std::stoi(strMonth);
	int day = std::stoi(strDay);
	int before7y{};
	int before7m{};
	int before7d{};

	if (day > 7) {
		before7d = day - 7;
		before7y = year;
		before7m = month;
		return toStrDate(before7y, before7m, before7d);
	}
	if (month == 1) { before7d = getLastDayOfMonth(year - 1, 12) + (day - 7); }
	else { before7d = getLastDayOfMonth(year, month - 1) + (day - 7);}

	
	if (month == 1) { 
		before7m = 12; 
		before7y = year - 1; 
		return toStrDate(before7y, before7m, before7d);
	}

	before7m = month - 1;
	before7y = year;
	return toStrDate(before7y, before7m, before7d);
}

std::string CalcDateSingleton::calcStrBefore14day() {
	std::string strYear = strToday.substr(0, 4);
	std::string strMonth = strToday.substr(4, 2);
	std::string strDay = strToday.substr(6, 2);

	int year = std::stoi(strYear);
	int month = std::stoi(strMonth);
	int day = std::stoi(strDay);
	int before14y{};
	int before14m{};
	int before14d{};

	if (day > 15) {
		before14d = day - 14;
		before14y = year;
		before14m = month;
		return toStrDate(before14y, before14m, before14d);
	}
	if (month == 1) { before14d = getLastDayOfMonth(year - 1, 12) + (day - 14); }
	else { before14d = getLastDayOfMonth(year, month - 1) + (day - 14);}

	
	if (month == 1) { 
		before14m = 12; 
		before14y = year - 1; 
		return toStrDate(before14y, before14m, before14d);
	}

	before14m = month - 1;
	before14y = year;
	return toStrDate(before14y, before14m, before14d);
}

std::string CalcDateSingleton::calcStrLastDayOfThisMonth() {
	std::string strYear = strToday.substr(0, 4);
	std::string strMonth = strToday.substr(4, 2);
	std::string strDay = strToday.substr(6, 2);

	int lastDay = getLastDayOfMonth(std::stoi(strYear), std::stoi(strMonth));

	return strYear + strMonth + std::to_string(lastDay);

}

bool CalcDateSingleton::isLeapYear(int year) {
	if (((year % 4 == 0) && (year % 100 != 0)) || year % 400 == 0) {
		return true;
	}
	return false;
}

int CalcDateSingleton::getLastDayOfMonth(int year, int month) {
	int leapDays[] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	int nonLeapDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	bool isleap = isLeapYear(year);

	if (isleap) { return leapDays[month - 1]; }

	return nonLeapDays[month - 1];
}

std::string CalcDateSingleton::toStrDate(int year, int month, int day) {
	std::string strYear = std::to_string(year);
	std::string strMonth = std::to_string(month);
	std::string strDay = std::to_string(day);
	if (month <= 9) { strMonth = '0' + std::to_string(month); }
	if (day <= 9) { strDay = '0' + std::to_string(day); }

	return strYear + strMonth + strDay;
}

void CalcDateSingleton::showDate(){
	strFebruaryLastYear = calcStrFebruaryLastYear();
	strFebruaryThisYear = calcStrFebruaryThisYear();
	strSttDay = calcStrSttDay();
	strEndDay = calcStrEndDay();

	std::cout << "Today          : " << strToday << std::endl;
	std::cout << "7 Days Ago     : " << strBefore7day << std::endl;
	std::cout << "14 Days Ago    : " << strBefore14day << std::endl;
	std::cout << "Last Day       : " << strLastDay << std::endl;
	std::cout << "Last Feb       : " << strFebruaryLastYear << std::endl;
	std::cout << "This Feb       : " << strFebruaryThisYear << std::endl;
	std::cout << "Fiscal Start   : " << strSttDay << std::endl;
	std::cout << "Fiscal End     : " << strEndDay << std::endl;
}

std::string CalcDateSingleton::calcStrFebruaryLastYear(){
	std::string lastY = std::to_string(std::stoi(myYear) - 1);
	return lastY + "02";
}
std::string CalcDateSingleton::calcStrFebruaryThisYear() { 
	std::string thisY = myYear;
	return thisY + "02";
}
std::string CalcDateSingleton::calcStrSttDay(){ 
	std::string lastY = std::to_string(std::stoi(myYear) - 1);
	return lastY + "03" + "01";
}
std::string CalcDateSingleton::calcStrEndDay(){
	std::string thisY = myYear;
	bool isLeap = this->isLeapYear(std::stoi(thisY));
	if (isLeap) { return thisY + "02" + "29"; }
	return thisY + "02" + "28";
}

// --- NEW FUNCTIONS by Mr.GEMINI ---

std::string CalcDateSingleton::getOneMonthBefore(const std::string& dateStr) {
    int year, month, day;
    sscanf(dateStr.c_str(), "%d/%d/%d", &year, &month, &day);

    tm date = {};
    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;

    // Decrement the month
    date.tm_mon -= 1;

    // Normalize the date using mktime. This handles year/month rollovers correctly.
    mktime(&date);

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y/%m/%d", &date);
    return std::string(buffer);
}

std::string CalcDateSingleton::getTwoMonthsAfter(const std::string& dateStr) {
    int year, month, day;
    sscanf(dateStr.c_str(), "%d/%d/%d", &year, &month, &day);
    //dateStr.c_str() -> sscanfが必要とする(const char*)に変換する

    tm date = {}; //tm構造体dateをゼロで初期化
    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;

    // Increment the month
    date.tm_mon += 2;

    // tm構造体をtime_t値(エポックからの秒数)に変換する
    // この変換によって正しい年月日になる　うるう年なども考慮.
    mktime(&date);

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y/%m/%d", &date); //tm構造体dateを"YYYY/mm/dd"にする
    return std::string(buffer); //std::stringに変換
}


// ローカル関数　createWorkingDays()から呼ばれる
bool isWorkingDay(const tm& date, const std::vector<std::vector<std::string>>& holidays) {
    // Check for Saturday (6) or Sunday (0)
    if (date.tm_wday == 0 || date.tm_wday == 6) {
        return false;
    }

    // Format the date to "YYYY/MM/DD" for holiday check
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y/%m/%d", &date);
    std::string dateStr(buffer);

    // Check if the date is in the holiday list
    for (const auto& holidayEntry : holidays) {
        if (!holidayEntry.empty() && holidayEntry[0] == dateStr) {
            return false;
        }
    }

    return true;
}
// Implementation of the method to create the list of working days
std::vector<std::string> CalcDateSingleton::createWorkingDays(
                        const std::vector<std::vector<std::string>>& holidays,
                        const std::string& strToday) 
{
    std::vector<std::string> workingDays = {};
    std::vector<std::string> pastDays;

    int year, month, day;
    sscanf(strToday.c_str(), "%d/%d/%d", &year, &month, &day);
    
    // --- Set "Today" ---
    tm today_tm = {};
    today_tm.tm_year = year - 1900;
    today_tm.tm_mon = month - 1; // Month is 0-indexed
    today_tm.tm_mday = day;
    // Set time components to 0 and tm_isdst to -1 to let mktime determine DST
    today_tm.tm_hour = 0;
    today_tm.tm_min = 0;
    today_tm.tm_sec = 0;
    today_tm.tm_isdst = -1; //サマータイムはosに依存 
    mktime(&today_tm); // Normalize the tm struct and find tm_wday

    // 2稼働日前
    // --- Find previous 2 working days ---
    tm currentDate = today_tm;
    int daysFound = 0;
    while (daysFound < 2) {
        // Move to the previous day
        currentDate.tm_mday -= 1;
        mktime(&currentDate); // Normalize

        if (isWorkingDay(currentDate, holidays)) {
            char buffer[11];
            strftime(buffer, sizeof(buffer), "%Y/%m/%d", &currentDate);
            pastDays.push_back(std::string(buffer));
            daysFound++;
        }
    }
    // 14稼働日後
    // Reverse to get chronological order
    std::reverse(pastDays.begin(), pastDays.end());
    workingDays.insert(workingDays.end(), pastDays.begin(), pastDays.end());

    // --- Find today + next 14 working days ---
    currentDate = today_tm;
    daysFound = 0;
    while (daysFound < 15) {
        if (isWorkingDay(currentDate, holidays)) {
            char buffer[11];
            strftime(buffer, sizeof(buffer), "%Y/%m/%d", &currentDate);
            workingDays.push_back(std::string(buffer));
            daysFound++;
        }
        // Move to the next day
        currentDate.tm_mday += 1;
        mktime(&currentDate); // Normalize
    }

    return workingDays;
}
