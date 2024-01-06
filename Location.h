#pragma once
#include <string>
struct Location
{
	int id;
	float longitude, latitude;
	Location(int id, float longitude, float latitude);
	Location(std::string locationFormat);
	std::string toString() const;
	static float getDistance(Location loc1, Location loc2);
};

struct LocationComparer {
	bool operator() (const Location&, const Location&) const;
};