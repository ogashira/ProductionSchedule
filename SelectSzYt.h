#ifndef _SELECTSZYT_H_
#define _SELECTSZYT_H_

#include "IFSelectSql.h"
#include <vector>
#include <string>
#include "ConnectSql.h"

class SelectSzYt : public IFSelectSql
{
public:
    SelectSzYt(std::string strOneMonthBefore,
               std::string strTwoMonthsAfter);
	void ExecuteStatement(std::vector<std::vector<std::string>>*);

private:
    std::string strOneMonthBefore;
    std::string strTwoMonthsAfter;
};
#endif //_SELECTSZYT_H_
