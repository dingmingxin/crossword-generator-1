#include "Dict.h"
#include "Grid.h"
#include "xws.h"
#include <iostream>
using namespace std;

int nodes = 0;

bool fill(Grid &xword, Dict &dict)
{
	// Count how many tree nodes we've visited. Debugging only.
	nodes++;

	// If the crossword is fully filled, we don't have to do anything.
	if(xword.unfilled() == 0)
		return true;
	
	// Variables to store the next-word-to-be-filled, and its length.
	char* word = NULL;
	int word_length;
	
	// Vector to store all dictionary words of the given length.
	vector <string> words_this_long;
	
	int i = 0;
	int num_words_tried = 0;
	
	// This will store a temporary copy of the passed Grid object.
	Grid new_xword;

	// Get the next-word-to-be-filled from the grid.
	xword.next_word(word, word_length);
	
	// Get all dictionary words of the same length as the next-word-to-be-filled.
	dict.get_words(words_this_long, word_length);
	
//	for(i = 0; i < dict.num_words(word_length); i++)

	while(num_words_tried < dict.num_words(word_length))
	{
		if(rand_double(1,100) > P_M_C_FACTOR)
		{
			// If this dictionary word "fits" (that is, if its letters don't conflict
			// with any already-filled letters of the next-word-to-be-filled)...
			if(word_fits(word, words_this_long[i]))
			{
				// ... then fill the next-word with that dictionary word,
				// and go down a level.
				
				new_xword = xword;
	
				if(new_xword.fill_next_word(words_this_long[i].data()))
				{
		//			new_xword->print();
					
					if(fill(new_xword, dict))
					{
						xword = new_xword;
						return true;
					}
				}
			}
			
			num_words_tried++;
		}
		
		i++;
		if(i == dict.num_words(word_length))
			i = 0;
	}

	return false;
}

bool word_fits(char* word, const string &dict_word)
{
//	if(strlen(word) != dict_word.length())
//		return false;
		
	int i;
	
	for(i = 0; i < dict_word.length(); i++)
		if(word[i] != GRID_BLANK_CHAR)
			if(word[i] != dict_word[i])
				return false;

	return true;
}

void rand_seed()
{
//	int seed = (int)time(0);
	srand((int)time(0));
}

double rand_double(double low, double high)
{
	return low + ((high-low) * rand() * (1.0/RAND_MAX));
}