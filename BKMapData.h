#pragma once
#include "Location.h"
#include "Route.h"
#include <set>
#include <string>
#include <vector>

class BKMapData
{
public:
	BKMapData();
	const Location* findLocationById(int id) const;

	void addLocation(int id, float longitude, float latitude);
	void addRoute(int startId, int destId, float length, const std::vector<std::string>& chunkFormat);
	const Route* getRoute(int startID, int destID) const;
	std::vector<std::vector<Route>> findRoute(int startId, int destID) const;
	std::vector<Location> listLocationsInRange(const Location& centerLoc, float distance) const;
	int getLastLocationId() const;
	std::vector<Route> listAllInvalidRoute() const;

	static BKMapData initFromFile(const std::string& locationFilePath, const std::string& routeFilePath);
	static bool checkValidChunkFormat(std::string);
	void saveDataToFile(const std::string& locationFilePath, const std::string& routeFilePath) const;
private:
	std::set<Location, LocationComparer> locations;
	std::vector<Route> routes;

	BKMapData(std::vector<std::string> locations, std::vector<std::string> routes);
	std::vector<std::vector<Route>> recurRoutes(int startId, int endId, int recursiveLevel) const;
};
