#ifndef _EXCEL_H_
#define _EXCEL_H_

#include <string>
#include <vector>

class Excel
{

public:
    void readExcelHinbantaiouToVec(
            std::vector<std::vector<std::string>>* data
        );

    void readExcelMatomeToVec(
            std::vector<std::vector<std::string>>* data
        );
};

#endif //_EXCEL_H_
