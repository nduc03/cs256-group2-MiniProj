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
	Location findLocationById(int id);
private:
	std::set<Location> locations;
	std::vector<Route> routes;
};

