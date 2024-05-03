#include "BST.h"
using namespace std;

//Zainub Siddiqui, CS163, 6/2/23
//purpose - this is the client interface of the program
//and will include the menu function for this program. 
//The program will allow the user to add, remove, retrieve,
//display travel activites.

int main()
{
	table travel_collection;
	char location[100];
	char region[100];
    char todo[100];
	char season[100];
	char travelChoice[100];
	float cost {0.0};
	int height {0};
	int choice {0};
	int items_loaded {0};

	do 
	{
		choice = menu();
		if (choice == 1) //add new location to BST
		{
			travel travel_add;
			cout << "\nEnter Location: ";
			cin.get(location, 100); cin.ignore(100, '\n');
			cout << "Enter Region (State/Country): ";
			cin.get(region, 100); cin.ignore(100, '\n');
			cout << "Enter Things to Do: ";
			cin.get(todo, 100); cin.ignore(100, '\n');
			cout << "Enter Best Time of Year: ";
			cin.get(season, 100); cin.ignore(100, '\n');
			cout << "Enter Choice of Travel: ";
			cin.get(travelChoice, 100); cin.ignore(100, '\n');
			cout << "Enter Estimated Cost: ";
			cin >> cost; cin.ignore(100, '\n');
			travel_add.create_travel(location, region, todo, season, travelChoice, cost);

			//insert into BST
			if (!travel_collection.add_location(location, travel_add))
				cout << "Error - Failed to Add." << endl;
		}

		else if (choice == 2) //load from external file to BST
		{
			if (!travel_collection.load())
				cout << "Error - Couldn't load items." << endl;
			else
				cout << "Success - Loaded items." << endl;
		}

		else if (choice == 3) //remove location from BST
		{
			cout << "\nWhich location would you like to remove? ";
			cin.get(location, 100); cin.ignore(100, '\n');

			if (travel_collection.remove_location(location))
				cout << "Success - removed item." << endl;
			else
				cout << "Error - couldn't remove item." << endl;
		}
		
		else if (choice == 4) //retrieve location
		{
			cout << "\nWhat location would you like to retrieve? ";
			cin.get(location, 100); cin.ignore(100, '\n');
			travel an_entry;

			if (travel_collection.retrieve_location(location, an_entry))
			{
				an_entry.display();
			}
			else
			{
				cout << "\nLocation not found!" << endl;
			}
		}
		
		else if (choice == 5) //display all by season
		{
			cout << "Enter season: ";
			cin.get(season, 100); cin.ignore(100, '\n');

			if (!travel_collection.display_by_season(season))
				cout << "Season not found!" << endl;
		}

		else if (choice == 6) //display all
		{
			travel_collection.display_all();
		}
		
	} while (choice != 7);
	
	height = travel_collection.find_height();
	cout << "Height of BST: " << height << endl;

	return 0;
}

int menu()
{
	int choice {0};
	cout << "\nMenu Options:" << endl
	<< "1) Add a location" << endl
	<< "2) Load external file to BST" << endl
	<< "3) Remove by location name" << endl
	<< "4) Retrieve item by matching location" << endl
	<< "5) Display all by season" << endl
	<< "6) Display BST" << endl
	<< "7) Quit" << endl
	<< ">> ";
	cin >> choice; cin.ignore(100, '\n');
	return choice;
}

