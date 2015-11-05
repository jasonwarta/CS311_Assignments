/*
 * ssarray.h
 * 
 * Jason Warta
 * 2015.09.21
 * 
 * SSArray class defenition for CS311 Assignment 2
 */

#ifndef SSARRAY_H_INCLUDED
#define SSARRAY_H_INCLUDED

#include <cstdlib> //using std::size_t

/*
 * class SSArray
 * SSArray is a generic typed RAII container class
 * Invariants:
 *   data_ is a pointer to the start of a collection of the specified type
 *   data_ is allocated using new, and deleted when the class object is deleted
 */
template<class SSA>
class SSArray{

public:
	/*** * * * * * * * * ****/
	/*** Type Defenitions ***/
	/*** * * * * * * * * ****/

	/*
	 * generic types
	 * size_type is an unsigned type for tracking the size of the array
	 * value_type is the type ofitems in the array
	 */
	typedef std::size_t size_type;
	typedef SSA value_type;

 	/*
 	 * Iterators
 	 * iterator is a pointer to a value_type
	 * const_iterator is a pointer to a const value_type
	 */
	typedef value_type * iterator;
	typedef const value_type * const_iterator;

	/*** * * * * * * ****/
	/*** Constructors ***/
	/*** * * * * * * ****/

	/*
	 * SSArray() - default ctor
	 * pre: none
	 * post: creates an array of size 10
	 */
	SSArray():size_(10){
		data_ = new value_type[size_];
	};

	/*
	 * SSArray(const SSArray&) - copy ctor
	 * pre: must pass a valid SSArray object
	 * post: replaces current object with passed object
	 */
	SSArray(const SSArray &rhs){
		if(this != &rhs){
			delete[] data_;
			size_ = rhs.size_;
			data_ = new value_type[size_];

			for(size_type i = 0; i < size_; i++){
				data_[i] = rhs.data_[i];
			}
		}
	}

	/*
	 * operator=(SSArray&) - copy assignment operator
	 * pre: must pass a valid SSArray object
	 * post: replaces current object with passed object, and returns it by reference
	 */
	SSArray & operator=(const SSArray &rhs){
		// if(this != &rhs){
		// 	delete[] data_;

		// 	size_ = rhs.size_;
		// 	data_ = new value_type[size_];

		// 	for(size_type i = 0; i < size_; i++){
		// 		data_[i] = rhs.data_[i];
		// 	}
		// }
		return *(this(rhs));
	}

	/*
	 * ~SSarray() - destructor
	 * pre: none
	 * post: array is deleted, and size is set to 0
	 */
	~SSArray(){
		delete[] data_;
		size_ = 0;
	}


	/*
	 * SSArray(size_type) - one parameter constructor
	 * pre: must pass valid, non-negative array size
	 * post: size is set to passed value
	 *       array is constructed of the specified size, with default values
	 */
	explicit SSArray(size_type size):size_(size){
		data_ = new value_type[size_];
	}

	/*
	 * SSArray(size_type, const value_type) - two parameter constructor
	 * pre: must pass valid, non-negative size, and a value to init the array's elements to
	 * post: size is set to passed value
	 *       array is constructed of the specified size, with all the elements set to the passed value
	 */
	SSArray(size_type size, const value_type & init_value):size_(size){
		data_ = new value_type[size_];

		for(size_type i = 0; i < size_; i++){
			data_[i] = init_value;
		}
	}

	/*** * * * * * * * ****/
	/*** Member Methods ***/
	/*** * * * * * * * ****/

	/*
	 * operaotr[](size_type) - bracket operator
	 * pre: must pass a valid index within the range of 0 to size-1
	 *      invalid index returns the item at index 0
	 * post: returns the item at the specified index
	 */
	value_type & operator[](size_type idx){
		if(idx >= 0 && idx < size_) return data_[idx];
		else return data_[0];
	}

	/*
	 * operator[](size_type) - bracket operator, const version
	 * pre: must pass valid index within the range of 0 to size-1
	 * 	    invalid index returns the item at index 0
	 * post: returns the item at the specified index
	 */
	value_type & operator[](size_type idx) const{
		if(idx >= 0 && idx < size_) return data_[idx];
		else return data_[0];
	}

	/*
	 * size() - size function, const
	 * pre: none
	 * post: returns the size of the array
	 */
	size_type size() const{
		return size_;
	}

	/*
	 * begin() - iterator
	 * pre: none
	 * post: returns an iterrator to the first element in the array
	 */
	iterator begin(){
		return data_;
	}

	/*
	 * begin() - iterator, const version
	 * pre: none
	 * post: returns an iterator to the first element in the array
	 */
	const_iterator begin() const{
		return data_;
	}

	/*
	 * end() - iterator
	 * pre: none
	 * post: returns an iterator to the last element in the array
	 */
	iterator end(){
		return data_+size_;
	}

	/*
	 * end() - iterator, const version
	 * pre: none
	 * post: returns an iterator to the last element in the array
	 */
	const_iterator end() const{
		return data_+size_;
	}

	/*** * * * * * * * * * * * * * * ***/
	/*** friend overloaded operators ***/
	/*** * * * * * * * * * * * * * * ***/

	/*
	 * operator==(const SSArray&, const SSarray&) - boolean operator ==
	 * pre: must pass valid, comparable SSArray objects
	 * post: returns a boolean true if the SSArray objects are equivalent
	 */
	friend bool operator==(const SSArray<value_type> &lhs, const SSArray<value_type> &rhs){
		if(lhs.size_ == rhs.size_){
			for(size_type i = 0; i < lhs.size_; i++){
				if(lhs[i] != rhs[i]) return false;
			}
			return true;
		} else {
			return false;
		}
	};

	/*
	 * operator!=(const SSArray&, const SSArray&) - boolean operator !=
	 * pre: must pass valid, comparable SSArray objects
	 * post: returns a boolean true if the SSArray objects are not equivalent
	 */
	friend bool operator!=(const SSArray<value_type> &lhs, const SSArray<value_type> &rhs){
		return !(rhs == lhs);
	};

	/*
	 * operator<(const SSArray&, const SSArray&) - boolean operator <
	 * pre: must pass valid, comparable SSArray objects
	 * post: returns a boolean true if the first object is less than the second object
	 */
	friend bool operator<(const SSArray<value_type> &lhs, const SSArray<value_type> &rhs){
		//determine smaller value to avoid going out of bounds
		size_type min;
		if(lhs.size() < rhs.size()){
			min = lhs.size();
		} else {
			min = rhs.size();
		}

		//compare each item in array, and return if conditions are satisfied
		for(size_type i = 0; i < min; i++){
			if(lhs[i] < rhs[i]) return true;
			else if(lhs[i] > rhs[i]) return false;
		}

		//at this point, each item has been compared to, and
		//been found to be equal to, the corresponding item in the other array, so we
		//check the size, and return the appropriate response
		if(lhs.size_ < rhs.size_) return true;
		else if (lhs.size_ >= rhs.size_) return false;

		return false;
	};

	/*
	 * operator<=(const SSarray&, const SSArray&) - boolean operator <=
	 * pre: must pass valid, comparable SSArray objects
	 * post: returns a boolean true if the first object is less than or equal to the second object
	 */
	friend bool operator<=(const SSArray<value_type> &lhs, const SSArray<value_type> &rhs){
		return !(lhs > rhs);
	};

	/*
	 * operator>(const SSarray&, const SSarray&) - boolean operator >
	 * pre: must pass valid, comparable SSArray objects
	 * post: returns a boolean true if the first object is greater than the second object
	 */
	friend bool operator>(const SSArray<value_type> &lhs, const SSArray<value_type> &rhs){
		return rhs < lhs;
	};

	/*
	 * operator>=(const SSarray&, const SSarray& - boolean operator >=
	 * pre: must pass valid, comparable SSArray objects
	 * post: returns a boolean true if the first object is greater than or equal to the second object)
	 */
	friend bool operator>=(const SSArray<value_type> &lhs, const SSArray<value_type> &rhs){
		return !(lhs < rhs);
	};


private:
	value_type * data_;
	size_type size_;
};

#endif

