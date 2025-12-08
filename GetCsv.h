#pragma once
#include <string>
#include <vector>
#include <map>


class GetCsv
{
public:
	GetCsv();
	~GetCsv();
	std::vector<std::vector<std::string>>* getCsv(std::string, char);
	void getCsv(std::vector<std::vector<std::string>>*, std::string, char);
};
