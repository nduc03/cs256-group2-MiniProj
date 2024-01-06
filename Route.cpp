#include "Route.h"

using namespace std;

RouteChunk::RouteChunk(int location, float width, RouteType routeType)
{

}

RouteChunk::RouteChunk(string routeChunkFormat)
{

}

float RouteChunk::getChunkArea() const
{
    // if RouteType is INDENT -> calculate the area of rectangle
    // if RouuteType is DIAGONAL -> calculate the areac of trapezoid (hình thang)
}

/// <summary>
/// Due to the format, the this method will get rid of the startLocation property
/// </summary>
/// <returns></returns>
string RouteChunk::toString() const
{
    return to_string(endLocation) + "," + to_string(width) + "," + to_string(routeType);
}

Route::Route(int startId, int destId, float length, const vector<RouteChunk>& chunks)
{

}

bool Route::checkValidRoute() const
{
    // check the length of the route, if less than length of 2 locations -> false
    // else true
    // use Location::getDistance() to get the length of 2 locations
}

float Route::getRouteArea() const
{
    // calculate the sum of all area in RouteChunk
}

string Route::toString() const
{
    string res = "PATH:";
    res += to_string(startLoc.id);
    res.push_back(',');
    res += to_string(destLoc.id);
    res.push_back('\n');
    res += to_string(length);
    res.push_back('\n');
    for (auto& chunk : chunks)
    {
        res += chunk.toString();
        res.push_back('\n');
    }
}

//RouteDrawer::RouteDrawer(Route route, int screenHeight, int screenWidth)
//{
//}
//
//void RouteDrawer::draw()
//{
//}

