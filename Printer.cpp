#include "Printer.h"
#include <iostream>
#include <regex>

void Printer::printScreen(std::vector<std::vector<std::string>>* master)
{
	for (int i = 0; i < (*master).size(); i++) {
		for (int j = 0; j < (*master)[i].size()-1; j++) {
			std::cout << (*master)[i][j] << ",";
			//printf("%-25s", (*master)[i][j].c_str());
		}
		std::cout << (*master)[i][(*master)[i].size()-1] << std::endl;
	}
}

void Printer::printScreen(std::vector<std::string>* master)
{
	for (int i = 0; i < (*master).size(); i++) {
			std::cout << (*master)[i] << std::endl;
	}
}

void Printer::printScreen(std::map<std::string, std::string>* master) {

	for (auto iter = master->begin(); iter != master->end(); iter++) {
		std::cout << iter->first << "=>" << iter->second << std::endl;
	}
}

void Printer::printScreen(std::unordered_map<std::string, std::string>* master) {

	for (auto iter = master->begin(); iter != master->end(); iter++) {
		std::cout << iter->first << "=>" << iter->second << std::endl;
	}
}

void Printer::printScreen(std::map<std::string, int>* master) {

	for (auto iter = master->begin(); iter != master->end(); iter++) {
		std::cout << iter->first << "=>" << iter->second << std::endl;
	}
}

void Printer::printScreen(std::map<std::string, float>* master) {

	for (auto iter = master->begin(); iter != master->end(); iter++) {
		std::cout << iter->first << "=>" << iter->second << std::endl;
	}
}

void Printer::printScreen(std::map<std::string, std::vector<std::string>>* master) {

	for (auto iter = master->begin(); iter != master->end(); iter++) {
		std::cout << iter->first << "=>" << iter->second[0] << ","
			                             << iter->second[1] << "," 
			                             << iter->second[2] << ","
			                             << std::endl;
	}
}

void Printer::printfScreen(std::vector<std::vector<std::string>>* master)
{

    printf("\n");
    printf("%s\n", "--------------------+-------------------------+-------------------------+-------------------------+-------------------------+-------------------------+-------------------------+-------------------------+");

	for (int i = 0; i < master->size() -1; i++) {
        char cstr0[25];
        int noOfElements = (*master)[i].size();
		convertToFloat((&(*master)[i][0]), cstr0); 
        printf("%-20s|", cstr0);
        for (int j=1; j<noOfElements; j++){
            char cstr[25];
            convertToFloat((&(*master)[i][j]), cstr); 
            printf("%-25s|", cstr);
        }
        printf("\n");
        printf("%s\n", "--------------------+-------------------------+-------------------------+-------------------------+-------------------------+-------------------------+-------------------------+-------------------------+");
    }

    //ÅIs
    char cstr0[25];
    convertToFloat(&(*master)[master->size()-1][0], cstr0); 
    printf("%-20s|", cstr0);
    for (int j = 1;  j< (*master)[master->size()-1].size(); j++){
        char cstr[25];
        convertToFloat((&(*master)[master->size()-1][j]), cstr); 
        printf("%-25s|", cstr);
    }
    printf("\n");
    printf("%s\n", "--------------------+-------------------------+-------------------------+-------------------------+-------------------------+-------------------------+-------------------------+-------------------------+");
}
    

int Printer::convertToFloat(std::string* str, char* cstr) {
	std::regex reNum(R"([+-]?\d+(?:\.\d+)?)");

	if (std::regex_match(*str, reNum)) {
		std::sprintf(cstr, "%d", std::stoi(*str));
	}
	else {
		strcpy_s(cstr, (*str).size()+1, (*str).c_str());
	}
	return 0;
}
