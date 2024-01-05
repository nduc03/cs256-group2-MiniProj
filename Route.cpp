#include "Route.h"

using namespace std;

RouteChunk::RouteChunk(int location, float width, RouteType routeType)
{

}

float RouteChunk::getChunkArea() const
{
    // if RouteType is INDENT -> calculate the area of rectangle
    // if RouuteType is DIAGONAL -> calculate the areac of trapezoid (hình thang)
}

Route::Route(int startId, int destId, float length, const vector<RouteChunk>& routeData)
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

//RouteDrawer::RouteDrawer(Route route, int screenHeight, int screenWidth)
//{
//}
//
//void RouteDrawer::draw()
//{
//}

