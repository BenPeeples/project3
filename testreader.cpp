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

using namespace std;

int main() {
	Bible bible = Bible("/home/class/csc3004/Bibles/web-complete");
	LookupResult status;
	int refBook;
	int refChap;
	int refVerse;
	string bibleType;
	string message;
	Ref reference;
	Verse output;
	string titleOutput;
	string toSend;

	Fifo recfifo("Recieve Pipe");
	Fifo sendfifo("Send Pipe");

	recfifo.openread();

	while (true) {
		message = recfifo.recv();

		vector<string> tokens;
		stringstream check1(message);
		string intermediary;
		while (getline(check1, intermediary, ':')) {
			tokens.push_back(intermediary);
		}
		refBook = stoi(tokens[0]);

		refChap = stoi(tokens[1]);

		refVerse = stoi(tokens[2]);


		/*bibleType = *delimmitedString++;

		
		if (bibleType == "World English Bible") {
			bible = Bible("/home/class/csc3004/Bibles/web-complete");
		}
		if (bibleType == "King James Version") {
			bible = Bible("/home/class/csc3004/Bibles/kjv-complete");
		}
		if (bibleType == "Darby Translation") {
			bible = Bible("/home/class/csc3004/Bibles/dby-complete");
		}
		if (bibleType == "Young's Literal Translation") {
			bible = Bible("/home/class/csc3004/Bibles/ylt-complete");
		}
		if (bibleType == "Webster Translation") {
			bible = Bible("/home/class/csc3004/Bibles/webster-complete");
		}*/

		reference = Ref(refBook, refChap, refVerse);

		output = bible.lookup(reference, status);
		if (status == SUCCESS) {
			titleOutput = reference.getBookName();
			titleOutput.append(" " + to_string(reference.getChap()) + " "); titleOutput.append(to_string(reference.getVerse()));
			cout << titleOutput + " " + output.getVerse() << endl;
			sendfifo.openwrite();
			toSend = titleOutput + " ";
			toSend.append(output.getVerse());
			sendfifo.send(toSend);
			sendfifo.fifoclose();
		}
		else {
			sendfifo.openwrite();
			sendfifo.send(bible.error(status));
			sendfifo.fifoclose();
		}
	}
}