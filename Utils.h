#pragma once
#include <vector>
#include <string>
class Utils
{
public:
	// main.cpp
	static std::vector<std::string> split(const std::string&, char);
	// main.cpp
	static bool isNonNegativeNumber(const std::string&);
	// Location.cpp
	static double toRadians(double);
	// Location.cpp
	static double haversine(double);
	// main.cpp
	static bool isBlankString(const std::string&);
};