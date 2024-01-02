#include "BKMapData.h"

using namespace std;

BKMapData::BKMapData(vector<string> locations, vector<string> routes)
{

}

Location BKMapData::findLocationById(int id) const
{
	// dùng binary search vì id đã đc sort
}

Route BKMapData::getRouteData(const Location& loc1, const Location& loc2) const
{
}

vector<Route> BKMapData::findRoute(const Location& loc1, const Location& loc2) const
{
}

std::vector<Location> BKMapData::listLocationsInRange(const Location& centerLoc, float distance) const
{
}

BKMapData BKMapData::initFromFile(const string& locationFilePath, const string& routeFilePath)
{
	//return BKMapData();
}

void BKMapData::saveDataToFile(const string& locationFilePath, const string& routeFilePath) const
{
}

void BKMapData::addLocation(Location locData)
{
}

void BKMapData::addRoute(Route route)
{
}

