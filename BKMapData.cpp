#include "BKMapData.h"
#include "Utils.h"
#include <algorithm>
#include <fstream>

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
		// use substr to remove first 5 char (PATH:) then split 2 location Ids by minus sign
		auto locIdData = Utils::split(data[0].substr(5), '-');
		auto& lengthData = data.at(1);
		auto start = findLocationById(stoi(locIdData.at(0)));
		auto dest = findLocationById(stoi(locIdData.at(1)));
		vector<RouteChunk> chunkList;
		for (int i = 2; i < data.size(); i++)
		{
			if (data.at(i).empty()) continue; // Sometimes last line is empty string cause error, need to be ignored to avoid error
			chunkList.emplace_back(data.at(i));
		}
		this->routes.emplace_back(*start, *dest, stof(lengthData), chunkList);
	}
}

// Using recursion to brute force and find all the routes
// The routes in reverse order and is not sorted
vector<vector<Route>> BKMapData::recurRoutes(int start, int dest, int recursiveLevel) const
{
	if (recursiveLevel >= routes.size() * 2) return vector<vector<Route>>(); // Prevent infinity recursive
	if (start == dest) return vector<vector<Route>>();
	vector<vector<Route>> recurList;
	for (auto& route : routes)
	{
		if (route.getStartLoc().getId() == start && route.checkValidRoute())
		{
			if (route.getDestLoc().getId() == dest) recurList.push_back(vector<Route>({ route }));
			for (auto& subRoute : recurRoutes(route.getDestLoc().getId(), dest, ++recursiveLevel))
			{
				subRoute.push_back(route);
				recurList.push_back(subRoute);
			}
		}
	}

	// Remove all routes with incorrect destination

	vector<vector<Route>> res;
	for (int i = 0; i < recurList.size(); i++)
	{
		if (recurList[i][0].getDestLoc().getId() == dest) res.push_back(recurList[i]);
	}
	return res;
}

bool BKMapData::checkValidChunkFormat(string str)
{
	auto infoParts = Utils::split(str, ',');
	if (infoParts.size() != 3) return false;
	try
	{
		int type = stoi(infoParts[2]);
		if (type != 1 && type != 2) return false;
	}
	catch (invalid_argument)
	{
		return false;
	}
	for (auto& part : infoParts)
	{
		if (!Utils::isNonNegativeNumber(part)) return false;
	}
	return true;
}

BKMapData::BKMapData()
{
}

/// <summary>
/// Find the location then return the object with the same id.
/// If id does not exist, return default constructor which has id = -1
/// </summary>
/// <param name="id"></param>
/// <returns>Return the object if found, if not return empty Location object with id = -1</returns>
const Location* BKMapData::findLocationById(int id) const
{
	auto it = lower_bound(locations.begin(), locations.end(), id, LocationComparer::compareById);
	if (it != locations.end())
	{
		return &(*it);
	}
	return nullptr;
}

const Route* BKMapData::getRoute(int startID, int destID) const
{
	const Route* ptr;
	for (auto& r : routes)
	{
		if (r.getStartLoc().getId() == startID && r.getDestLoc().getId() == destID)
		{
			ptr = &r;
			return ptr;
		}
	}
	return nullptr;
}

/// <summary>
/// The correct route is in reverse order, remember to use reverse for-loop to iterate the correct route
/// All the possible routes are sorted in ascending order of the length
/// </summary>
/// <param name="startId"></param>
/// <param name="endId"></param>
/// <returns>Return all possible routes, where each route path is in the reverse order</returns>
vector<vector<Route>> BKMapData::findReverseRoutes(int startId, int destId) const
{
	auto res = recurRoutes(startId, destId, 0);
	sort(res.begin(), res.end(), [](vector<Route>& a, vector<Route>& b) { return a.size() < b.size(); });
	return res;
}

vector<Location> BKMapData::listLocationsInRange(const Location& centerLoc, float distance) const
{
	vector<Location> res;
	for (auto& location : locations)
	{
		if (location == centerLoc) continue;
		if (Location::getDistance(centerLoc, location) < distance)
			res.push_back(location);
	}
	return res;

}

int BKMapData::getLastLocationId() const
{
	return locations.rbegin()->getId();
}

vector<Route> BKMapData::listAllInvalidRoute() const
{
	vector<Route> res;
	for (auto& route : routes)
	{
		if (!route.checkValidRoute()) res.push_back(route);
	}
	return res;
}

/// <summary>
/// Convert all data from file to array of infomation
/// Then initialize the BKMapData
/// </summary>
/// <param name="locationFilePath"></param>
/// <param name="routeFilePath"></param>
/// <returns></returns>
BKMapData BKMapData::initFromFile(const string& locationFilePath, const string& routeFilePath) // note error
{
	ifstream locFile(locationFilePath);
	ifstream routeFile(routeFilePath);
	if (locFile.fail() || routeFile.fail()) throw ios_base::failure("Cannot open the files to read the data.");
	string buf;
	vector<string> loc, route;
	while (getline(locFile, buf)) 
	{
		loc.emplace_back(buf);
	}
	string routeStringData;
	while (getline(routeFile, buf)) 
	{
		if (buf.empty() || Utils::isBlankString(buf)) continue;
		if (buf.starts_with("PATH:")) 
		{
			if (!routeStringData.empty())
			{
				if (routeStringData.ends_with('\n')) routeStringData.pop_back();
				route.emplace_back(routeStringData);
			}
			routeStringData = ""; // clear the previous data if previous exists
			routeStringData += buf;
			routeStringData.push_back('\n');
			if (getline(routeFile, buf)) // line2: length
			{
				if (Utils::isNonNegativeNumber(buf))
				{
					routeStringData += buf;
					routeStringData.push_back('\n');
				}
				else throw invalid_argument("Invalid length format! Cannot read the file. Current buffer: " + buf);
			}
			else throw invalid_argument("Invalid length format! Maybe end of file but does not have enough data.");
		}
		else if (!routeStringData.empty()) // if first line is not PATH: -> invalid file
		{
			if (checkValidChunkFormat(buf))
			{
				routeStringData += buf;
				routeStringData.push_back('\n');
			}
			else
			{
				string errMsg = "Invalid chunk format! Cannot read the file. Current buffer: " + buf;
				throw invalid_argument(errMsg);
			}
		}
		else throw invalid_argument("Invalid file format! Cannot read the file. Current buffer: " + buf);
	}
	route.emplace_back(routeStringData); // dont forget to add the last path.
	return BKMapData(loc, route);
}

void BKMapData::saveDataToFile(const string& locationFilePath, const string& routeFilePath) const
{
	fstream file(locationFilePath, ios::out);
	if (file.fail()) throw ios_base::failure("Cannot open the location file to save the data.");
	for (const auto& loc : locations)
		file << loc.toString() << '\n';

	file.close();
	file.open(routeFilePath, ios::out);
	if (file.fail()) throw ios_base::failure("Cannot open the route file to save the data.");

	for (const auto& route : routes)
		file << route.toString() << '\n';
}

void BKMapData::addLocation(int id, float longitude, float latitude)
{
	locations.insert(Location(id, longitude, latitude));
}

/// <summary>
/// 
/// </summary>
/// <param name="startId"></param>
/// <param name="destId"></param>
/// <param name="length"></param>
/// <param name="chunkFormat">all chunk format need to be validated before use this function</param>
void BKMapData::addRoute(int startId, int destId, float length, const vector<string>& chunkFormatList)
{
	vector<RouteChunk> chunks;
	for (auto& chunkFormat : chunkFormatList)
	{
		chunks.emplace_back(chunkFormat);
	}
	const Location* start = findLocationById(startId);
	const Location* dest = findLocationById(destId);
	if (start == nullptr || dest == nullptr) throw invalid_argument("Invalid location id");

	routes.emplace_back(*start, *dest, length, chunks);
}
