#pragma once
#include <string>
class Location
{
public:
	Location(int id, float longitude, float latitude);
	// automatically parse the string that have the Location format then construct the object
	Location(std::string locationFormat);
	Location();
	int getId() const;
	float getLongitude() const;
	float getLatitude() const;
	// convert the object back to the string with the same format as the file
	std::string toString() const;
	// describe the data of location
	std::string describe() const;
	// Anh Trong
	static double getDistance(const Location& loc1, const Location& loc2);
	// Duc
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