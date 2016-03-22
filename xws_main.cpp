#include "Grid.h"
#include "Dict.h"
#include "xws.h"
#include <iostream>
using namespace std;

extern int nodes;

int main(int argc, char* argv[])
{
	Grid xword;
	Dict dict;
	char* grid_file_name;
	char* dict_file_name;

	if(argc != 3)
	{
		cout << "Usage is: xws GRID_FILE_NAME DICT_FILE_NAME\n";
		return 0;
	}
	
	grid_file_name = argv[1];
	dict_file_name = argv[2];
	
	// Load grid.
	if(!xword.load(grid_file_name))
	{
		cout << "Could not load grid!\n";
		return 0;
	}
	
		// Print grid (which should be blank).
		xword.print();
	
	// Load dictionary.
	if(!dict.load(dict_file_name))
	{
		cout << "Could not load dictionary!\n";
		return 0;
	}

		// Print dictionary.
		// dict.print();
	
	cout << "\nSolving puzzle, please wait...\n";
	
	// For PMC in fill()
	rand_seed();
	rand_double(1,1);
	
	// Fill crossword from loaded dictionary.
	fill(xword, dict);
	
	// Print the now-filled grid.
	xword.print();
	
	cout << nodes << endl;

	return 0;
}