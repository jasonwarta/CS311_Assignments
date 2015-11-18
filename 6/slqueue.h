// slqueue.h
// Jason Warta and Jason Bright
// 17 Nov 2015
//
// For CS 311 Fall 2015
// Header for class template SLQueue
// Used in Assignment 6

#ifndef SLQUEUE_H_INCLUDED
#define SLQUEUE_H_INCLUDED

#include "slist.h"

template<class SLQ>
class SLQueue{
public:
	typedef SLQ value_type;

/*
 * default ctor
 * pre: none
 * post: creates empty list of value_type
 * exception: no-throw guarantee
 */
SLQueue(){
	data_ = SList<value_type>();
}
	
/*
 * empty
 * pre: none
 * post: returns a bool based on whether the queue is empty
 * exception: no-throw guarantee
 */
bool empty() const {
	return (data_.empty());
}

/*
 * front
 * pre: none
 * post: returns a reference to the item at the front of the queue
 * exception neutral
 */
value_type & front() {
	return data_.front();
}  

/*
 * front - const version
 * pre: none
 * post: returns a reference to the item at the front of the queue
 * exception neutral
 */
const value_type & front() const {
	return data_.front();
}

/*
 * push
 * pre: must pass a object of the correct type
 * post: adds the item to the end of the queue
 * exception neutral
 */
void push(const value_type & temp) {
	data_.push_back(temp);
}

/*
 * pop
 * pre: none
 * post: removes the item at the front of the queue
 * exception neutral
 */
void pop() {
	data_.pop_front();
}

private: 
	SList<value_type> data_;  //Create the linked list for the Queue
};//end class SLQueue


#endif