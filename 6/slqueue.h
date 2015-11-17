#ifndef SLQUEUE_H_INCLUDED
#define SLQUEUE_H_INCLUDED

#include <cstddef>
using std::size_t;
#include <algorithm>
using std::swap;


template<class Q>
class SLQueue{
public:
bool empty() {
	return true;  //just so it compiles
}

Q * front() {
	return nullptr; //just so it compiles
}  

Q * front() const {
	return nullptr; //just so it compiles

}

void push(Q temp) {
	
}

void pop() {
	
}

};//end class SLQueue


#endif