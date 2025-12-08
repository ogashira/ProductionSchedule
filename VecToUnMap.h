#ifndef _VECTOUNMAP_H_
#define _VECTOUNMAP_H_

#include <vector>
#include <unordered_map>
#include <string>

class VecToUnMap 
{
public:
	void vecToUnMap(
            std::vector<std::vector<std::string>>* vec,
            std::unordered_map<std::string, std::string>* unMap
            );

	void vecToUnMap(
            std::vector<std::vector<std::string>>* vec,
            std::unordered_map<std::string, std::string>* unMap,
            int keyIndex,
            int valueIndex
            );
};
#endif //_VECTOUNMAP_H_
