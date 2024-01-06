#include "Location.h"

using namespace std;

Location::Location(int id, float longitude, float latitude) 
{

}

Location::Location(string locationFormat)
{
	// parse the text format from example then init the struct
}

string Location::toString() const
{
}

float Location::getDistance(Location loc1, Location loc2)
{
	// use formula arccos(sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(long2-long1))*6371 (km)
}

bool LocationComparer::operator()(const Location& a, const Location& b) const
{
	return a.id < b.id;
}
