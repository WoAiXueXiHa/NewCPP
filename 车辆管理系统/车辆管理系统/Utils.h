#pragma once
#include <string>

std::string trim(std::string s);
std::string readLine(const std::string& prompt);
double      readDoubleStrict(const std::string& prompt);
double      readDoubleOrNaN(const std::string& prompt);
