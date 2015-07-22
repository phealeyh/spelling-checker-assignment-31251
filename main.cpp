#include <iostream>
#include <fstream>
#include "spellcheck.h"
using namespace std;

/* Functional prototypes */
void printSyntax();

   /*Method: printSyntax
   * -------------------
   * Prints the appropriate syntax that the user must use when using the program
   */
   void printSyntax()
   {
      cout << "ERROR - Incorrect number of arguments " << endl;
      cout << "Syntax : spellcheck dictionary file " << endl;
   }



   int main(int argc, char *argv[])
   {
      spellcheck dictionary;
      if(argc == 3)
      { //must accept a second argument
         dictionary.loadDictionaryFile(argv[1]);
         dictionary.checkTextFile(argv[2]);
         cout << "A total of " <<  dictionary.wordCount()
            << " words were found in this file" << endl;
         cout << dictionary.unknownWordsCount() << " had unknown spelling" << endl;
      }
      else
      {
         printSyntax();
      }
      return 0;
   }
