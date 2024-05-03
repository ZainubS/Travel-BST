#include "BST.h"
using namespace std;

//Zainub Siddiqui, CS163, 6/2/23
//Purpose - this file will implement the member functions of the travel class
//for an individual travel entry

//constructor - initilize data members
travel::travel()
{
	location = NULL;
	region = NULL;
	todo = NULL;
	season = NULL;
	travelChoice = NULL;
	cost = 0.0;
}

//destructor - deallocate dynamic memory
travel::~travel()
{
	delete [] location;
	delete [] region;
	delete [] todo;
	delete [] season;
	delete [] travelChoice;
	location = region = todo = season = travelChoice = NULL;
}

//compares added location to current location
int travel::compare(char * location_to_add)
{
	if (!location || !location_to_add)
		return 0;
	if (strcmp(location_to_add, location) > 0)
	{
		return 1;
	}
	else if (strcmp(location_to_add, location) == 0)
	{
		return 2;
	}
	else if (strcmp(location_to_add, location) < 0)
	{
		return 0;
	}

	return 0;
}
//converts string to all lower
int travel::convert_to_lower(char * input)
{
	int size = strlen(input);
	for (int i = 0; i < size; ++i)
	{
		if (isalpha(input[i]))
				input[i] = tolower(input[i]);
	}
	return 1;
}

//create travel entry
int travel::create_travel(char * locationToAdd, char * regionToAdd, char * todoToAdd, char * seasonToAdd, char * travelToAdd, float costToAdd)
{
	if (!locationToAdd || !regionToAdd || !todoToAdd || !seasonToAdd || !travelToAdd)
		return 0;

	if (location)
		delete [] location;
	if (region)
		delete [] region;
	if (todo)
		delete [] todo;
	if (season)
		delete [] season;
	if (travelChoice)
		delete [] travelChoice;
	location = region = todo = season = travelChoice = NULL;
	
	convert_to_lower(locationToAdd);
	location = new char[strlen(locationToAdd) + 1];
	strcpy(location, locationToAdd);
	region = new char[strlen(regionToAdd) + 1];
	strcpy(region, regionToAdd);
	todo = new char[strlen(todoToAdd) + 1];
	strcpy(todo, todoToAdd);
	season = new char[strlen(seasonToAdd) + 1];
	strcpy(season, seasonToAdd);
	travelChoice = new char[strlen(travelToAdd) + 1];
	strcpy(travelChoice, travelToAdd);
	cost = costToAdd;
	return 1;
}

//copy travel entry
int travel::copy_travel(travel & copy_from)
{
	int success = create_travel(copy_from.location, copy_from.region, copy_from.todo, copy_from.season, copy_from.travelChoice, copy_from.cost);
	return success;
}

//check if location is same as argument passed in
int travel::location_matches(char * location_to_find)
{
	bool found = false;

	if (!location)
		return found;

	if (strcmp(location, location_to_find) == 0)
	{
		found = true;
	}

	return found;
}

//check if season is same as argument passed in
int travel::season_matches(char * season_to_find)
{
	bool found = false;

	if (!season)
		return found;

	if (strcmp(season, season_to_find) == 0)
	{
		found = true;
	}

	return found;
}

//retrieve information by location name
int travel::retrieve(char * location_find, travel & copy_to)
{
	if (!location || !region || !todo || !season || !travelChoice)
		return 0;

	int success = 0;

	if (strcmp(location, location_find) == 0)
	{
		copy_to.location = new char[strlen(location) + 1];
		strcpy(copy_to.location, location);
		copy_to.region = new char[strlen(region) + 1];
		strcpy(copy_to.region, region);
		copy_to.todo = new char[strlen(todo) + 1];
		strcpy(copy_to.todo, todo);
		copy_to.season = new char[strlen(season) + 1];
		strcpy(copy_to.season, season);
		copy_to.travelChoice = new char[strlen(travelChoice) + 1];
		strcpy(copy_to.travelChoice, travelChoice);
		copy_to.cost = cost;
		success = 1;
	}

	return success;
}

//display travel entry
int travel::display()
{
	if (!location || !region || !todo || !season || !travelChoice)
		return 0;

	cout << "**************************************" << endl
	<< "Location: " << location << "\nRegion: " << region 
	<< "\nAttractions: " << todo << "\nBest Time of Year: " <<
	season << "\nTravel Choice: " << travelChoice << "\nEstimated Cost: " 
	<< cost << "\n**************************************" << endl;

	return 1;
}







