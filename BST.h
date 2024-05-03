#include <cstring>
#include <cctype>
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>

//Zainub Siddiqui, CS163, 6/2/23
//Purpose - This is the header file for the table ADT which
//will implement a BST for the data structure. It will 
//include class interfaces and function prototypes.

int menu();

class travel
{
	public:
	travel();
	~travel();
	int create_travel(char * locationToAdd, char * regionToAdd, char * todoToAdd, char * seasonToAdd, char * travelToAdd, float costToAdd);
	int copy_travel(travel & copy_from);
	int convert_to_lower(char * input);
	int retrieve(char * location, travel & copy_to);
	int location_matches(char * location_to_find);
	int compare(char * location_to_add);
	int season_matches(char * season_to_find);
	int display();

	private:
	char * location;
	char * region;
	char * todo;
	char * season;
	char * travelChoice;
	float cost;
};

struct node 
{
	travel travel_entry;
	node * left;
	node * right;
};

class table
{
	public:
	table();
	~table();
	int find_height();
	int load();
	int add_location(char * location, travel & to_add);
	int remove_location(char * location);
	int retrieve_location(char * location_to_find, travel & found);
	int display_all();
	int display_by_season(char * season);

	private:
	int find_height(node * root);
	int add_location(node * &root, char * location, travel & to_add);
	int remove_location(node * &root, char * location);
	int retrieve_location(node * root, char * location_to_find, travel & found);
	int display_by_season(node * root, char * season);
	int display_all(node * root);
	int remove_all(node * &root);
	node * root;
	int height;
};


