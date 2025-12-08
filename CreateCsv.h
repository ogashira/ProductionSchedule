#pragma once
#include <vector>
#include <string>
#include <string>
#include <map>

class CreateCsv
{
public:
	CreateCsv();
	virtual ~CreateCsv();
	void toCsv(
		std::vector<std::vector<std::string>>* vec,
		std::string* col,
		std::string* path
	);

	void toCsv(
		std::map<std::string, float>* map,
		std::string* col,
		std::string* path
	);

};

