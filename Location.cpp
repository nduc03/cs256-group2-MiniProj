#include "Location.h"

using namespace std;

Location::Location(int id, float longitude, float latitude) 
{

}

Location::Location(string locationFormat)
{
	// parse the text format from example then init the struct
}

/// <summary>
/// Using default constructor means that it is not a valid location and the id = -1, other field is empty
/// </summary>
Location::Location()
{
	this->id = -1;
}

int Location::getId() const
{
}

int Location::getLongitude() const
{
}

int Location::getLatitude() const
{
}

string Location::toString() const
{
}

float Location::getDistance(Location loc1, Location loc2)
{
	// use formula arccos(sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(long2-long1))*6371 (km)
}

bool Location::operator==(const Location& other) const
{
	return this->id == other.id;
}

bool LocationComparer::operator()(const Location& a, const Location& b) const
{
	return a.getId() < b.getId();
}

bool LocationComparer::compareById(const Location& loc, int id)
{
	return loc.getId()< id;
}
