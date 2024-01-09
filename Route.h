#pragma once
#include "Location.h"
#include <vector>

enum RouteType 
{
	INDENT = 1, DIAGONAL = 2
};

struct RouteChunk 
{
	int location;
	float width;
	RouteType routeType;
	RouteChunk(int location, float width, RouteType routeType);
	// automatically parse the string that have the RouteChunk format then construct the object
	RouteChunk(std::string routeChunkFormat);
	// convert the object back to the string with the same format as the file
	std::string toString() const;
	// describe the data of the chunk
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
	// convert the object back to the string with the same format as the file
	std::string toString() const;
	// describe the data of the route
	std::string describe() const;
private:
	float length;
	Location startLoc, destLoc;
	std::vector<RouteChunk> chunks;
};