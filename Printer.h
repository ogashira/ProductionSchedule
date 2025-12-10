#ifndef _PRINTER_H_
#define _PRINTER_H_

#include <vector>
#include <string>
#include <map>
#include <unordered_map>

class Printer
{
public:
	void printScreen(std::vector<std::vector<std::string>>*);
	void printScreen(std::vector<std::string>*);
	void printScreen(std::map<std::string, std::string>*);
	void printScreen(std::unordered_map<std::string, std::string>*);
	void printScreen(std::map<std::string, float>*);
	void printScreen(std::map<std::string, int>*);
	void printScreen(std::map<std::string, std::vector<std::string>>* master);
	void printfScreen(std::vector<std::vector<std::string>>*);
private:
	int convertToFloat(std::string* str, char* cstr);
};


#endif // _PRINTER_H_
