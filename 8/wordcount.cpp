// wordcount.cpp
// Jason Warta and Jason Bright
// 10 Dec 2015
//
// For CS 311 Fall 2015
// Counts the number of times different words appear in a file
// Used in Assignment 8

#include <map>
using std::map;
#include <fstream>
using std::ifstream;
using std::string;
using std::size_t;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
	
/*
Word count takes a file name as input, and outputs a delimited list of the words found within the file and the number of times it occurs.
If an error is detected during the file read, the count will be aborted and the program will exit.  
This program is designed for plain text files.  While it will "do it's best" for other files the results are not guaranteed.
If an invalid file name is presented, it will quit; 
Requirement:  Valid filename be presented
Fail to meet requirements:  Program will terminate.
*/
int main(){
//Get the file name.  
	string fname;  //file name
	cout << "Enter a filename: ";
	getline(cin,fname);
//Open the file
	ifstream ifs(fname);
	if(ifs.bad()) {
		cout << "Error opening file" << endl;
		return 1;
	}
	string input;
	map<string, size_t> count;

	if(ifs.is_open() && ifs.good()){
		while(ifs.good()){
			try {  //Only known time this throws is if the user has input a directory name on windows
				ifs >> input;
			}
			catch(...){  //This is a controlled exit, not a crash.
				cout << "Error in file read occurred, exiting" << endl;
				cout << "Did you try to open a folder?" << endl;
				ifs.close();
				return 1;
			}				
			if(count.find(input) == count.end()) count[input] = 1; //Word not found in the mapp, add to map
			else count[input]++; //Word found, increment count for that word.

//			if(ifs.eof()) break;
		}
//Print the listing
		for(auto i = count.begin(); i != count.end(); i++){
			cout << i->first << " " << i->second << endl;
		}
		ifs.close();
	}
	else {
		cout << "Could not open file." << endl;
	}
	return 0;
}