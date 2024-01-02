#include "Location.h"

using namespace std;

Location::Location(int id, float longitude, float latitude) 
{

}

Location::Location(string locationFormat)
{
	// parse the text format from example then init the struct
}

float Location::getDistance(Location loc1, Location loc2)
{
	// use formula sqrt(pow(loc2.longitude - loc1.longitude, 2) + pow(loc2.latitude - loc1.latitude, 2))
}

bool LocationComparer::operator()(const Location& a, const Location& b) const
{
	return a.id < b.id;
}
