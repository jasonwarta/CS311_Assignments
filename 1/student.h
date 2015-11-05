/*
 * student.h
 * 
 * Jason Warta
 * 2015.09.15
 * 
 * header for Student class
 */

#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <string>
#include <iostream>
#include <sstream>

using std::string;
using std::ostream;
using std::stringstream;

class Student{

public:
	/* 
	 * Every instance of this class will have:
	 * a string, holding the name value. Unless set by the client, this will be an emtpy string
	 * an int, holding the ID value. Unless set by the client, this will be 0.
	 * 
	 * This class makes use of the following silently written functions:
	 * copy constructor
	 * copy assignment operator
	 */


	/* 
	 * Student constructor
	 * pre: None
	 * post: name is set to nothing, id is set to 0
	 */
	Student():name_(""),id_(0){};

	/*
	 * Student constructor
	 * pre:	must pass a valid string and a valid int between 0 and 99999999, inclusively
	 *      invalid input sets string to empty, and id to 0
	 * post: sets name to passed string and id to passed int
	 */
	Student(string name, int id);

	/*
	 * Student destructor
	 * pre: None
	 * post: sets name to an emtpy string and id to 0
	 */
	~Student();

	/*
	 * getName
	 * pre: none
	 * post: returns the name
	 */
	string getName() const;

	/*
	 * getID
	 * pre: none
	 * post: returns the id
	 */
	int getID() const;

	/*
	 * setName
	 * pre: must pass valid string
	 * 			if string is invalid, name will be set to an empty string
	 * post: name is updated to the passed value
	 */
	void setName(string name);

	/*
	 * setID
	 * pre: must pass valid int within the range 0-99999999
	 * 			invalid input is set to 0
	 * post: sets ID to passed value
	 */
	void setID(int id);

	/*
	 * toString
	 * pre: none
	 * post: returns a formated string version of the Student object in the following format
	 * 			 "john doe (12345678)"
	 */
	string toString() const;

	/*
	 * operator==
	 * pre: must compare two valid Student objects
	 * post: compares the Student objects and returns true if they are identical
	 */
	bool operator==(const Student &other) const;

	/*
	 * operator!=
	 * pre: must compare two valid Student objects
	 * post: compares the Student objects and returns true if they are not identical
	 */
	bool operator!=(const Student &other) const;

	/*
	 * operator<<
	 * pre: must pass valid ostream and Student objects
	 *      invalid input not gaurenteed to produce expected results
	 * post: returns an ostream
	 */
	friend ostream& operator<<(ostream &os, const Student &rhs);

private:
	string name_;
	int id_;
};

#endif