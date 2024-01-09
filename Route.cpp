#include "Route.h"
#include "Utils.h"
#include <format>

using namespace std;

RouteChunk::RouteChunk(int location, float width, RouteType routeType)
{
    this->location = location;
    this->width = width;
    this->routeType = routeType;
}

RouteChunk::RouteChunk(string routeChunkFormat)
{
    auto temp = Utils::split(routeChunkFormat, ',');
    this->location = stoi(temp[0]);
    this->width = stof(temp[1]);
    this->routeType = (stoi(temp[2]) == 1) ? INDENT : DIAGONAL;
}

/// <summary>
/// Return the same format as the input file
/// </summary>
/// <returns></returns>
string RouteChunk::toString() const
{
    return to_string(location) += "," + format("{:.2f}",width) += "," + to_string(routeType);
}

string RouteChunk::describe() const
{
    string str("At location ");
    str += to_string(location) += " the road has the width: ";
    str += format("{:.2f}", width);
    return str;
}

Route::Route(const Location& startLoc, const Location& destLoc, float length, const vector<RouteChunk>& chunks)
{
    this->startLoc = startLoc;
    this->destLoc = destLoc;
    this->length = length;
    this->chunks = chunks;
}

float Route::getLength() const
{
    return length;
}

Location Route::getStartLoc() const
{
    return startLoc;
}

Location Route::getDestLoc() const
{
    return destLoc;
}

bool Route::checkValidRoute() const
{
    // valid route need at least 2 chunks, 
    if (chunks.size() < 2) return false;
    // the first chunk location must be 0, 
    if (chunks.at(0).location != 0) return false;
    // the last chunk location must equal to the length of the route,
    if (chunks.at(chunks.size() - 1).location != length) return false;
    // the route length must greater than or equal the distance between the 2 location
    if (Location::getDistance(startLoc, destLoc) > length) return false;
    return true;
}

// Use the area formula of trapezoid then divided by 1000 to convert from m to km
float Route::getRouteArea() const
{
    float res = 0;
    for (int i = 1; i < chunks.size(); i++)
    {
        res += 0.001f * 0.5f *
            (chunks.at(i).width + chunks.at(i - 1).width) * 
            (chunks.at(i).location - chunks.at(i - 1).location);
    }
    return res;
}

string Route::toString() const
{
    string res = "PATH:";
    res += to_string(startLoc.getId());
    res.push_back('-');
    res += to_string(destLoc.getId());
    res.push_back('\n');
    res += format("{:.2f}", length);
    res.push_back('\n');
    for (auto& chunk : chunks)
    {
        res += chunk.toString();
        res.push_back('\n');
    }
    return res;
}

string Route::describe() const
{
    string str = "";
    for (auto& chunk : chunks)
    {
        str += chunk.describe() += '\n';
    }
    return str;
}
