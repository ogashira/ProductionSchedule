#ifndef _SELECTHSFORMAT_H_
#define _SELECTHSFORMAT_H_

#include "IFSelectSql.h"
#include <vector>
#include <string>
#include "ConnectSql.h"

class SelectHsFormat : public IFSelectSql
{
public:
	void ExecuteStatement(std::vector<std::vector<std::string>>*);
};
#endif //_SELECTTMUSER_H_
