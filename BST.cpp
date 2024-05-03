#include "BST.h"
using namespace std;

//Zainub Siddiqui, CS163, 6/2/23
//Purpose - This file will implement the member functions
//of the table ADT for a BST.

//constructor - initialize table
table::table()
{
	root = nullptr;
	height = 0;
}

//destructor - deallocate dynamic memory
table::~table()
{
	remove_all(root);
}

//remove all - recursive
int table::remove_all(node * &root)
{
	if (!root) 
		return 0;
	int count = remove_all(root->left);
	count += remove_all(root->right);
	++count;
	delete root;
	root = nullptr;
	return count;
}

//add location to BST - wrapper
int table::add_location(char * location, travel & to_add)
{
	return add_location(root, location, to_add);
}

//add location to BST - recursive
int table::add_location(node * &root, char * location, travel & to_add)
{
	if (!root)
	{
		root = new node;
		int success = root->travel_entry.copy_travel(to_add);
		root->left = nullptr; root->right = nullptr;
		return success;
	}

	if (!root->travel_entry.compare(location)) //location added is less than root->location
		add_location(root->left, location, to_add);
	else if (root->travel_entry.compare(location)) //location added is greater than root->location
		add_location(root->right, location, to_add);
	return 1;
}

//display all - wrapper 
int table::display_all()
{
	if (!root)
		return 0;
	return display_all(root);
}

//display all sorted - recursive
int table::display_all(node * root)
{
	if (!root)
		return 0;
	int count = display_all(root->left);
	root->travel_entry.display();
	return ++count + display_all(root->right);
}

//remove location from BST - wrapper
int table::remove_location(char * location)
{
	if (!root)
		return 0;
	return remove_location(root, location);
}

//remove location from BST - recursive
int table::remove_location(node * &root, char * location)
{
	int success = 1;
	if (!root)
		return 0;
	if (!root->travel_entry.compare(location)) //location added is less than root->location
   	     success = remove_location(root->left, location);
	else if (root->travel_entry.compare(location) == 1) //location added is greater than root->location
		success = remove_location(root->right, location);

	else if (root->travel_entry.compare(location) == 2) //found match
	{
		//node is leaf
		if (!root->left && !root->right) 
		{
			delete root;
			root = nullptr;
		}
		// node has one child	
		else if (!root->right && root->left) 
		{
			node * hold = root->left;
			delete root;
			root = hold;
		}
		
		else if (!root->left && root->right)
		{
			node * hold = root->right;
			delete root;
			root = hold;
		}
		//node has two children - Find IOS
		else if (root->left && root->right)
		{
			cout << "node to remove is with two children." << endl;
			node * current = root->right;
			node * previous = nullptr;
			node * hold = nullptr;
			while (current->left)
			{
				previous = current;
				current = current->left;
			}
			//copy data of IOS into node to delete
			root->travel_entry.copy_travel(current->travel_entry);
			//check for & hold onto IOS right child & adopt
			if (previous)
			{
				hold = current->right;
				delete current;
				previous->left = hold; 
			}
			else
			{
				delete current;
				root->right = nullptr;
			}
		}
		success = 1;
	}
	
	return success;
}

//retrieve location - wrapper
int table::retrieve_location(char * location_to_find, travel & found)
{
	if (!root)
		return 0;
	return retrieve_location(root, location_to_find, found);
}

//retrieve location - recursive
int table::retrieve_location(node * root, char * location_to_find, travel & found)
{
	int success = 0;
	if (!root)
		return 0;
	if (root->travel_entry.compare(location_to_find) == 2)
	{
		root->travel_entry.retrieve(location_to_find, found);
		return 1;
	}
	if (!root->travel_entry.compare(location_to_find)) //less than root->location
	{
		success = retrieve_location(root->left, location_to_find, found);
	}

	else if (root->travel_entry.compare(location_to_find) == 1) //greater than root->location
	{
		success = retrieve_location(root->right, location_to_find, found);
	}

	return success;
}

//display all by season - wrapper
int table::display_by_season(char * season)
{
	if (!root)
		return 0;
	return display_by_season(root, season);
}

//display all by season - recursive
int table::display_by_season(node * root, char * season)
{
	if (!root)
		return 0;
	int count = display_by_season(root->left, season);
	if (root->travel_entry.season_matches(season))
	{
		root->travel_entry.display();
		++count;
	}
	return count += display_by_season(root->right, season);

}

//determine height of BST - wrapper
int table::find_height()
{
	if (!root)
		return 0;
	return find_height(root);
}

//determine height of BST - recursive
int table::find_height(node * root)
{
	if (!root) 
		return 0;
	int height_left = find_height(root->left);
	int height_right = find_height(root->right);
	int height = max(height_left, height_right) + 1;
	return height;
}

//load items from external data file into BST
int table::load()
{
	ifstream file_in; //input from file
	char location[100];
	char region[100];
	char todo[100];
	char season[100];
	char travelChoice[100];
	float cost = 0; 
	int count = 0;
	int success {0};
	
	file_in.open("travel.txt");
	if (file_in)
	{
		file_in.get(location, 100, '|');
		file_in.ignore(100, '|');

		while (file_in && !file_in.eof())
		{
			travel to_load;
			file_in.get(region, 100, '|');
			file_in.ignore(100, '|');
			file_in.get(todo, 100, '|');
			file_in.ignore(100, '|');
			file_in.get(season, 100, '|');
			file_in.ignore(100, '|');
			file_in.get(travelChoice, 100, '|');
			file_in.ignore(100, '|');
			file_in >> cost;
			file_in.ignore(100, '\n');
			++count;
			
			to_load.create_travel(location, region, todo, season, travelChoice, cost);
			success = add_location(location, to_load);

			file_in.get(location, 100, '|');
			file_in.ignore(100, '|');
		}
		file_in.close();
	}
	
	cout << count << " Items loaded." << endl;
	return success;
}





