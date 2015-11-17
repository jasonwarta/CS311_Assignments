// slist.h
// Jason Warta and Jason Bright
// 17 Nov 2015
//
// For CS 311 Fall 2015
// Header for class template TSmArray
// Used in Assignment 6
// Note: Was going to do a fancy memory saving system, but realized that we're not guaranteed to have an efficient assignment available.

#ifndef SLIST_H_INCLUDED
#define SLIST_H_INCLUDED

#include <cstddef>
using std::size_t;
#include <algorithm>
using std::swap;
//for testing purposes
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;

template<class SL>
class SList{

public:
	typedef std::size_t size_type;
	typedef SL value_type;
	
	struct LLNode{
		value_type data_;
		LLNode * next_;

		/*
	 	 * 
	 	 */
		explicit LLNode(const value_type & data, LLNode * next = nullptr):data_(data),next_(next){}

		/*
	 	 * 
	 	 */
		~LLNode(){
			if (next_ != nullptr) {//make sure there's another node to delete
//				delete next_; //delete any following nodes
			}
		}
	};//end of struct LLNode

	/*
	 * default ctor
	 * Creates a list of size 0
	 * Pre: None
	 * Post: list of size 0
	 * Exception: no throw guarantee
	 */
	SList(){
		head_ = nullptr;
		size_ = 0;

	}

	/*
	 * copy ctor
	 * 
	 */
	SList(const SList & rhs){
		head_ = nullptr;
		size_ = 0;
		auto temp = rhs.head_;
		while (temp != nullptr) {
			push_back(temp->data_); //store the next item in the back of the list
			temp = temp->next_; //move to the next item
		}
	}

	/*
	 * copy assignment
	 * 
	 */
	SList & operator=(SList rhs){
		swap(rhs);
		return *this;
	}

	/*
	 * destructor
	 * 
	 */
	~SList(){
//		delete head_;
	}

	/*
	 * Swap function
	 * Preconditions: valid lists
	 * Post: the objects are swapped
	 * Exception: No throw guarantee
	 */
	void swap(SList & rhs){
		std::swap(head_,rhs.head_);
		std::swap(back_,rhs.back_);
		std::swap(size_,rhs.size_);
	}

	/*
	 * Size() - Returns the size of the list
	 * Modified to be constant time.
	 * Pre: none
	 * Post: returns the size of the list
	 * Exception: no throw guarantee
	 */
	size_type size() const {
		return size_;
// Old code saved just in case.		
/*
		auto p = head_;
		size_type size = 0;
		while(p != nullptr){
			p = p->next_;
			size++;
		}
		return size;
*/
	}

	/*
	 * empty - returns a bool indiciting whether or not the size of the list is zero
	 * precondition: none
	 * post: returns a true if the list is empty, otherwise false.
	 * exception: no-throw guarantee.
	 */
	bool empty() const {
	return !(size_);
	}

	/*
	 * 
	 */
	void clear(){
		if (head_ != nullptr)
		{
			delete head_;
			back_ = nullptr;
			head_ = nullptr;

			/*  Stretch goal:  save on memory allocation
			back_->next_ = spares_; //take the last item, add the existing spares to it.
			back_ = nullptr;
			head_ = nullptr;
			size_ = 0; // set size to zero
			*/
		}
	}

	/*
	 * push_back: Adds a new element to the end of the list.
	 * exception neutral
	 */
	void push_back(const value_type & item){
		//Stretch goal:  Memory managment
		LLNode * temp = new LLNode(item);
		if(head_ == nullptr){ //Check to see if the list was empty
			head_ = temp; //head was empty, make it point to the new first item.
			back_ = temp; //first item is also the last item
		} else //not an empty list
		{
			back_->next_ = temp; //append address to the last item in the list
			back_ = temp; //point back at the new end address.
		}
		++size_; //add another to the list
	}

	/*
	 * Removes a node from the beginning of the list
	 * Constant time
	 * pre: none; if list is empty it doesn't do anything
	 * post: first item is deleted and head_ points to the next item in the list
	 * exception: no throw guarantee
	 */
	void pop_front(){
		if (head_ != nullptr) { //make sure the list isn't empty.  If it is, do nothing.
			auto temp = head_; //save head into a temp variable
			head_ = head_->next_ ; //put the address of the next link into head
			temp->next_ = nullptr; //clear out the next address in our temp to prevent it from deleting the rest
			delete temp; //delete the node.  
			--size_; //keep track of the size of the list
		}

	}

	/*
	 * 
	 */
	template<typename OutputIterator>
	void get(OutputIterator dest) const{
		LLNode * temp = head_;
		while (temp != nullptr) {
			dest = temp->data_;
			temp = temp->next_;
		}
			
	}

	/*
	 * 
	 */
	void reverse(){
		//3 pointer rotate
		//(head,head->next_,save)
		LLNode * save = nullptr;
		LLNode * s2 = nullptr;
		back_ = head_;
		while (head_ != nullptr) {
			s2 = save; //Put safe into temporary value
			save = head_; //put head into safe
			head_ = head_->next_; //move head up one
			save->next_ = s2; //put the temporary value into the old node
		}
		head_ = save;  //Put head to what it should be
		back_->next_ = nullptr;
		
	}

	/*
	 * front() - returns a pointer to the data in the first element
	 * pre: there has to be data to return
	 * post: returns the pointer, otherwise unknown
	 * exception:  Currently neutral
	 */
	value_type & front(){
		return head_->data_;
	}

	/*
	 * const version of front()
	 * pre:  there has to be data to return
	 * post: returns a pointer to the data
	 * exception:  Currently neutral
	 */
	const value_type & front() const{
		return head_->data_;
	}

private:
	LLNode * head_; //First item in list
	LLNode * back_; //Last item in list
	size_type size_ ; //Size of the list, avoids having to recalculate it

};//end of class SList

#endif