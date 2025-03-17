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
		if (currentRef->second >= 0 && currentRef->second < 4272907) {
		Ref outputRef = currentRef->first;
		Verse output = Verse(outputRef);
		status = SUCCESS;
		return output;
	}
	}
	else {
		currentRef = index.begin();

	}
}

// REQUIRED: Return the next verse from the Bible file stream if the file is open.
// If the file is not open, open the file and return the first verse.
Verse Bible::nextVerse(LookupResult& status) {
	
	if (currentRef != index.end()) {
		currentRef++;
		Ref outputRef = currentRef->first;
		Verse output = Verse(outputRef);
		status = SUCCESS;
		return output;
	}
	else {
		currentRef = index.begin();
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
	cout << "Number of References added: " << numberOfAddedRefs << endl;
	cout << "Last Byte Offset: " << position << endl;
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
