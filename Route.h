#pragma once
#include "Location.h"
#include <vector>

enum RouteType 
{
	INDENT = 1, DIAGONAL = 2
};

struct RouteChunk 
{
	int location; // also means current location when reading the file
	float width;
	RouteType routeType;
	RouteChunk(int location, float width, RouteType routeType);
	RouteChunk(std::string routeChunkFormat);
	std::string toString() const;
	std::string describe() const;
};

class Route
{
public:
	Route(const Location& startLoc, const Location& destLoc, float length, const std::vector<RouteChunk>& chunks);

	float getLength() const;
	Location getStartLoc() const;
	Location getDestLoc() const;

	bool checkValidRoute() const;
	float getRouteArea() const;
	std::string toString() const;
	std::string describe() const;
private:
	float length;
	Location startLoc, destLoc;
	std::vector<RouteChunk> chunks;
};