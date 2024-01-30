
#ifndef COMMON_H
#define COMMON_H
#include <vector>
#include <string>
#include <unordered_map>
#include "cocos2d.h"

extern std::unordered_map<int,std::vector<cocos2d::Vec2>> HXoffsetMap;

std::vector<std::string> splitStringByDelimiter(const std::string& inputString, const std::string& delimiter, bool insertlastSpace = true);
std::vector<std::string> splitStringByChar(const std::string& inputString, char delimiter);

size_t getCurrentMemoryUsage();

void loadOffset();

#endif //COMMON_H
