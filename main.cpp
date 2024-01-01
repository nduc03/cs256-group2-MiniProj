#include <iostream>
#include <string>
#include "BKMapData.h"

using namespace std;

int main()
{
    string option;
    do {
        cout << "BKMap program\n"
            << "1. Add data: Add new routes or locations.\n"
            << "2. Display data.\n"
            << "3. Display routes.\n"
            << "4. Display locations.\n"
            << "5. Check valid data.\n"
            << "6. Exit the program.\n"
            << "Enter your option: ";
        getline(cin, option);
        if (option  == "1") {

        }
        else if (option == "2") {
            // Enter 2 locations, display direct routes between them (if any), draw a map of the route, and calculate the route area.
        }
        else if (option == "3") {
            // Enter 2 locations, display a number for routes (direct and indirect) between them (if any), 
            // and draw a map of the routes sorted by length between the two locations.
        }
        else if (option == "4") {
            // Enter a location and any distance to display all locations within that distance from the entered location
        }
        else if (option == "5") {
            // Check the validity of data: check all routes for any route with a length less than the distance between two points, 
            // check if routes have valid starting and ending points.
        }
        else {
            cout << "Invalid option!";
            continue;
        }
    } while (option == "6");
    cout << "Program exited!";
}
