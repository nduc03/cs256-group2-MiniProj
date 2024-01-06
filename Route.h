#pragma once
#include <vector>
#include "Location.h"

enum RouteType 
{
	INDENT = 1, DIAGONAL = 2
};

struct RouteChunk 
{
	int startLocation; // also means previous location 
	int endLocation; // also means current location when reading the file
	float width;
	RouteType routeType;
	RouteChunk(int location, float width, RouteType routeType);
	RouteChunk(std::string routeChunkFormat);
	float getChunkArea() const;
	std::string toString() const;
	// ý tưởng: thêm method để vẽ chunk
};

class Route
{
public:
	Route(int startId, int destId, float length, const std::vector<RouteChunk>& chunks);

	bool checkValidRoute() const;
	float getRouteArea() const;
	std::string toString() const;
	// ý tưởng: thêm method để vẽ toàn bộ route dựa trên việc ghép những chunk đã đc vẽ
private:
	float length;
	Location startLoc, destLoc;
	std::vector<RouteChunk> chunks;
};

//class RouteDrawer 
//{
//public:
//	RouteDrawer(Route route, int screenHeight, int screenWidth);
//	void draw();
//private:
//	Route route;
//	std::vector<std::vector<char>> canvas;
//};