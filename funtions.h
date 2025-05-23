#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
void PrintStrings(const std::string* strings, int32_t size);
void DeleteStrings(std::string* strings);
std::string* FillStringArray(int32_t& size);
void ProcessAndSortStrings(std::string* strings, int32_t size);

#endif
