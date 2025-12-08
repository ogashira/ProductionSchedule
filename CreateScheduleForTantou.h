#ifndef _CREATESCHEDULEFORTANTOUID_H_
#define _CREATESCHEDULEFORTANTOUID_H_

#include <string>
#include <map>
#include <vector>
#include <unordered_map>

class CreateScheduleForTantou
{
public:
    CreateScheduleForTantou(
            std::string* tantouSei,
            std::string* todaySlash, 
            std::vector<std::vector<std::string>>* vecSzYt,
            std::unordered_map<std::string, std::string>* uMapHinbanTantouSei,
            std::vector<std::string>* workingDays,
            std::vector<std::vector<std::string>>* matome,
            std::unordered_map<std::string, std::string>* uMapHinbanBTest
            );
	void createScheduleForTantou(
            std::vector<std::vector<std::string>>* scheduleForTantou
            );
private:
    std::string* tantouSei;
    std::string* todaySlash; 
    std::vector<std::vector<std::string>>* vecSzYt;
    std::unordered_map<std::string, std::string>* uMapHinbanTantouSei;
    std::vector<std::string>* workingDays;
    std::vector<std::vector<std::string>>* matome;
    std::unordered_map<std::string, std::string>* uMapHinbanBTest;

    //method
    int addAsterForThaistanley( std::string* hinban, std::string nonyusaki);
    int addCountForKoitAB(std::string* hinban);


};

#endif //_CREATESCHEDULEFORTANTOUID_H_
