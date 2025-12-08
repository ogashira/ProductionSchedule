#ifndef _CALCDATESINGLETON_H_
#define _CALCDATESINGLETON_H_


#include <string>
#include <vector>

class CalcDateSingleton
{
private:

	static CalcDateSingleton* instance;
	CalcDateSingleton(); 

	std::string myYear;               // User-provided year (e.g., "2024")
	std::string strToday;             // strToday "20251128"
	std::string strBefore7day;
	std::string strBefore14day;
	std::string strLastDay;
	std::string strFebruaryLastYear;  // Last year's February (e.g., 202302)
	std::string strFebruaryThisYear;  // This year's February (e.g., 202402)
	std::string strSttDay;            // Fiscal year start day (e.g., 20230301)
	std::string strEndDay;            // Fiscal year end day (e.g., 20240229)

	bool isLeapYear(int);
	std::string calcStrToday();         
	std::string calcStrBefore7day();
	std::string calcStrBefore14day();
	std::string calcStrLastDayOfThisMonth();
	int getLastDayOfMonth(int, int);
	std::string toStrDate(int, int, int);

public:
	~CalcDateSingleton();

	static CalcDateSingleton* getInstance();

	std::string returnStrLastDay();
	std::string returnStrToday();
	std::string calcStrFebruaryLastYear();
	std::string calcStrFebruaryThisYear();
	std::string calcStrSttDay();
	std::string calcStrEndDay();

    std::vector<std::string> createWorkingDays(
                        const std::vector<std::vector<std::string>>& holidays,
                        const std::string& strToday);
	void showDate();
	void setMyYear(std::string myYear);

    // New public methods
    std::string getOneMonthBefore(const std::string& dateStr);
    std::string getTwoMonthsAfter(const std::string& dateStr);
};

#endif //_CALCDATESINGLETON_H_
