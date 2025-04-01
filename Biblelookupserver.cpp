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
	int verseNum;
	string bibleType;
	string message;
	Ref reference;
	Verse output;
	string titleOutput;
	string toSend;
	string previousMessage;

	Fifo recfifo("request");
	Fifo sendfifo("reply");

	
	sendfifo.openwrite();
	recfifo.openread();
	while (true) {
		
		message = recfifo.recv();
		cout << message << endl;

		if (message != previousMessage) {
			vector<string> tokens;
			stringstream check1(message);
			string intermediary;
			while (getline(check1, intermediary, ':')) {
				tokens.push_back(intermediary);
			}
			refBook = stoi(tokens[0]);

			refChap = stoi(tokens[1]);

			refVerse = stoi(tokens[2]);
			
			verseNum = stoi(tokens[3]);
		
			bibleType = tokens[4];
			
			



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
			}

			reference = Ref(refBook, refChap, refVerse);
			cout << refBook << endl;
			output = bible.lookup(reference, status);
			
			
			if (verseNum == 1) {
				if (status == SUCCESS) {
					titleOutput = reference.getBookName();
					titleOutput.append(" " + to_string(reference.getChap()) + " ");
					titleOutput.append(to_string(reference.getVerse()));
					cout << titleOutput + " " + output.getVerse() << endl;

					toSend = titleOutput + " ";
					toSend.append(output.getVerse());
					sendfifo.send(toSend);


				}
				else {
					sendfifo.send(bible.error(status));
				}
			}
			else {
				map<Ref, int>::iterator it;
				
				for (int i = 0; i < verseNum; i++) {
					it = bible.getCurrentRef();
					Ref curRef = it->first;
					titleOutput = curRef.getBookName();
					titleOutput.append(" " + to_string(curRef.getChap()) + " ");
					titleOutput.append(to_string(curRef.getVerse()));
					cout << titleOutput + " " + output.getVerse() << endl;

					toSend = titleOutput + " ";
					toSend.append(output.getVerse());
					sendfifo.send(toSend);

					output = bible.nextVerse(status);
				}
			}
			previousMessage = message;
		}
	}
}