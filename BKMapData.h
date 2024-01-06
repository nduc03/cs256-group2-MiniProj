#pragma once
#include <vector>
#include <string>
#include <set>
#include "Location.h"
#include "Route.h"

class BKMapData
{
	//BKMapData(const BKMapData& obj) = delete;

public:
	Location findLocationById(int id) const;

	void addLocation(Location location);
	void addRoute(Route route);
	Route getRoute(const Location& loc1, const Location& loc2) const;
	std::vector<Route> findRoute(const Location& loc1, const Location& loc2) const;
	std::vector<Location> listLocationsInRange(const Location& centerLoc, float distance) const;

	static BKMapData initFromFile(const std::string& locationFilePath, const std::string& routeFilePath);
	void saveDataToFile(const std::string& locationFilePath, const std::string& routeFilePath) const;
private:
	BKMapData(std::vector<std::string> locations, std::vector<std::string> routes);
	std::set<Location, LocationComparer> locations;
	std::vector<Route> routes;
	static bool checkValidRouteLength(std::string);
	static bool checkValidRouteInfo(std::string);
};
