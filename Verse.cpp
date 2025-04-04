// Verse class function definitions
// Computer Science, MVNU

#include "Verse.h"
#include <iostream>
using namespace std;

Verse::Verse() {  	// Default constructor
    verseText = "Uninitialized Verse!";
    verseRef = Ref();
} 

// REQUIRED: Parse constructor - pass verse string from file
Verse::Verse(const string s) {
	// use Ref constructor to create verseRef
	// store the remainder of the string in verseText
    verseRef = Ref(s);
    
    verseText = verseRef.getLeftOverTextFromConstructor();

}

Verse::Verse(const Ref ref) {
    verseRef = ref;
    verseText = verseRef.getLeftOverTextFromConstructor();
}

// REQUIRED: Accessors
string Verse::getVerse() {
    return verseText;
}

Ref Verse::getRef() {
    return verseRef;
}

// display reference and verse
void Verse::display() {
    getRef().display();
    cout << " " << verseText;
 }
