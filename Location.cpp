#define _USE_MATH_DEFINES

#include "Location.h"
#include "Utils.h"
#include <cmath>

using namespace std;

Location::Location(int id, float longitude, float latitude)
{
    this->id = id;
    this->longitude = longitude;
    this->latitude = latitude;
}

Location::Location(string locationFormat)
{
    vector<string> temp;
    temp = Utils::split(locationFormat, ',');
    id = stoi(temp[0]);
    longitude = stof(temp[1]);
    latitude = stof(temp[2]);
}

Location::Location()
{
}

int Location::getId() const
{
    return id;
}

float Location::getLongitude() const
{
    return longitude;
}

float Location::getLatitude() const
{
    return latitude;
}
string Location::toString() const
{
    return to_string(id) + "," + to_string(latitude) + "," + to_string(longitude);
}

string Location::describe() const
{
    string str = "ID: ";
    str += to_string(id) += ", Latitude: ";
    str += to_string(latitude) += ", Longitude: ";
    return str += to_string(longitude);
}

double Utils::toRadians(double degree)
{
    return degree * M_PI / 180.0;
}

double Utils::haversine(double alpha)
{
    return sin(alpha / 2.0) * sin(alpha / 2.0);
}

double Location::getDistance(const Location& loc1, const Location& loc2)
{
    double lat1 = Utils::toRadians(loc1.getLatitude());
    double lon1 = Utils::toRadians(loc1.getLongitude());
    double lat2 = Utils::toRadians(loc2.getLatitude());
    double lon2 = Utils::toRadians(loc2.getLongitude());
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    double a = Utils::haversine(dLat) + cos(lat1) * cos(lat2) * Utils::haversine(dLon);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return floor(6371.0 * c);
}

bool Location::operator==(const Location& other) const
{
	return this->id == other.id;
}

bool LocationComparer::operator()(const Location& a, const Location& b) const
{
	return a.getId() < b.getId();
}

bool LocationComparer::compareById(const Location& loc, int id)
{
	return loc.getId() < id;
}
