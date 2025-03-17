// Class Ref
// Computer Science, MVNU
//
// Ref is a class for representing a Bible reference consisting of
//    * integer book   - the book from 1 (Genesis) to 66 (Revalation)
//    * integer chap   - the chapter number >1
//    * integer verse  - he verse numner >1
//

#ifndef Ref_H
#define Ref_H
#include <string> 
#include <stdlib.h>
using namespace std;

// GetNextToken returns a token from str, which contains all characters
// up to the first character from delimiters
string GetNextToken(string& str, const string& delimiters);

class Ref {
private:
   short book, chap, verse;	// Reference information
   string leftOverTextFromConstructor; // Text that will become the verse
public:
   Ref();  	// Default constructor
   Ref(string s); 	// Parse constructor - example parameter "43:3:16"
   Ref(const int,const int,const int); 	// Construct from three integers;
   // Accessors
   int getBook();	// Access book number
   int getChap();	// Access chapter number
   int getVerse();	// Access verse number
   string getLeftOverTextFromConstructor(); // Access for the text
   string getBookName(); // Get the book as a string
   // REQUIRED Comparison: determine if two references are equal
   bool operator==(const Ref) const;
   // OPTIONAL: < and > comparisons for Ref objects might also be useful
   bool operator < (const Ref) const;
   bool operator > (const Ref) const;
   
   // REQUIRED: Display the reference on cout, example output: John 3:16
   // Your version of display should show the book name
   // corresponding to the stored book number.
   void display();
   
   //Convert the Reference to a string.
   string toString();
};

#endif //Ref_H
