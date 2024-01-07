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
	return true;
}

static string promptInput(const string& prompt)
{
	cout << prompt;
	string buf;
	getline(cin, buf);
	return buf;
}

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
				cout << "Created new location with ID: " << id;
				input = promptInput("Enter latitude: ");
				float lat = stof(promptInput("Enter latitude: "));
				input = promptInput("Enter latitude: ");
				float longitude = stof(promptInput("Enter latitude: "));
				data.addLocation(id, longitude, lat);
			}
			else if (input == "2")
			{
				Location start = data.findLocationById(stoi(promptInput("Enter start location ID:")));
				if (start == Location())
				{
					cout << "Invalid input! Please enter data again.";
					continue;
				}
				Location dest = data.findLocationById(stoi(promptInput("Enter end location ID: ")));
				if (dest == Location())
				{
					cout << "Invalid input! Please enter data again.";
					continue;
				}
				float length = stof(promptInput("Enter route length: "));
				cout << "Describe every position of the route in number with the format like this: position, width, type.\n"
					<< "Where type is 1 when that part is indented, type is 2 when it is diagonal.\n"
					<< "Must include at least one begin position equal 0 and one last position equal to the length";
				vector<string> chunkFormatlist;
				while (true)
				{
					input = promptInput("Describe the part or type EXIT to stop input: ");
					if (input == "EXIT") break;
					if (BKMapData::checkValidChunkFormat(input))
					{
						// TODO: cân thiết nên check các postion có hợp lệ không
						// tức là cần check 0 <= pos <= length, và pos trước nhỏ hơn pos sau
						chunkFormatlist.push_back(input);
					}
					else cout << "Invalid input! Please enter data again.";
				}
				if (chunkFormatlist.size() < 2) cout << "Invalid input! Please enter data again.";
				data.addRoute(start.getId(), dest.getId(), length, chunkFormatlist);
			}
			else cout << "Invalid input! Please enter data again.";
		}
		catch (invalid_argument)
		{
			cout << "Invalid input! Please enter data again.";
		}
		break;
	}
}

int main()
{
	BKMapData data;
	try
	{
		data = BKMapData::initFromFile("path/placeholder1", "path/placeholder2");
	}
	catch (ios_base::failure e)
	{
		cout << e.what();
	}
	string input;
	do
	{
		cout << "------------------------------------------------"
			<< "BKMap program\n"
			<< "1. Add a new location or a new route.\n"
			<< "2. Display a specific route data.\n"
			<< "3. Display routes between 2 locations.\n"
			<< "4. Display locations.\n"
			<< "5. Check valid route.\n"
			<< "6. Exit the program.\n"
			<< "-------------------------------------------------"
			<< "Enter your option: ";
		getline(cin, input);
		if (input == "1")
		{
			handleInputNewData();
		}
		else if (input == "2")
		{
			// Enter 2 locations, display direct routes between them (if any), draw a map of the route, and calculate the route area.
		}
		else if (input == "3")
		{
			// Enter 2 locations, display a number for routes (direct and indirect) between them (if any), 
			// and draw a map of the routes sorted by length between the two locations.
		}
		else if (input == "4")
		{
			// Enter a location and any distance to display all locations within that distance from the entered location
		}
		else if (input == "5")
		{
			// Check the validity of data: check all routes for any route with a length less than the distance between two points, 
			// check if routes have valid starting and ending points.
		}
		else
		{
			cout << "Invalid option!";
			continue;
		}
	} while (input == "6");
	data.saveDataToFile("path/placeholder1", "path/placeholder2");
	cout << "Program exited!";
}
