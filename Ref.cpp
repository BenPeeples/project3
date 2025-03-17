// Ref class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;

// GetNextToken - general routine for getting next token from a string
// Parameters
//    str - string to search. search is destructive, i.e., token is removed.
//    delimiters - string, a list of characters to use a delimiters between tokens
// Returns: string token (removed from str)

string GetNextToken(string& str, const string& delimiters = " ") {
  // Skip delimiters at beginning                                          
  string::size_type startPos = str.find_first_not_of(delimiters, 0);
  // Find position of delimiter at end of token                                           
  string::size_type endPos = str.find_first_of(delimiters, startPos);

  // Found a token, remove it from string, and return it                       
  string next = str.substr(startPos, endPos - startPos);
  string rest = str.substr(endPos - startPos + 1, string::npos);
  str = rest;
  return(next);
}

// Ref member functions

Ref::Ref() {book = 0; chap = 0; verse = 0;}  	// Default constructor

Ref::Ref(const string s) { // Parse constructor - receives a line "34:5:7 text"
    string rtext = s; // make local copy of string to avoid modifying parameter
    // parse the reference - notice, currently there is no error checking!
    // Get book number
    string strbook = GetNextToken(rtext,":");
    book = atoi(strbook.c_str());
    // Get the chapter number
    string strchap = GetNextToken(rtext,":");
    chap = atoi(strchap.c_str());
    // Get the verse number
    string strverse = GetNextToken(rtext," ");
    verse = atoi(strverse.c_str());
    leftOverTextFromConstructor = rtext;
}

Ref::Ref(const int b, const int c, const int v) { 	// Construct Ref from three integers
	book = b;
	chap = c;
	verse = v;
}

// Accessors
int Ref::getBook() {return book;}	 // Access book number
int Ref::getChap() {return chap;}	 // Access chapter number
int Ref::getVerse() {return verse;} // Access verse number

string Ref::toString() {
        return to_string(getBook()) + ":" + to_string(getChap()) + ":" + to_string(getVerse());
}
// TO DO: implement comparison functions
// REQUIRED: == comparison
bool Ref::operator==(const Ref r) const {
    if (this->book == r.book) {
        if (this->chap == r.chap) {
            if(this->verse == r.verse){
                return true;
            }
        }
    }
    return false;
}

// OPTIONAL: define < and > comparisons
bool Ref::operator<(const Ref r) const {
    
    if (book < r.book) {
        return true;
    }
    else if (book == r.book) {
        if (chap < r.chap) {
            return true;
        }
        else if (chap == r.chap) {
            if (verse < r.verse) {
                return true;
            }
            else if (verse == r.verse) {
                return false;
            }
            else { return false; }
        }
        else { return false; }
    }
    else {
        return false;
    }
}
bool Ref::operator > (const Ref r) const {
    if (book > r.book) {
        return true;
    }
    else if (book == r.book) {
        if (chap > r.chap) {
            return true;
        }
        else if (chap == r.chap) {
            if (verse > r.verse) {
                return true;
            }
            else if (verse == verse) {
                return true;
            }
            else { return false; }
        }
        else { return false; }
    }
    else { return false; }
}
// TO DO: modify display function to show book name instead of book number
void Ref::display() { 	// Display Reference
    //Variables to hold the string version of b,v,c
    //Find the book and save it to the string
    string bookStr = getBookName();
        
    cout << bookStr << ":" << chap << ":" << verse;
}
string Ref::getBookName() {
    string output;

    map<int, string> books = { {1,"Genesis"}, {2,"Exodus"},{3,"Leviticus"},{4,"Numbers"},{5,"Deuteronomy"},{6,"Joshua"},{7,"Judges"},
    {8,"Ruth" },{9,"1 Samuel"},{10,"2 Samuel"},{11,"1 Kings"},{12,"2 Kings"}
        ,{13,"1 Chronicles"},{14,"2 Chronicles"},{15, "Ezra"},{16,"Nehemiah"},{17,"Esther"},{18,"Job"},{19,"Psalms"},{20,"Proverbs"},{21,"Ecclesiastes"}
        ,{22,"Song of Solomon"},{23,"Isaiah"},{24,"Jeremiah"},{25,"Song Lamentations"},{26,"Ezekiel"},{27,"Daniel"},{28,"Hosea"},{29,"Joel"},
        {30,"Amos"},{31,"Obadiah"},{32,"Jonah"},{33,"Micah"},{34,"Nahum"},{35,"Habakkuk"},{36,"Zephaniah"},{37,"Haggai"},{38,"Zechariah"},{39,"Malachi"},{40,"Matthew"}
        ,{41,"Mark"},{42,"Luke"},{43,"John"},{44,"Acts"},{45,"Romans"},{46,"1 Corinthians"},{47,"2 Corinthians"},{48,"Galatians"},{49,"Ephesians"}
        ,{50,"Philippians"},{51,"Colossians"},{52,"1 Thessalonians"},{53,"2 Thessalonians"},{54,"1 Timothy"},{55,"2 Timothy"},{56,"Titus"},{57,"Philemon"}
    ,{58,"Hebrews"},{59,"James"},{60,"1 Peter"},{61,"2 Peter"},{62,"1 John"},{63,"2 John"},{64,"3 John"},{65,"Jude"},{66,"Revelation"} };
    if (getBook() <= 66 && getBook() >= 1) {
        output = books.at(getBook());
        return output;
    }
    return to_string(getBook());
    
}
string Ref::getLeftOverTextFromConstructor() {
    return leftOverTextFromConstructor;
}
