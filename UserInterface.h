#ifndef _USERINTERFACE_H_
#define _USERINTERFACE_H_

#include <vector>
#include <string>
#include "CalcDateSingleton.h"

class UserInterface
{
public:
	void startChat();
    std::string getTantouSei();

private:
	std::string tantouSei; //t04Å@Ç»Ç«

};
#endif //_USERINTERFACE_H_

