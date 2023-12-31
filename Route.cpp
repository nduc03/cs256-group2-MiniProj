#include "Route.h"

RouteData::RouteData(int location, float width, RouteType pathType)
{

}

Route::Route(int startId, int destId, int length, const std::vector<RouteData>& pathData)
{
}

bool Route::checkValidPath()
{
    // check the length of the path, if less than length of 2 location -> false
    // else true
    // use Location::getDistance() to get the distance
}

