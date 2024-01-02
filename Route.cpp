#include "Route.h"

using namespace std;

RouteData::RouteData(int location, float width, RouteType routeType)
{

}

Route::Route(int startId, int destId, float length, const vector<RouteData>& routeData)
{
}

bool Route::checkValidRoute() const
{
    // check the length of the route, if less than length of 2 locations -> false
    // else true
    // use Location::getDistance() to get the length of 2 locations
}

RouteDrawer::RouteDrawer(Route route, int screenHeight, int screenWidth)
{
}

void RouteDrawer::draw()
{
}

