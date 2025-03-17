#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Ref.h"
#include "Verse.h"
#include "Bible.h"
using namespace std;

int main() {
	Bible bible = Bible("web-complete");
	LookupResult status;
	Verse num1 = bible.lookup(Ref(1, 1, 1), status);
	num1.display();
	Verse num2 = bible.lookup(Ref(43, 3, 16), status);
	num2.display();
	Verse num3 = bible.lookup(Ref(66, 5, 12), status);
	num3.display();
	Verse num4 = bible.lookup(Ref(1, 2, 2), status);
	num4.display();
	num4 = bible.nextVerse(status);
	num4.display();
	num4 = bible.nextVerse(status);
	num4.display();
	num4 = bible.nextVerse(status);
	num4.display();
	Verse num5 = bible.lookup(Ref(1, 1, 1), status);
	num5.display();
	num5 = bible.nextVerse(status);
	num5.display();
	num5 = bible.nextVerse(status);
	num5.display();
	num5 = bible.nextVerse(status);
	num5.display();
	num5 = bible.nextVerse(status);
	num5.display();
	num5 = bible.nextVerse(status);
	num5.display();
	num5 = bible.nextVerse(status);
	num5.display();
	Verse num6 = bible.lookup(Ref(1, 1, 1), status);
	num6.display();
	num6 = bible.nextVerse(status);
	num6.display();
	num6 = bible.nextVerse(status);
	num6.display();
	num6 = bible.nextVerse(status);
	num6.display();
	num6 = bible.nextVerse(status);
	num6.display();
	num6 = bible.nextVerse(status);
	num6.display();
	num6 = bible.nextVerse(status);
	num6.display();
	num6 = bible.nextVerse(status);
	num6.display();
	num6 = bible.nextVerse(status);
	num6.display();
	num6 = bible.nextVerse(status);
	num6.display();
	num6 = bible.nextVerse(status);
}