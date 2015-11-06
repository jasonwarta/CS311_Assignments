// tsmarray.h
// Jason Warta and Jason Bright
// 5 Nov 2015
//
// For CS 311 Fall 2015
// Header for class template TSmArray
// Used in Assignment 5

#ifndef TSMARRAY_H_INCLUDED
#define TSMARRAY_H_INCLUDED

#include <cstddef>
using std::size_t;
#include <algorithm>
using std::copy;


// Template class TSmArry
// Impliments a "smart array" somewhat similar to std::Vector
// Requirements: type must be assignable/swappable.
// Class invariants:
// Data_: pointer to data array
// Size_: size of array
// Capacity_: capacity of array. Internal use only.

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
	//Creates a TSMArray of the desired type of size 0.
	//Pre:  None
	//Post: TSMArray of requested type, size 0.
	//Error:  Exception neutral, safe(no data to alter anyways)
	
	TSmArray():size_(0),capacity_(0){
		data_ = new value_type[size_];
	}

	/*
	 * TSmArray(const TSmArray &) - copy ctor
	 * pre: must pass a valid TSmArray object
	 * post: replaces current object with passed object
	 * Error: Exception neutral, safe
	 */
	TSmArray(const TSmArray & rhs)
		:size_(rhs.size_),
		 capacity_(rhs.capacity_),
		 data_(new value_type[capacity_]) {
		
		try{
			if(data_ != rhs.data_ && data_ != nullptr){
				copy(rhs.begin(),rhs.end(),begin());
			}
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
	 * exception: neutral, safe.
	 */
	TSmArray & operator=(TSmArray rhs) {
		swap(rhs);
		return *this;
	}

	/*
	 * ~TSmArray - destructor
	 * pre: none
	 * post: array is deleted, and size is set to 0
	 * exception:  No throw guarantee.
	 */
	~TSmArray(){
		if(data_ != nullptr){
			delete[] data_;
		}
	}

	/*
	 * TSmArray(size_type)
	 * creates a TSMArray object of give size
	 * pre: value passed should be positive if converting from signed to unsigned number.
	 * Otherwise created array is likely to be quite large('undefined behavior').
	 * post: TSmArray object of given size.
	 * exception: neutral, safe
	 */
	explicit TSmArray(size_type size):size_(size){
		data_ = new value_type[size_];
		capacity_ = size_; //jb - constructor wasn't setting capacity.  Took ~hour to find!
	}

	/*
	 * Bracket Operator
	 * Returns value at given iterator point
	 * UNLESS value would go past range of data value, then returns first element
	 * Pre: Value needs to be less than size_
	 * Post: value at given position of index.
	 * Exception: neutral, safe
	 */
	value_type & operator[](size_type idx){
		if(idx >= 0 && idx < size_) return data_[idx];
		return data_[0]; //Removing warning.
	}

	/*
	 * Const Bracket Operator
	 * Returns value at given iterator point
	 * UNLESS value would go past range of data value, then returns first element
	 * Pre: Value needs to be less than size_
	 * Post: value at given position of index.
	 * Exception: neutral, safe
	 */
	value_type & operator[](size_type idx) const{
		if(idx >= 0 && idx < size_) return data_[idx];
		return data_[0]; //Removing warning.
	}

	/*
	 * Accessor: size
	 * Pre: None
	 * Post: returns the size of the data array
	 * Exception: No Throw guarantee
	 */
	size_type size() const{
		return size_;
	}

	/*
	 * Accessor: Array empty test
	 * Pre: None
	 * Post: returns 1 if the size of the data array is zero.
	 * Exception: No Throw guarantee
	 */
	bool empty() const{
		return !size_;
	}

	/*
	 * Resize function
	 * Pre: A new size for the array; Not so large as to create a memory error
	 * Post: Array changed to the new size
	 * Exception: Neutral, safe.  
	 */
	void resize(size_type n_size){
		if(n_size <= capacity_) size_ = n_size;
		// if(size <= size_) size_ = size;
		// else if (size_ < capacity_) size_ = size; 
		//JB bug fix - ++size -> =
		else{			
			capacity_ = 2 * size_;
  		value_type * temp = new value_type[capacity_];
			try {
				copy(data_,data_ + size_,temp);  //jb - simplified this.
				std::swap(temp,data_);
				delete[] temp;
			}
			catch(...) {
				delete[] temp; // make sure the memory is deleted.
				throw; //kick the error on
			}
		}
		size_ = n_size;
	}


	/*
	 * Insert operation
	 * Pre: Valid position and value/item to insert
	 * Post: array of increased size
	 * Exception: Neutral, safe.
	 */
	iterator insert(iterator itr, const value_type & item){
		size_type idx = itr - data_;
		resize(size_+1);
		data_[size_-1] = item;
		std::rotate(begin()+idx,end()-1,end());

		return data_ + idx;
	}

	/*
	 * Remove operation
	 * Pre: Valid position and value/item to remove
	 * Post: array of reduced size
	 * Exception: No throw guarantee
	 */
	iterator remove(iterator itr){
		std::rotate(itr,itr+1,end());
		resize(size_-1);
		return itr;
	}

	/*
	 * Accessor: begin.
	 * Pre: None
	 * Post: returns pointer to beginning of data array
	 * Exception: no throw guarantee
	 */
	iterator begin(){
		return data_;
	}

	/*
	 * Accessor: const begin.
	 * Pre: None
	 * Post: returns pointer to beginning of data array
	 * Exception: no throw guarantee
	 */
	const_iterator begin() const{
		return data_;
	}

	/*
	 * Accessor: end.
	 * Pre: None
	 * Post: returns pointer to one past end of data array
	 * Exception: no throw guarantee
	 */
	iterator end(){
		return data_ + size_;
	}

	/*
	 * Accessor: const end.
	 * Pre: None
	 * Post: returns pointer to one past end of data array
	 * Exception: no throw guarantee
	 */
	const_iterator end() const{
		return data_ + size_;
	}

	/*
	 * Swap function
	 * Swaps the values of two TSMArray objects
	 * Pre: pointer to valid TSmArray
	 * Post: swapped values
	 * Exception: no throw guarantee (it doesn't move data that would throw)
	 */
	void swap(TSmArray & rhs){
		std::swap(data_,rhs.data_);
		std::swap(size_,rhs.size_);
		std::swap(capacity_,rhs.capacity_);
	}


private:
	size_type size_;  //Size of array
	size_type capacity_; //Actual 'size' of array, IE capacity to grow without resizing and moving data
	value_type * data_;  //pointer to data array.


};	//end of clas TSmArray

#endif