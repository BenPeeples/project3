// Bible class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include "Verse.h"
#include "Bible.h" 
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

Bible::Bible() { // Default constructor
	infile = "/home/class/csc3004/Bibles/web-complete";
	instream = ifstream(infile);
	isOpen = true;
	buildTextIndex();
	currentRef = index.begin();
}

// Constructor – pass bible filename
Bible::Bible(const string s) { infile = s; instream = ifstream(infile); isOpen = true; buildTextIndex(); currentRef = index.begin();
}



// REQUIRED: lookup finds a given verse in this Bible
Verse Bible::lookup(Ref ref, LookupResult& status) { 
	

	currentRef = index.find(ref);
	if (currentRef != index.end()) {
		string line = "TEST";
		//Open the file at specific position
		
		Ref outputRef = currentRef->first;
		Verse output = Verse(outputRef);
		status = SUCCESS;
		return output;
		
	}
	else {
		currentRef = index.begin();
		map<int, int> chapterPerBook = { {1,50},{2,40},{3,27},{4,36},{5,34},{6,24},{7,21},{8,4},{9,31},{10,24},{11,22},{12,25},{13,29},{14,36},{15,10},{16,13},{17,10},{18,42},{19,150},{20,31},{21,12},{22,8},{23,66},{24,52},{25,5},{26,48},{27,12},{28,14},{29,3},{30,9},{31,1},{32,4},{33,7},{34,3},{35,3},{36,3},{37,2},{38,14},{39,4},{40,28},{41,16},{42,24},{43,21},{44,28},{45,16},{46,16},{47,13},{48,6},{49,6},{50,4},{51,4},{52,5},{53,3},{54,6},{55,4},{56,3},{57,1},{58,13},{59,5},{60,5},{61,3},{62,5},{63,1},{64,1},{65,1},{66,22} };
		map<int, int>::iterator chapterCount = chapterPerBook.find(ref.getChap());
		
		if (ref.getBook() >66 || ref.getBook()< 1) {
			status = NO_BOOK;
		}
		else if (chapterCount->second < ref.getChap() && ref.getChap() <1) {
			status = NO_CHAPTER;
		}
		else {
			status = NO_VERSE;
		}
	}
}

// REQUIRED: Return the next verse from the Bible file stream if the file is open.
// If the file is not open, open the file and return the first verse.
Verse Bible::nextVerse(LookupResult& status) {
	Ref toCompare = Ref(66,22,21);
	if (currentRef->first == toCompare) {
		currentRef = index.begin();
		Ref outputRef = currentRef->first;
		Verse output = Verse(outputRef);
		status = SUCCESS;
		return output;
	}
	else {
		currentRef++;
		Ref outputRef = currentRef->first;
		Verse output = Verse(outputRef);
		status = SUCCESS;
		return output;
	}
}

// REQUIRED: Return an error message string to describe status
string Bible::error(LookupResult status) {
	string output;
	Ref ref = currentRef->first;
	
	if (status == NO_BOOK) {
		output = "Error: no such book " + to_string(ref.getBook());
	}
	if (status == NO_CHAPTER) {
		output = "Error: no such chapter " + to_string(ref.getChap()) + " in " + ref.getBookName();
	}
	if (status == NO_VERSE) {
		output = "Error: no such verse " + to_string(ref.getVerse()) + " in " + ref.getBookName() + " " + to_string(ref.getChap());
	}
	if (status == OTHER) {
		output = "Other Error";
	}
	if (status == SUCCESS) {
		output = "SUCCESS";
	}
	return output;
}

void Bible::display() {
	cout << "Bible file: " << infile << endl;
}

bool Bible::checkIfOpen() {
	if (instream.is_open()) {
		return true;
	}
	return false;
}
map<Ref, int>::iterator Bible::getCurrentRef() {
	return currentRef;
}

void Bible::openFile() {instream.open(infile, std::ifstream::in);}

void Bible::closeFile() {instream.close();}



void Bible::buildTextIndex() {
	int position;
	int numberOfAddedRefs = 0;
	string line;
	if (isOpen) {
		while (getline(instream, line)) {
			Ref tempRef = Ref(line);
			position = (int)instream.tellg();
			index.insert(make_pair(tempRef, position));
			numberOfAddedRefs++;
		}
	}
	//cout << "Number of References added: " << numberOfAddedRefs << endl;
	//cout << "Last Byte Offset: " << position << endl;
}
	
// OPTIONAL access functions
// OPTIONAL: Return the reference after the given ref
Ref Bible::next(const Ref ref, LookupResult& status) {
	map<Ref, int>::iterator it;
	it = index.find(ref);
	Ref blankRef;
	if (it != index.end()) {
		it++;
		return it->first;
	}
	else { return blankRef; }
}

//// OPTIONAL: Return the reference before the given ref
Ref Bible::prev(const Ref ref, LookupResult& status) {
	map<Ref, int>::iterator it;
	it = index.find(ref);
	Ref blankRef;
	if (it != index.end()) {
		it--;
		return it->first;
	}
	else { return blankRef; }
}
