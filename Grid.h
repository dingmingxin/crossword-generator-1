/*
 *  Grid.h
 *  Crossword Puz
 *
 *  Edited by TK.
 *
 */

#ifndef GRID_H
#define GRID_H

#include <fstream>
#include <list>
using namespace std;

enum orient{vertical,horizontal};

const char GRID_FILL_CHAR = ' ';
const char GRID_BLANK_CHAR = '_';
const char GRID_H_SPACE = ' ';
const char GRID_V_SPACE = ' ';


class Word
{
public:
	char * letters;
	int length;
	int startCol;
	int startRow;
	int endCol;
	int endRow;
	bool hasBlanks;
	orient direction;
	
	bool operator<(const Word&);		//need to overload < and > for sorting
	bool operator>(const Word&);
	Word operator=(const Word&);
	Word();
	~Word();
	Word(const Word &);
};

class Grid
{
private:
	char **crossword;					//2-dimensional array to hold puzzle rep
	int gridSize;						//number of columns & rows (all puzzles are square, i.e. rows=columns)
	list<Word> wordList;				//linked list to hold all words
	
	void updateWordList();
	void getLongestWordToBeFilled();
	int countEmptySquares();
	int getSize(ifstream&);				//used when importing new file
	
public:
	Grid();								// Default constructor
	Grid(const Grid &);					// Copy constructor
	Grid operator=(const Grid &);		// Overloaded operator =
	~Grid();							// Destructor
	
	bool load(const char*);				// load grid from passed file_name
	void print();						// print formatted puzzle
	void printWordList();				// print list of words
	int unfilled();						// return number of words to be filled
	bool next_word(char* &word, int &word_length);	//set reference params with info for next word to be filled
	bool fill_next_word(const char* word);			//place passed char* word into grid

};

#endif