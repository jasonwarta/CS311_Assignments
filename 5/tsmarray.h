// tsmarray.h
// Jason Warta and Jason Bright
// 5 Nov 2015
//
// For CS 311 Fall 2015
// Header for class template TSmArray
// Used in Assignment 5

#ifndef TSMARRAY_H_INCLUDED
#define TSMARRAY_H_INCLUDED

#include <iostream>     // for std::cout, std::endl, std::cin
using std::cout;
using std::endl;
#include <cstddef>
using std::size_t;
#include <algorithm>
using std::copy;


template<class TSA>
class TSmArray{

public:

	/*
	 * typedefs
	 * declare size_type, value_type, iterator, const_iterator
	 */
	typedef std::size_t size_type;
	typedef TSA value_type;
	typedef value_type * iterator;
	typedef const value_type * const_iterator;

	//default ctor
	TSmArray():size_(0),capacity_(0){
		data_ = new value_type[size_];
	}

	/*
	 * TSmArray(const TSmArray &) - copy ctor
	 * pre: must pass a valid TSmArray object
	 * post: replaces current object with passed object
	 */
	TSmArray(const TSmArray & rhs)
		:size_(rhs.size_),
		 capacity_(rhs.capacity_),
		 data_(new value_type[capacity_]) {
		
		try{
			if(data_ != rhs.data_ && data_ != nullptr){
				// data_ = new value_type[capacity_];
				copy(rhs.begin(),rhs.end(),begin());
			}
			// copy(rhs.begin(),rhs.end(),begin());
		}
		catch(...){
			//cleanup if an exception is thrown. jb
			if(data_ != nullptr){
				delete[] data_;
			}
			throw;
		}
			
	}

	/*
	 * operator=(TSmArray &) - copy assignment operator
	 * pre: must pass a valid TSmArray object
	 * post: replaces current object with passed object, and returns it by reference
	 */
	TSmArray & operator=(TSmArray rhs) {
		swap(rhs);
		return *this;
	}

	/*
	 * ~TSmArray - destructor
	 * pre: none
	 * post: array is deleted, and size is set to 0
	 */
	~TSmArray(){
		if(data_ != nullptr){
			delete[] data_;
		}
	}

	/*
	 * TSmArray(size_type)
	 */
	explicit TSmArray(size_type size):size_(size){
		data_ = new value_type[size_];
		capacity_ = size_; //jb - constructor wasn't setting capacity.  Took ~hour to find!
	}

	/*
	 * Bracket Operator
	 * Returns value at given iterator point
	 */
	value_type & operator[](size_type idx){
		if(idx >= 0 && idx < size_) return data_[idx];
		return data_[0]; //Removing warning.
	}

	/*
	 * Const Bracket Operator
	 * Returns value at given iterator point
	 */
	value_type & operator[](size_type idx) const{
		if(idx >= 0 && idx < size_) return data_[idx];
		return data_[0]; //Removing warning.
	}

	/*
	 * 
	 */
	size_type size() const{
		return size_;
	}

	/*
	 * 
	 */
	bool empty() const{
		return !size_;
	}

	/*
	 * 
	 */
	void resize(size_type n_size){
		if(n_size <= capacity_) size_ = n_size;
		// if(size <= size_) size_ = size;
		// else if (size_ < capacity_) size_ = size; //JB bug fix - ++size -> =
		else{			
			value_type * temp = nullptr;
			try {
				capacity_ = 2 * size_;
				temp = new value_type[capacity_];
			}
			catch(...){
				//cleanup if an exception is thrown. jb
				cout << "resize exception thrown" << endl;
				if(temp != nullptr){
					delete[] temp;
				}
				throw;
			}
			try {
				copy(data_,data_ + size_,temp);  //jb - simplified this.
				std::swap(temp,data_);
				delete[] temp;
			}
			catch(...) {
				delete[] temp; // make sure the memory is deleted.
				throw; //kick the error on
			}	
			size_ = n_size;
		}
	}

	/*
	 * 
	 */
	iterator insert(iterator itr, const value_type & item){
		size_type idx = itr - data_;
		resize(size_+1);
		data_[size_-1] = item;
		std::rotate(begin()+idx,end()-1,end());

		return data_ + idx;
	}

	/*
	 * 
	 */
	iterator remove(iterator itr){
		std::rotate(itr,itr+1,end());
		resize(size_-1);
		return itr;
	}

	/*
	 * 
	 */
	iterator begin(){
		return data_;
	}

	/*
	 * 
	 */
	const_iterator begin() const{
		return data_;
	}

	/*
	 * 
	 */
	iterator end(){
		return data_ + size_;
	}

	/*
	 * 
	 */
	const_iterator end() const{
		return data_ + size_;
	}

	/*
	 * 
	 */
	void swap(TSmArray & rhs){
		std::swap(data_,rhs.data_);
		std::swap(size_,rhs.size_);
		std::swap(capacity_,rhs.capacity_);
	}


private:
	size_type size_;
	size_type capacity_;
	value_type * data_;


};	//end of clas TSmArray

#endif