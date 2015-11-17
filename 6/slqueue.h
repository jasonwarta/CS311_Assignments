// slqueue.h
// Jason Warta and Jason Bright
// 17 Nov 2015
//
// For CS 311 Fall 2015
// Header for class template TSmArray
// Used in Assignment 6

#ifndef SLQUEUE_H_INCLUDED
#define SLQUEUE_H_INCLUDED

#include "slist.h"

template<class SLQ>
class SLQueue{
public:
	typedef SLQ value_type;
	typedef value_type * iterator;
	typedef const value_type * const_iterator;	
	
bool empty() const {
	return (data_.empty());  //just so it compiles
}

SLQ & front() {
	return data_.front();
}  

const SLQ & front() const {
	return data_.front();
}

void push(SLQ temp) {
	
}

void pop() {
	
}

private: 
	SList<SLQ> data_;  //Create the linked list for the Queue
};//end class SLQueue


#endif