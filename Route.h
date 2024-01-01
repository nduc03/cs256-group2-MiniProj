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
	RouteType routeType;
	RouteData(int location, float width, RouteType routeType);
};

class Route
{
public:
	Route(int startId, int destId, float length, const std::vector<RouteData>& routeData);

	bool checkValidRoute() const;
private:
	float length;
	Location startLoc, destLoc;
	std::vector<RouteData> routeData;
};

class RouteDrawer 
{
public:
	RouteDrawer(Route route, int screenHeight, int screenWidth);
	void draw();
private:
	Route route;
	std::vector<std::vector<char>> canvas;
};