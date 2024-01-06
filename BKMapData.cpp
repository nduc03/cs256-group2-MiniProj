#include <algorithm>
#include <fstream>
#include "BKMapData.h"
#include "Utils.h"

using namespace std;

/// <summary>
/// Initilize the BKMap using the specific format.
/// The format should be correct before calling this constructor, 
/// because this constructor does not check the format validity.
/// </summary>
/// <param name="locations">Each element use the format "id, latitude, longitude"</param>
/// <param name="routes">
/// Each element use the format:
/// "
/// <para>PATH:location_id_1, location_id_2</para>
/// <para>route_length</para>
/// <para>position, width, route_type</para>
/// <para>position, width, route_type</para>
/// <para>...</para>
/// "
/// </param>
BKMapData::BKMapData(vector<string> locations, vector<string> routes)
{
	for (auto& loc : locations)
	{
		this->locations.emplace(loc);
	}
	for (auto& str : routes)
	{
		string temp;
		vector<string> data = Utils::split(str, '\n');
		// remove first 5 char (PATH:) then split 2 location Ids by comma
		auto locIdData = Utils::split(data[0].substr(5), ',');
		auto& lengthData = data[1];
		vector<RouteChunk> chunkList;
		for (int i = 2; i < data.size(); i++)
		{
			chunkList.emplace_back(data.at(i));
		}
		this->routes.emplace_back(
			stoi(locIdData.at(0)),
			stoi(locIdData.at(1)),
			stof(lengthData),
			chunkList
		);
	}
}

bool BKMapData::checkValidRouteLength(std::string str)
{
	for (auto& c : str)
	{
		if (c != '.' || !isdigit(c)) return false;
	}
	return true;
}

bool BKMapData::checkValidRouteInfo(std::string str)
{
	int commaCount = 0;
	for (auto& c : str)
	{
		if (c == ',') commaCount++;
		else if (c != '.' || !isdigit(c)) return false;
	}
	return commaCount == 2;
}

Location BKMapData::findLocationById(int id) const
{
	// dùng binary search vì id đã đc sort
}

Route BKMapData::getRoute(const Location& loc1, const Location& loc2) const
{
}

vector<Route> BKMapData::findRoute(const Location& loc1, const Location& loc2) const
{
}

std::vector<Location> BKMapData::listLocationsInRange(const Location& centerLoc, float distance) const
{

}

/// <summary>
/// Convert all data from file to array of infomation
/// Then initialize the BKMapData
/// </summary>
/// <param name="locationFilePath"></param>
/// <param name="routeFilePath"></param>
/// <returns></returns>
BKMapData BKMapData::initFromFile(const string& locationFilePath, const string& routeFilePath)
{
	ifstream locFile(locationFilePath);
	ifstream routeFile(routeFilePath);
	string buf;
	vector<string> loc, route;
	while (getline(locFile, buf)) 
	{
		loc.emplace_back(buf);
	}
	string routeStringData;
	while (getline(routeFile, buf)) 
	{
		if (buf.starts_with("PATH:")) 
		{
			if (!routeStringData.empty()) route.emplace_back(routeStringData);
			routeStringData = ""; // clear the previous data if previous exists
			routeStringData += buf;
			routeStringData.push_back('\n');
			if (getline(routeFile, buf)) 
			{
				if (checkValidRouteLength(buf))
				{
					routeStringData += buf;
					routeStringData.push_back('\n');
				}
				else throw invalid_argument("Invalid file format! Cannot read the file");
			}
			else throw invalid_argument("Invalid file format! Cannot read the file");
		}
		else if (!routeStringData.empty()) // if first line is not PATH: -> invalid file
		{
			if (checkValidRouteInfo(buf))
			{
				routeStringData += buf;
				routeStringData.push_back('\n');
			}
			else throw invalid_argument("Invalid file format! Cannot read the file");
		}
		else throw invalid_argument("Invalid file format! Cannot read the file");
	}

	return BKMapData(loc, route);
}

/// <summary>
/// The file path should be different from the input file path from BKMapData::initFromFile
/// to avoid override the input file.
/// </summary>
/// <param name="locationFilePath"></param>
/// <param name="routeFilePath"></param>
void BKMapData::saveDataToFile(const string& locationFilePath, const string& routeFilePath) const
{
	fstream file(locationFilePath);
	for (const auto& loc : locations)
		file << loc.toString() << '\n';

	file.close();
	file.open(routeFilePath);

	for (const auto& route : routes)
		file << route.toString() << '\n';
}

void BKMapData::addLocation(Location location)
{
	locations.insert(location);
}

void BKMapData::addRoute(Route route)
{
	routes.push_back(route);
}

