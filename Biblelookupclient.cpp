/* sslookupclient.cpp
 * Shakespeare full-text search client:
 * receives an Ajax request from web client
 * extracts search string, and sends request to sslookupserver
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Ref.h"
#include "Verse.h"
#include "Bible.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "fifo.h"
#include "vector"

 // Stuff for Ajax
#include "/home/class/csc3004/cgicc/Cgicc.h"
#include "/home/class/csc3004/cgicc/HTTPHTMLHeader.h"
#include "/home/class/csc3004/cgicc/HTMLClasses.h"
using namespace cgicc;

//Stuff for pipes                                                               





int main() {
	cout << "Content-Type: text/plain\n\n" << endl;
	Cgicc cgi;
	//Take the input from the web page.

	//Open the pipes

	//  BOOK:CHAPTER:VERSE:VERSNUMBERS:TRANSLATION
	//cout << "before fifo" << endl;
	Fifo recfifo("reply");
	Fifo sendfifo("request");

	recfifo.openread();
	sendfifo.openwrite();

	//cout << "After fifo" << endl;
	//while (true) {
		//cout << "Inside loop" << endl;
		form_iterator book = cgi.getElement("book");
		form_iterator chapter = cgi.getElement("chapter");
		form_iterator verse = cgi.getElement("verse");
		form_iterator nv = cgi.getElement("num_verse");
		form_iterator type = cgi.getElement("Bible_type");

		//Error checking: check for input values existing.
		//Ints to store the values input to compare.
		int amountVerses = 1;
		int chapterNumber = 0;
		int bookNumber = 0;
		int verseNumber = 0;

		//Booleans to keep track of valid input
		bool validChap = false;
		bool validBook = false;
		bool validVerse = false;

		if (nv != cgi.getElements().end()) {
		//	cout << "verse numbver" << endl;
			amountVerses = nv->getIntegerValue();
		}
		else {
			amountVerses = 1;
		}



		if (book != cgi.getElements().end()) {
			//cout << "Inside book" << endl;
			bookNumber = book->getIntegerValue();
			if (bookNumber > 66) {
				cout << "<p> Invalid Book Input: Book Number ( " << bookNumber << " ) is too high. </p>" << endl;
			}
			else if (bookNumber < 1) {
				cout << "<p> Invalid Book Input: Book Number  ( " << bookNumber << " ) is not a positive number. </p>" << endl;
			}
			else {
				validBook = true;
			}
		}
		if(bookNumber == 0 || book == cgi.getElements().end()){
			validBook = false;
			cout << "<p> No book number input. Please input a book number between 1 and 66.</p>" << endl;
		}




		if (chapter != cgi.getElements().end()) {
			//cout << "Inside chapter" << endl;
			chapterNumber = chapter->getIntegerValue();
			if (chapterNumber > 150) {
				cout << "<p>The chapter number (" << chapterNumber << ") is too high.</p>" << endl;
			}
			else if (chapterNumber <= 0) {
				cout << "<p>The chapter must be a positive number.</p>" << endl;
			}
			else {
				validChap = true;
			}
		}
		if(chapterNumber == 0 || chapter == cgi.getElements().end()){
			validChap = false;
			cout << "<p> No chapter number input. Please input a chapter number between 1 and 150.</p>" << endl;
		}



		if (verse != cgi.getElements().end()) {
			//cout << "Inside verse" << endl;
			verseNumber = verse->getIntegerValue();
			if (verseNumber < 0) {
				cout << "<p> Invalid Verse Input: Verse Number ( " << verseNumber << " ) is not a positive number. </p>" << endl;
			}
			else if (verseNumber > 176) {
				cout << "<p> Invalid Verse Input: Verse Number ( " << verseNumber << " ) is too high. </p>" << endl;
			}
			else {
				validVerse = true;
			}
		}
		if(verseNumber == 0 || verse == cgi.getElements().end()){
			validVerse = false;
			cout << "<p> No verse number input. Please input a verse number .</p>" << endl;
		}




		//Do this when there is an input value for all the vlaues.
		if (validVerse && validBook && validChap) {
			string bibleType;
			if (type != cgi.getElements().end()) {
				//cout << "Inside type" << endl;
				bibleType = **type;
			}
			else {
				bibleType = "World English Bible";
			}
			//Format the reference to send.
			//cout << "Before sending" << endl;
			
			//Take the output and display it on the webpage.


			string results = " IT SHOULD PRINT SOMETHING HERE WHEN THE THING GETS DONE";
			string referenceToSend = to_string(bookNumber) + ":" + to_string(chapterNumber) + ":" +
			to_string(verseNumber) + ":" + to_string(amountVerses) + ":" + bibleType;
			sendfifo.send(referenceToSend);

			for (int i = 0; i < amountVerses; i++) {
				results = recfifo.recv();

				cout << "<p>" << results << "</p>" << endl;
			}
			
		}
		recfifo.fifoclose();
		sendfifo.fifoclose();
	}
//}