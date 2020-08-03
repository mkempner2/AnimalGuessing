// myUtils-Mini.h
// Doug DeGroot
// mini version
//
// changelog:
//	6/1/20 - pruned down to essentials for class work
// notes:
//	openForWriting - modify to check for pre-existence and to
//		add a version number so we don't overwrite an existing file
//		maybe let filename default to "", and if so, use a predefined
//		output file name [nope, don't do it!]
//
#ifndef MYUTILS_H
#define MYUTILS_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// ===== define a few macros for use in output
#define sp  ' '
#define sp2 '  '
#define sp3 '   '
#define sep ", "


// ===== show and other output routines ===== //

void show(string msg) {
   cout << msg << endl;
} //show

void show(string msg1,string msg2) {
   cout << msg1 << ": " << msg2 << endl;
} //show

void show(string msg,int num) {
   cout << msg << ": " << num << endl;
} //show

void show(string msg,int num1,int num2) {
   cout << msg << ": " << num1 << sp << num2 << endl;
} //show

void line() {
   cout << "---------------------------------------" << endl;
} //line


// ===== misc system routines ========================-- //

void pause() {
	system("pause");
} //pause


bool askYN(string question="") {
  if (question != "")
	  cout << question << ": ";
  char foo;
  cin >> foo;
  cin.ignore();
  return (toupper(foo) == 'Y');
} //askYN


// ckError - compare to C++'s assert
// if condition doesn't hold, report the error, pause, and then continue
void ckError(bool condition,string errorString) {
   if (condition) {
      cout << errorString << endl;
      system("pause");
   }
} //ckError


// ensure - compare to C++'s assert
// if condition doesn't hold, report the error, pause, and then continue
void ensure(bool condition,string errorString) {
   if (!condition) {
      show(errorString);
      system("pause");
   }
} //ensure



// ===== IO and File Routines ============================= //

bool openForReading(ifstream &infile,string fileName) {
	infile.open(fileName);
	if (infile.good()) //then the file opened just fine
		return true;
	else {
		perror("Can't open the specified input file.");
		cout << "The file name used was: " << fileName << endl;
		cout << "Enter another file name to use (or quit): ";
		getline(cin,fileName);
		cout << "--- the new file name is: " << fileName << endl;
		if (fileName != "quit") // maybe check for QUIT, too
			return openForReading(infile,fileName); //note the use of recursion here
		else return false;
	}
} //openFor Reading


bool openForWriting(ofstream &outfile,string fileName) {
	//bad code -- too many internal returns; fix this
	outfile.open(fileName);
	if (outfile.good()) //then the file opened just fine
		return true;
	else {
		perror("Can't open the specified output file");
		cout << "The file name used was: " << fileName << endl;
		cout << "Enter another file name to use (or quit): ";
		getline(cin,fileName);
		cout << "--- The new file name is: " << fileName << endl;
		if (fileName != "quit") {
			openForWriting(outfile,fileName); //note the use of recursion here
			return true;
		}
		else return false; //or should I actually EXIT here?
	}
} //openForWriting


// showFileStatus
void showFileStatus(ifstream &theStream) {
    show("File Status:");
    cout << "EOF bit:" << theStream.eof() << endl;
    cout << "FAIL bit:" << theStream.fail() << endl;
    cout << "BAD bit:" << theStream.bad() << endl;
    cout << "GOOD bit:" << theStream.good() << endl;
    theStream.clear();
} //showFileStatus



// ===== Console Utilities ============================= //

void greenScreen() { //set the font color to green
	system("color A"); //A=green, B=light blue, C=red
} //greenScreen

void blueScreen() { //set the font color to green
	system("color B"); //A=green, B=light blue, C=red
} //blueScreen

void redScreen() { //set the font color to green
	system("color C"); //A=green, B=light blue, C=red
} //blueScreen


// ===== END =========================================== //

#endif //MYUTILS_H




