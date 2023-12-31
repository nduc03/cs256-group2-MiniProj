#pragma once
#include <vector>
#include "Location.h"

enum RouteType 
{
	INDENT, DIAGONAL
};

struct RouteData 
{
	int location;
	float width;
	RouteType pathType;
	RouteData(int location, float width, RouteType pathType);
};

class Route
{
public:
	Route(int startId, int destId, int length, const std::vector<RouteData>& pathData);

	bool checkValidPath();
private:
	int length;
	Location startLoc, destLoc;
	std::vector<RouteData> pathData;
};