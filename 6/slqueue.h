#ifndef SLQUEUE_H_INCLUDED
#define SLQUEUE_H_INCLUDED

#include <cstddef>
using std::size_t;
#include <algorithm>
using std::swap;


template<class SLQ>
class SLQueue{
public:
	typedef SLQ value_type;
	typedef value_type * iterator;
	typedef const value_type * const_iterator;	
bool empty() const {
	return true;  //just so it compiles
}

SLQ & front() {
	SLQ temp; //just so it compiles
	return temp;
}  

SLQ & front() const {
	SLQ temp;
	return temp; //just so it compiles

}

void push(SLQ temp) {
	
}

void pop() {
	
}

};//end class SLQueue


#endif