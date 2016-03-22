#include "Dict.h"
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

//Defining Destrutor:
Dict::~Dict()
{
  /*delete TwoLet;
  delete ThreeLet;
  delete FourLet;
  delete FiveLet;
  delete SixLet;
  delete SevenLet;*/

}
/*
YANA AND KARUNYAS WORK IS IN PURPLE FONT COLOR.
*** Dict::load ***

Loads words from a file of the given name into the dictionary.

Dict file format:
Each line is a single word (that is, words are separated by newlines).
Words might contain spaces, apostrophes, hyphens - all such characters must
be cleaned from the word before storing it. Also, words must be converted

to ALLCAPS before storing them.
*/
bool Dict::load(char* dict_file_name)
{
  // #include <fstream>
  fstream read_file;

  string word;

  read_file.open(dict_file_name,ios::in);
  //Check for any file open errors,return 1
  if(!read_file)
    {
      cout<<"Error in opening file!"<<endl;
      return false;
    }


  getline(read_file,word);
  while (!read_file.fail())
  {

    getline(read_file,word);
    string str="";
    for(int j=0;j<word.size();j++)
  {
      if (word[j]!=' '&&word[j]!='-'&&word[j]!='\'')
      str+=toupper((word)[j]);

  }

    file_list.push_back(str);
  }

    //Close file
  read_file.close();
  
  //declare and initialize all indexes
  int ind2, ind3, ind4, ind5, ind6, ind7, length;
  length = ind2 = ind3 = ind4 = ind5 = ind6 = ind7 = 0;

  //if the vector is not empty, loop through all elements, get the size of ea string and place it in the appropriate vector by length
	if (!file_list.empty())
	{
		for (int index = 0; index < file_list.size(); index++)
    	{
			length = file_list[index].length();

			switch(length)
			{
				case 2:
				  TwoLet.push_back(file_list[index]);
				  ind2++;
				  break;
				case 3:
				  ThreeLet.push_back(file_list[index]);
				  ind3++;
				  break;
				case 4:
				  FourLet.push_back(file_list[index]);
				  ind4++;
				  break;
				case 5:
				  FiveLet.push_back(file_list[index]);
				  ind5++;
				  break;
				case 6:
				  SixLet.push_back(file_list[index]);
				  ind6++;
				  break;
				case 7:
				  SevenLet.push_back(file_list[index]);
				  ind7++;
				  break;
				default:
					;
					//cout<< file_list[index] << " is not a valid word (length 2 through 7).\n";
							 //<<"Discarding this word.\n";
			}//end switch
		}//end for
	}
  
  return true;

}

int Dict::num_words(int length)
{
	switch(length)
	{
		case 2:
			return TwoLet.size();
		case 3:
			return ThreeLet.size();
		case 4:
			return FourLet.size();
		case 5:
			return FiveLet.size();
		case 6:
			return SixLet.size();
		case 7:
			return SevenLet.size();
		default:
			return 0;
	}
}

/*

YANA AND KARUNYAS WORK IS IN PURPLE FONT COLOR.
*** Dict::print ***

Prints the dictionary, sorted and grouped by word length.
This is for debugging purposes.

*/

void Dict::print()
{
  int max = file_list.size();

  for (int i=0;i<max;i++)
    {
        cout<<file_list[i]<<"  ";
    if(i%5==0)cout<<endl;
    }
}

/*
SHAWNA’S WORK IS IN BLUE FONT

*** Dict::get_words ***

Stores all the dictionary words of the given length in the provided
string vector. Returns true if there are, in fact, words of that length,                                                  false otherwise.

*/
/***********************************************************************************
 *get_words()stores each word in the appropriate array of strings based on length. *
 *It accepts an unsorted array of strings and returns success/failure status if    *
 *there were elements in the array, and therefore a member variable                *
 ***********************************************************************************/

bool Dict::get_words(vector <string> &words, int length)
{
	words.clear();

	switch(length)
	{
		case 2:
			if(TwoLet.size() != 0)
			{
				words = TwoLet;
				return true;
			}
			else return false;
		case 3:
			if(ThreeLet.size() != 0)
			{
				words = ThreeLet;
				return true;
			}
			else return false;
		case 4:
			if(FourLet.size() != 0)
			{
				words = FourLet;
				return true;
			}
			else return false;
		case 5:
			if(FiveLet.size() != 0)
			{
				words = FiveLet;
				return true;
			}
			else return false;
		case 6:
			if(SixLet.size() != 0)
			{
				words = SixLet;
				return true;
			}
			else return false;
		case 7:
			if(SevenLet.size() != 0)
			{
				words = SevenLet;
				return true;
			}
			else return false;
		default:
			return false;
	}
}

