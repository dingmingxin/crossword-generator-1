#ifndef DICT_H
#define DICT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

/*

ARELIS AND SHELLEY WORK IN ORANGE COLOR FONT
Here is the code for the member variables declaration, constructor, and destructor.
The code have been tested and compiled, it works.
If you would like a copy of it please message Arelis.

*/


class Dict
{
  //Declaring pointers of strings to store sorted
  //strings of words:
 public:
  vector<string> file_list;
  vector<string> TwoLet;
  //Stores string of
  vector<string> ThreeLet;
  //Stores string of
  vector<string> FourLet;
  //Stores string of
  vector<string> FiveLet;
  //Stores string of
  vector<string> SixLet;
  //Stores string of
  vector<string> SevenLet;
  //Stores string of

 public:

  //Declaring and defining constructor:
  Dict()
    {
      /* TwoLet = new string;
      ThreeLet = new string;
      FourLet = new string;
      FiveLet = new string;
      SixLet = new string;
      SevenLet = new string;*/
      TwoLet.clear();
      ThreeLet.clear();
      FourLet.clear();
      FiveLet.clear();
      SixLet.clear();
      SevenLet.clear();
}
      //Calling destructor:
      ~Dict();

      bool load(char* dict_file_name);
      void print();
      bool get_words(vector <string> &words, int length);
      int num_words(int length);

};
#endif

