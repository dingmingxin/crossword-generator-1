/*
 *  Grid.cpp
 *  Crossword Puz
 *
 */
#include "Grid.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

/********************************************
 *
 * Word class- implementation of basic functions
 *	
 * bool operator<(const Word&);		//need to overload < and > for sorting
 * bool operator>(const Word&);
 * Word operator=(const Word&);
 * Word();
 * ~Word();
 * Word(const Word&);
 ********************************************/

bool Word::operator<(const Word& right)	//overloaded < operator, used for sorting
{
	
	//if they both have blanks, or they both don't have blanks, then compare length
	if((hasBlanks && right.hasBlanks) || (!hasBlanks && !right.hasBlanks)){	
		if (length < right.length)
			return true;
		else
			return false;
	}
	else if(hasBlanks && !right.hasBlanks) //if left has blanks, and right doesn't, then left is 'bigger'
		return false;
	else if(!hasBlanks && right.hasBlanks) //if left has no blanks, and right does, then right is 'bigger'
		return true;
	return true;
}

bool Word::operator>(const Word& right) //overloaded > operator
{
	//if they both have blanks, or they both don't have blanks, then compare length
	if((hasBlanks && right.hasBlanks) || (!hasBlanks && !right.hasBlanks)){	
		if (length > right.length)
			return true;
		else
			return false;
	}
	else if(hasBlanks && !right.hasBlanks) //if left has blanks, and right doesn't, then left is 'bigger'
		return true;
	else if(!hasBlanks && right.hasBlanks) //if left has no blanks, and right does, then right is 'bigger'
		return false;
	return false;
}

Word Word::operator=(const Word& right)	//overloaded = operator
{
	//copy all properties to calling Word object
	
	this->length = right.length;
	this->startCol = right.startCol;
	this->startRow = right.startRow;
	this->endCol = right.endCol;
	this->endRow = right.endRow;
	this->hasBlanks = right.hasBlanks;
	this->direction = right.direction;
	
	if(this->letters!=NULL)
		delete letters;
	this->letters = new char[this->length];
	strncpy(this->letters, right.letters, right.length);
	
	return *this;
}

Word::Word()
{
	letters = NULL;
}

Word::~Word() // destructor
{
	delete letters;
}

Word::Word(const Word& right){

	//copy all properties to calling Word object
	
	this->length = right.length;
	this->startCol = right.startCol;
	this->startRow = right.startRow;
	this->endCol = right.endCol;
	this->endRow = right.endRow;
	this->hasBlanks = right.hasBlanks;
	this->direction = right.direction;
	
	this->letters = new char[this->length];
	strncpy(this->letters, right.letters, right.length);
	
	return;
}

/********************************************
 *
 * Grid class implementation, listed in the following order:
 *
 * Grid();								// Default constructor
 * ~Grid();								// Destructor
 * Grid(const Grid &);					// Copy constructor
 * Grid operator=(const Grid &);		// assignment operator =
 *
 * int getSize(ifstream&);				// used by load() when importing new file
 * bool load(const char*);				// load grid from passed file_name
 * void updateWordList();				// find all words in puzzle, make wordList
 *
 * int countEmptySquares();				// return number of squares to be filled
 * int unfilled();						// return number of words to be filled

 * void print();						// print formatted puzzle
 * void printWordList();				// print list of words
 *
 * bool next_word(char* &word, int &word_length);	//set reference params with info for next word to be filled
 * bool fill_next_word(const char* word);			//place passed char* word into grid
 *
 ********************************************/
Grid::Grid() // The constructor
{
	crossword = NULL;
	gridSize = 0;

}

Grid::~Grid() // The destructor deletes the dynamically allocated array
{
	if(crossword!=NULL){
		for(int i = 0; i < gridSize; i++){
			delete [] crossword[i];
		}
		delete [] crossword;
	}
}

Grid::Grid(const Grid &right) //This is the copy constructor
{
	gridSize = right.gridSize;
	crossword = new char *[gridSize];

	//for each line, allocate memory and copy characters
	for(int i = 0; i < gridSize; i++){
		crossword[i] = new char [gridSize];
		for(int j=0; j<gridSize; j++){
			crossword[i][j] = right.crossword[i][j];
		}
	}
	
	this->updateWordList();
}

Grid Grid::operator=(const Grid &right) //This is the assignment operator
{
	if(right.crossword!=NULL){
		gridSize = right.gridSize;
		crossword = new char *[gridSize];
		//for each line, allocate memory and copy characters
		for(int i = 0; i < gridSize; i++){
			crossword[i] = new char [gridSize];
			for(int j=0; j<gridSize; j++){
				crossword[i][j] = right.crossword[i][j];
			}
		}
		this->updateWordList();
	}
	else {
		crossword = NULL;
		gridSize = 0;
	}

	return *this;
}

//private function called by load(). Passed parameter is the file (ifstream) as imported by load()
//returns integer of number of columns and rows. Returns negative value if invalid grid
int Grid::getSize(ifstream& sourceFile)
{
	int puzSize=0, rowLength;
	string tempString;

	//count how many rows of text
	while(sourceFile.good()){
		getline(sourceFile, tempString);
		puzSize++;
	}
	
	sourceFile.seekg(0,ios::beg);	//move cursor back to beginning
	sourceFile.clear();				//clear error flags
	
	//go through each line again, checking there are the right number of columns in each row
	while(!sourceFile.eof()){
		getline(sourceFile, tempString);
		rowLength = tempString.length();
		if(rowLength!=puzSize){ //if # of columns does not match # of rows
			cout << "Wrong number of columns in this row: "<<tempString<<endl;
			return -1; //if there is a problem, return negative number (and exit)
		}
	}
	sourceFile.seekg(0,ios::beg);	//when finished, make sure to leave cursor at beginning of file
	sourceFile.clear();				//clear error flags
	return puzSize;
}
				  
//Reads file (from passed filename), and checks if file is valid (has characters set by specs team
//If valid, imports the puzzle 'frame' into crossword**
//Returns true if successful, false (with message) if there was a problem
bool Grid::load(const char * filename)
{
	ifstream sourceFile(filename);
	bool gridcheck = true;  //assume true, change to false if finds errors
	char * line;
	
	if(!sourceFile){	//if file didn't open
		cout<<"File could not be opened.";
		return false;
	}
	else {
		//figure out dimensions of puzzle
		gridSize = getSize(sourceFile);
		cout<<"Gridsize is "<<gridSize<<endl;
		
		if(gridSize<0){ //if there was a problem
			cout<<"Grid not in correct format.\n";
			gridcheck = false;
		}
		else {
			line = new char[gridSize];			//use as temp variable
			crossword = new char*[gridSize];	//allocate new multidimensional array (1st dimension)
			
			for(int i=0;i<gridSize;i++){		// for each line
				crossword[i] = new char[gridSize];//allocate 2nd dimension

				if(sourceFile.good()){		// make sure still in the file
					
					sourceFile.getline(line, gridSize+1);	
						
					for(int j=0;j<gridSize;j++){ // for each column
						//check if valid character
						if(line[j]==GRID_FILL_CHAR || line[j]==GRID_BLANK_CHAR)
							crossword[i][j] = line[j];
						else{
							cout<<"Problem here ("<<line[j]<<") in line "<<i;
							gridcheck = false; 
						}
					}
				}
			}
		}
	}
	updateWordList();	//call to create linked list of word objects
	return gridcheck;	
}

// scan through the puzzle, first by row and then by column, and make a new item in wordList for each set of consecutive spaces (i.e. words)
// then sort list<Word> by descending word length (so longest word on top)
void Grid::updateWordList()
{
	Word tempWord;
	int startPos=0, endPos=1, tempLength=1;
	bool gotWord=false;
	wordList.clear();
	
	//get horizontal words.
	
	for(int row=0;row<gridSize;row++){	//for each row
		
		startPos = 0;
		endPos = 0;
		
		while(endPos<gridSize-1){							//make sure still within grid
			for(int i=startPos;i<gridSize-1; i++){			//go through column
				
				if(i<endPos)								//if inside last word that was found
					gotWord=false;							//do nothing
				else{
					if(crossword[row][i]!=GRID_FILL_CHAR){	//only continue if not a filled (black) square
						
						tempLength = 0;
						for(int len=0;len<gridSize-i;len++){	//count until hit next black square
							if(crossword[row][i+len]==GRID_FILL_CHAR)
								break;
							tempLength++;
						}
						
						if(tempLength>1){						//if word length is >1, make a new entry in list
							tempWord.length = tempLength;
							tempWord.startCol = i;
							tempWord.endCol = i+tempLength-1;
							tempWord.startRow = row;
							tempWord.endRow = row;
							tempWord.hasBlanks = false;
							tempWord.direction = horizontal;
							tempWord.letters = new char[tempLength];
							
							for(int x=0;x<tempLength;x++){		//see if there are any blanks, copy letters into tempWord
								if(crossword[row][x+i]==GRID_BLANK_CHAR)
									tempWord.hasBlanks = true;
								tempWord.letters[x] = crossword[row][x+i];
							}
						//	tempWord.letters[tempWord.length]='\0';
							wordList.push_back(tempWord);		//put on list
							gotWord = true;
							endPos = i+tempLength-1;
						}
					}
					
					if (!gotWord) {		//if didn't get a new word from current start position, move startPos and loop again
						startPos=i;
						endPos = i+1;
					}
				}
			}
		}
	}
	
	//get vertical words.
	
	for(int col=0;col<gridSize;col++){	//for each column
		
		startPos = 0;
		endPos = 0;
		
		while(endPos<gridSize-1){							//make sure still within grid
			for(int i=startPos;i<gridSize-1; i++){			//go through column
				if(i<endPos)								//if inside last word that was found
					gotWord=false;							//do nothing
				
				
				else{
					
					if(crossword[i][col]!=GRID_FILL_CHAR){	//only continue if not a filled (black) square
						
						tempLength = 0;
						for(int len=0;len<gridSize-i;len++){	//count until hit next black square
							if(crossword[i+len][col]==GRID_FILL_CHAR)
								break;
							tempLength++;
						}
						
						if(tempLength>1){						//if word length is >1, make a new entry in list
							tempWord.length = tempLength;
							tempWord.startCol = col;
							tempWord.endCol = col;
							tempWord.startRow = i;
							tempWord.endRow = i+tempLength-1;
							tempWord.letters = new char[tempLength];
							tempWord.hasBlanks = false;
							tempWord.direction = vertical;
							for(int x=0;x<tempLength;x++){		//see if there are any blanks, copy letters into tempWord
								if(crossword[i+x][col]==GRID_BLANK_CHAR)
									tempWord.hasBlanks = true;
								tempWord.letters[x] = crossword[i+x][col];
							}
							
							wordList.push_back(tempWord);		//put on list
							gotWord = true;
							endPos = i+tempLength-1;
						}
					}
					if (!gotWord) {		//if didn't get a new word from current start position, move startPos and loop again
						startPos=i+1;
						endPos = i+1;
					}
				}
				
			}
		}
	}
	wordList.sort();
	wordList.reverse();
	printWordList();
	return;
}

//Prints out formatted grid
void Grid::print() 
{
	cout << "Printing puzzle"<<endl;
	for(int i = 0; i < gridSize; i++){	// for each line
		for(int j = 0; j < gridSize; j++){	//for each column in the line
			cout<<crossword[i][j]<<GRID_H_SPACE;	//print character
		}
		cout<<endl;	
		for(int x=0;x<gridSize;x++)		// in between each line, have a separator line
			cout<<GRID_V_SPACE<<GRID_V_SPACE;
		cout << endl;
	}
}

// print contents of linked list of words
void Grid::printWordList()
{
	string directionToPrint;
	
	cout<<"\nPrinting wordList ("<<wordList.size()<<" items):\n";
	cout << "Orientation   StartRow   EndRow   StartCol  EndCol   Length   Word:"<<endl;
	
	for(list<Word>::iterator iter=wordList.begin(); iter!=wordList.end(); iter++){
		if(iter->direction==0)
			directionToPrint = "horizontal";
		else if(iter->direction==1)
			directionToPrint = "vertical";
			
		cout<<setw(15)<<left<<directionToPrint;
		cout<<setw(10)<<iter->startRow<<setw(10)<<iter->endRow
			<<setw(10)<<iter->startCol<<setw(10)<<iter->endCol<<setw(8)<<iter->length
			<<"      |";
			
			for(int i = 0; i < iter->length; i++)
				cout << iter->letters[i];
			
			cout<<"|\n";
	}
	cout<<"\n\n";
	return;
}

// go through crossword** and count number of spaces equal to the 'blank' character
int Grid::countEmptySquares()
{
	int numEmptySquares = 0;
	
	for(int i=0; i<gridSize; i++)
		for(int j=0; j<gridSize; j++)
			if(crossword[i][j] == GRID_BLANK_CHAR)
				numEmptySquares++;
	
	return numEmptySquares;
}

//Returns the number of not-yet-filled words (0 if the crossword is completed)
int Grid::unfilled()
{
	int anyUnfilledWords = 0;
	int unfilledSquares;
	
	for(list<Word>::iterator iter=wordList.begin(); iter!=wordList.end(); iter++)
			if(iter->hasBlanks)
				anyUnfilledWords++;
	
	unfilledSquares = countEmptySquares();
	
	if(anyUnfilledWords && unfilledSquares==0 || !anyUnfilledWords && unfilledSquares>0)
		cout<<"Uh-oh. There is an inconsistency in the grid.\n";
		
	return anyUnfilledWords;
}

//Stores the next word to be filled in the given character array, and its length in the given integer. 
//Returns true if there is a word to be filled, false if the words are all filled.
bool Grid::next_word(char* &word, int &word_length)
{
	Word tempWord;
	
	if(unfilled()>0){
		tempWord = wordList.front();
		word_length = tempWord.length;
		
		if(word!=NULL)
			delete word;
		word = NULL;
		word = new char[word_length + 1];
		
		strncpy(word, tempWord.letters, tempWord.length);
		word[word_length] = NULL;
		
		return true;
	}
	else
		return false;
}

//Fills the next-word-to-be-filled with the given char array. Returns true if
//successful, false otherwise.
bool Grid::fill_next_word(const char* word)
{
	Word tempWord;
	
	tempWord = wordList.front();
	if(!tempWord.hasBlanks){
		cout<<"Word does not need to be filled. There's a problem.";
		return false;
	}
	
	if(strlen(word)!=tempWord.length){
		cout<<"You entered a word that's the wrong size. ";
		return false;
	}
	
	for(int i=0;i<tempWord.length;i++){
		if(tempWord.letters[i]==GRID_BLANK_CHAR){ //blank and ready to be filled
			if(tempWord.direction==horizontal)
				crossword[tempWord.startRow][tempWord.startCol + i] = word[i];
			if(tempWord.direction==vertical)
				crossword[tempWord.startRow+i][tempWord.startCol]=word[i];
			//cout<<"filled in blank spot.\n";
		}
		else if(tempWord.letters[i]!=word[i]){
			cout<<"Cannot overwrite position "<<i<<"- '"<<tempWord.letters[i]<<"' with '"<<word[i]<<". Enter a valid word.\n";
			return false;
		}
	}
	updateWordList();
	return true;
}
