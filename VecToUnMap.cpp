#include "VecToUnMap.h"

void VecToUnMap::vecToUnMap(
            std::vector<std::vector<std::string>>* vec,
            std::unordered_map<std::string, std::string>* unMap
            )
{
    for (std::vector<std::string> line : *vec){
        if (line.size() == 2){
            (*unMap)[line[0]] = line[1];
        }
    }
}


void VecToUnMap::vecToUnMap(
            std::vector<std::vector<std::string>>* vec,
            std::unordered_map<std::string, std::string>* unMap,
            int keyIndex,
            int valueIndex
            )
{
    for (std::vector<std::string> line : *vec){
        if (line.size() >= valueIndex){
            (*unMap)[line[keyIndex]] = line[valueIndex];
        }
    }
}
