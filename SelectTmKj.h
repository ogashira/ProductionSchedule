#ifndef _SELECTTMKJ_H_
#define _SELECTTMKJ_H_

#include "IFSelectSql.h"
#include <vector>
#include <string>
#include "ConnectSql.h"

class SelectTmKj : public IFSelectSql
{
private:
    std::string beforeToday;
    std::string afterToday;
public:
    SelectTmKj(std::string, std::string);
	void ExecuteStatement(std::vector<std::vector<std::string>>*);
};
#endif //_SELECTTMKJ_H_
