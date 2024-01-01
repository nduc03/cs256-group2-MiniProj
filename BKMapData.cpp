#include "BKMapData.h"

BKMapData::BKMapData(std::string locationFilePath, std::string routeFilePath)
{

}

Location BKMapData::findLocationById(int id) const
{
}

Route BKMapData::getRouteData(Location loc1, Location loc2) const
{
}

std::vector<Route> BKMapData::findRoute(Location loc1, Location loc2) const
{
}

std::vector<Location> BKMapData::listLocationsInRange(Location centerLoc, float distance) const
{
}

void BKMapData::addLocation(Location locData)
{
}

void BKMapData::addRoute(Route route)
{
}

