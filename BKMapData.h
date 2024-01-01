#pragma once
#include <vector>
#include <string>
#include <set>
#include "Location.h"
#include "Route.h"

class BKMapData
{
public:
	BKMapData(std::string locationFilePath, std::string routeFilePath);
	Location findLocationById(int id) const;
	void addLocation(Location locData);
	void addRoute(Route route);
	Route getRouteData(Location loc1, Location loc2) const;
	std::vector<Route> findRoute(Location loc1, Location loc2) const;
	std::vector<Location> listLocationsInRange(Location centerLoc, float distance) const;
private:
	std::set<Location> locations; // consider using custom comparision
	std::vector<Route> routes;
};

