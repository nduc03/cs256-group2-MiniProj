#pragma once
#include <vector>
#include <string>
#include <set>
#include "Location.h"
#include "Route.h"

class BKMapData
{
public:
	BKMapData();
	Location findLocationById(int id) const;

	void addLocation(int id, float longitude, float latitude);
	void addRoute(int startId, int destId, float length, const std::vector<std::string>& chunkFormat);
	Route getRoute(const Location& loc1, const Location& loc2) const;
	std::vector<Route> findRoute(const Location& loc1, const Location& loc2) const;
	std::vector<Location> listLocationsInRange(const Location& centerLoc, float distance) const;
	int getLastLocationId() const;

	static BKMapData initFromFile(const std::string& locationFilePath, const std::string& routeFilePath);
	static bool checkValidChunkFormat(std::string);
	void saveDataToFile(const std::string& locationFilePath, const std::string& routeFilePath) const;
private:
	BKMapData(std::vector<std::string> locations, std::vector<std::string> routes);
	std::set<Location, LocationComparer> locations;
	std::vector<Route> routes;
};
