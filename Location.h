#pragma once
struct Location
{
	int id;
	float longitude, latitude;
	Location(int id, float longitude, float latitude);
	static float getDistance(Location loc1, Location loc2);
};

