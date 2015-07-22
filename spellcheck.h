//
// Created by Phealey on 19/05/2015.
//

#include <algorithm>
#include <fstream>
#include <string>
#include <string.h>
#include "bintree.h"

using namespace std;

class spellcheck
{
   private:


   int amountOfWords;
   int amountOfUnknownWords;

   /*Method: processLine
   * -------------------
   * This method uses the strok to tokenise words found in a single line
   * It then performs a loop whereby the first token is taken out of the line
   * and then processed to see what kind of token it is (word/number/unkown word)
   * If a word is found in the dictionary, it increments the amountOfWords variable
   * by one, if an unknown word is found (that is not a number), it increments both
   * the amount of words and amount of unknonwn words variable.
   * It does this until the last token of the line is found.
   */

   void processLine(char *line)
   {
      char spellingCharacters[] = " .,;:\\\"~!#%^*()-=+[]{}\\\\|<>?\t\n\r\\/";
      char *characters = strtok(line, spellingCharacters); //cut out words
      string word;
      while (characters)
      {//keep looping until last word is found
         word = characters;
         transform(word.begin(), word.end(), word.begin(), ::tolower);
         if(dictionaryTree.find(word) != NULL) //word found
         {
            amountOfWords++;
         }
         else if(!isNumber(word))
         {//non-number word doesn't exist
         //print out word
            cout << word << endl;
            amountOfUnknownWords++;
            amountOfWords++;
         }
         //change to lower case
         characters = strtok(NULL, spellingCharacters);
      }
   }
   /*Method: isNumber
   * -------------------
   * Checks whether or not given argument is a number
   */


   bool isNumber(const string &word)
   {
      return word.find_first_not_of("0123456789") == string::npos;
   }


   public:
      bintree<string> dictionaryTree;

      spellcheck()
      {
         amountOfWords = 0;
         amountOfUnknownWords = 0;
      }
   /*Method: loadDictionaryFile
   * -------------------
   * Accepts a dictionary file as an argument and then processes each line
   * each line will be added to the binary tree
   * If the dictionary file is somehow corrupted, an exception is thrown.
   */

   void loadDictionaryFile(char *dictionaryFile)
   {
      ifstream fin;
      fin.exceptions(ifstream::goodbit);
      string line;
      try
      {
         fin.open(dictionaryFile);
         while (getline(fin, line))
         {
            dictionaryTree.insert(line);
         }
      }
      catch(ifstream::failure e)
      {
         cerr << "Spellcheck program failed to load due to to the following error: " << endl
         << "Unable to open directory file to read" << endl;
      }
   }

   /*Method: checkTextFile
   * -------------------
   * Accepts a text file as an argument and proccesses each line.
   * Each line will then be stored in a array of characters
   * This will then be passed as an argument by calling proccesLine
   * It will keep doing this until reaching the end of the file.
   */


   void checkTextFile(char *textFile)
   {
      ifstream fin;
      fin.exceptions(ifstream::goodbit);
      try
      {
         fin.open(textFile);
      while (!fin.eof())
      {
         char string[100];
         fin.getline(string, 100);
         processLine(string);
      }
      }
      catch(ifstream::failure e)
      {
         cerr << "Spellcheck program failed to load due to the following error: " << endl
         << "Unable to access" << textFile << endl;
      }
   }

   const int wordCount() const
   {
      return amountOfWords;
   }

   const int unknownWordsCount() const
   {
      return amountOfUnknownWords;
   }


};