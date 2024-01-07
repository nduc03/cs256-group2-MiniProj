#pragma once
#include <vector>
#include <string>
class Utils
{
public:
	static std::vector<std::string> split(const std::string&, char);
	static bool isNonNegativeNumber(const std::string&);
};