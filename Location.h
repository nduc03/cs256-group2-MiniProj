#pragma once
#include <string>
class Location
{
public:
	Location(int id, float longitude, float latitude);
	Location(std::string locationFormat);
	Location();
	int getId() const;
	int getLongitude() const;
	int getLatitude() const;
	std::string toString() const;
	static float getDistance(Location loc1, Location loc2);
	bool operator==(const Location&) const;
private:
	int id;
	float longitude, latitude;
};

struct LocationComparer
{
	bool operator() (const Location&, const Location&) const;
	static bool compareById(const Location& loc, int id);
};