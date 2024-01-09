#include "BKMapData.h"
#include "Utils.h"
#include <iostream>
#include <string>

using namespace std;

vector<string> Utils::split(const string& str, char delim)
{
	string temp = "";
	vector<string> v;
	for (auto& c : str)
	{
		if (c != delim) temp += c;
		else
		{
			v.push_back(temp);
			temp.clear();
		}
	}
	v.push_back(temp);
	return v;
}

bool Utils::isNonNegativeNumber(const string& str)
{
	int dotCount = 0;
	for (auto& c : str)
	{
		if (dotCount > 1) return false;
		if (c == '.') dotCount++;
		else if (!isdigit(c)) return false;
	}
	return dotCount <= 1;
}

bool Utils::isBlankString(const string& str)
{
	for (auto& c : str)
	{
		if (c != ' ') return false;
	}
	return true;
}

// print the prompt to console then ask for input
// just like input() in python
static string promptInput(const string& prompt)
{
	cout << prompt;
	string buf;
	getline(cin, buf);
	return buf;
}

// handle all the tasks related to feature 1
// which is adding new data
static void handleInputNewData(BKMapData& data)
{
	string input;
	while (true)
	{
		try
		{
			input = promptInput("Enter 1 to add location, 2 to add route: ");
			if (input == "1")
			{
				int id = data.getLastLocationId() + 1;
				cout << "Created new location with ID: " << id << "\n";
				float lat = stof(promptInput("Enter latitude: "));
				float longitude = stof(promptInput("Enter longitude: "));
				data.addLocation(id, longitude, lat);
				break;
			}
			else if (input == "2")
			{
				const Location* start = data.findLocationById(stoi(promptInput("Enter start location ID: ")));
				if (start == nullptr)
				{
					cout << "Invalid input! Please enter data again.\n";
					continue;
				}
				const Location* dest = data.findLocationById(stoi(promptInput("Enter end location ID: ")));
				if (dest == nullptr)
				{
					cout << "Invalid input! Please enter data again.\n";
					continue;
				}
				if (data.getRoute(start->getId(), dest->getId()) != nullptr)
				{
					cout << "Route between 2 locations existed! Please enter data again.\n";
					continue;
				}

				float length = stof(promptInput("Enter route length: "));
				cout << "Describe every position of the route in number with the format like this: position, width, type.\n"
					<< "Where type is 1 when that part is indented, type is 2 when it is diagonal.\n"
					<< "Must include at least one begin position equal 0 and one last position equal to the length\n";
				vector<string> chunkFormatlist;
				while (true)
				{
					input = promptInput("Describe the part or type EXIT to stop input: ");
					if (input == "EXIT") break;
					if (BKMapData::checkValidChunkFormat(input))
					{
						chunkFormatlist.push_back(input);
					}
					else cout << "Invalid input! Please enter data again.\n";
				}
				if (chunkFormatlist.size() < 2)
				{
					cout << "Invalid input! Please enter data again.\n";
					continue;
				}
				data.addRoute(start->getId(), dest->getId(), length, chunkFormatlist);
				break;
			}
			else cout << "Invalid input! Please enter data again.\n";
		}
		catch (invalid_argument)
		{
			cout << "Invalid input! Please enter data again.\n";
		}
	}
}

int main()
{
	BKMapData data;
	try
	{
		data = BKMapData::initFromFile("Location.txt", "Path.txt");
	}
	catch (ios_base::failure e)
	{
		cout << e.what();
		cout << "\nProgram exited!\n";
		return -1;
	}
	catch (invalid_argument e)
	{
		cout << e.what();
		cout << "\nProgram exited!\n";
		return -1;
	}
	string input;
	while (true)
	{
		try
		{
			cout << "------------------------------------------------\n"
				<< "BKMap program\n"
				<< "1. Add a new location or a new route.\n"
				<< "2. Display a specific route data.\n"
				<< "3. Display routes between 2 locations.\n"
				<< "4. Display all the locations within the range.\n"
				<< "5. List all invalid routes.\n"
				<< "6. Exit the program.\n"
				<< "-------------------------------------------------\n"
				<< "Enter your option: ";
			getline(cin, input);
			if (input == "1")
			{
				handleInputNewData(data);
				cout << "Added successful.\n";
			}
			else if (input == "2")
			{
				int startID = stoi(promptInput("Enter start location ID: "));
				int endID = stoi(promptInput("Enter end location ID: "));
				auto route = data.getRoute(startID, endID);
				if (route != nullptr)
				{
					cout << "The length of the route is: " << route->getLength() << '\n';
					cout << "The total area of the route is: " << route->getRouteArea() << "km2\n";
					cout << "Here are the infomation of how the road looks like:\n"
						<< route->describe();
				}
				else cout << "The direct route between these 2 locations does not exist.\n";
			}
			else if (input == "3") // only find valid route 
			{
				int start = stoi(promptInput("Enter start location ID: "));
				int dest = stoi(promptInput("Enter destination ID: "));
				auto possibleRoutes = data.findReverseRoutes(start, dest);
				if (possibleRoutes.empty()) 
					cout << "There is no possible routes between location ID " << start << " and location ID " << dest << ".\n";
				else 
					cout << "Total possible route(s) between location ID "
					<< start << " and location ID " 
					<< dest << ": " << possibleRoutes.size() << '\n';
				for (int n = 0; n < possibleRoutes.size(); n++)
				{
					cout << "Option " << n + 1 << ":\n";
					cout << possibleRoutes[n][possibleRoutes[n].size() - 1].getStartLoc().getId();
					for (int i = possibleRoutes[n].size() - 1; i >= 0; i--)
					{
						cout << '-' << possibleRoutes[n][i].getDestLoc().getId();
					}
					cout << '\n';
				}
			}
			else if (input == "4")
			{
				input = promptInput("Enter center location ID: ");
				const Location* cenLoc = data.findLocationById(stoi(input));
				if (cenLoc != nullptr)
				{
					input = promptInput("Enter the radius you want to find in km: ");
					auto list = data.listLocationsInRange(*cenLoc, stof(input));
					cout << "Here are the infomation of all the location within " << input << " from location ID " << cenLoc->getId() << ":\n";
					for (auto& ele : list)
					{
						cout << ele.describe() << '\n';
					}
				}
				else
				{
					cout << "Cannot find that location.\n";
				}
			}
			else if (input == "5")
			{
				auto invalidRoutes = data.listAllInvalidRoute();
				if (invalidRoutes.empty()) cout << "There is no invalid route.\n";
				else
				{
					cout << "List of invalid route:\n";
					for (auto& r : invalidRoutes)
					{
						cout << "The route with start location ID: " 
							<< r.getStartLoc().getId() 
							<< " and destination ID: " 
							<< r.getDestLoc().getId() << '\n';
					}
				}
			}
			else if (input == "6") break;
			else
			{
				cout << "Invalid option!\n";
				continue;
			}
		}
		catch (invalid_argument)
		{
			cout << "Invalid input! Please enter data again.\n";
		}
		system("pause");
		system("cls");
	}
	data.saveDataToFile("Location.txt", "Path.txt");
	cout << "Program exited! Press any key to close the window.\n";
	system("pause >nul");
}
