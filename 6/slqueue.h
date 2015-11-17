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
	// typedef value_type * iterator;
	// typedef const value_type * const_iterator;	

SLQueue(){
	data_ = SList<value_type>();
}
	
bool empty() const {
	return (data_.empty());  //just so it compiles
}

value_type & front() {
	return data_.front();
}  

const value_type & front() const {
	return data_.front();
}

void push(value_type temp) {
	data_.push_back(temp);
}

void pop() {
	data_.pop_front();
}

private: 
	SList<value_type> data_;  //Create the linked list for the Queue
};//end class SLQueue


#endif