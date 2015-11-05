/*
 * student.cpp
 * 
 * Jason Warta
 * 2015.09.15
 * 
 * member and friend functions for Student class
 */

#include "student.h"
#include <iomanip>

Student::Student(string name, int id){
	//using set functions because they have built-in error checking and handling
	setName(name);
	setID(id);
}

Student::~Student(){
	name_ = "";
	id_ = 0;
}

string Student::getName() const{
	return name_;
}

int Student::getID() const{
	return id_;
}

void Student::setName(string name){
	if(&name != NULL){ //ensure that string actually exists
		name_ = name;
	} else {
		name_ = "";
	}
}

void Student::setID(int id){
	//check that id is valid and within range
	if(id >= 0 && id <= 99999999 && &id != NULL){
		id_ = id;
	} else {
		id_ = 0;
	}
}

string Student::toString() const{
	stringstream ss;
	ss << (*this);
	return ss.str();
}

bool Student::operator==(const Student &other) const{
	//check that the Student object is valid
	if(&other != NULL){
		return id_ == other.id_ && name_ == other.name_;
	} else {
		return false;
	}
}

bool Student::operator!=(const Student &other) const{
	//check that the Student object is valid
	if(&other != NULL){
		return !( *this == other );
	} else {
		return false;
	}
}

/*
 * operator<<
 * pre: must pass valid ostream and Student objects
 *      invalid input not gaurenteed to produce expected results
 * post: returns an ostream
 */
ostream& operator<<(ostream &os, const Student &rhs){
	//check that the ostream and Student objects are valid
	if(&rhs != NULL && &os != NULL){
		os << rhs.getName() << " (" << std::setfill('0') << std::setw(8) << rhs.getID() << ")";
	}
	return os;
}