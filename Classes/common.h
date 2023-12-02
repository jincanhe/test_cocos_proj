
#ifndef COMMON_H
#define COMMON_H
#include "vector"
#include "string"

std::vector<std::string> splitStringByDelimiter(const std::string& inputString, const std::string& delimiter);

size_t getCurrentMemoryUsage();

#endif //COMMON_H
