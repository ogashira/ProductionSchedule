#include "CreateCsv.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

CreateCsv::CreateCsv() {
}
CreateCsv:: ~CreateCsv() {

}
void CreateCsv::toCsv(
	std::vector<std::vector<std::string>>* vec,
	std::string* col,
	std::string* path
){

	std::ofstream ofs_csv_file(*path);

	ofs_csv_file << *col << std::endl;
	for (int i = 0; i < (*vec).size(); i++) {
		for (int j = 0; j < (*vec)[i].size()-1; j++) {
			if ((*vec)[i][j].find(",") != -1) {
				(*vec)[i][j].replace((*vec)[i][j].find(","), 1, "");
			}
			ofs_csv_file << (*vec)[i][j] << ',' ;
		}
		ofs_csv_file << (*vec)[i][(*vec)[i].size() - 1] << std::endl;
	}
}

void CreateCsv::toCsv(
	std::map<std::string, float>* map,
	std::string* col,
	std::string* path
){

	std::ofstream ofs_csv_file(*path);

	ofs_csv_file << *col << std::endl;
	for ( auto iter = map->begin(); iter != map->end(); iter++ ) {
		std::string key = iter->first;
		if (key.find(",") != std::string::npos) {
			key.replace(iter->first.find(","), 1, "");
		}
		ofs_csv_file << iter->first << "," << iter->second << std::endl;
	}
}
