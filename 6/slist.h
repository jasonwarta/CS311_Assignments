#ifndef SLIST_H_INCLUDED
#define SLIST_H_INCLUDED

#include <cstddef>
using std::size_t;
#include <algorithm>
using std::swap;



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
			delete next_;
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

	}

	/*
	 * copy assignment
	 * 
	 */
	SList & operator=(const SList & rhs){

	}

	/*
	 * destructor
	 * 
	 */
	~SList(){
	}

	/*
	 * 
	 */
	void swap(SList & rhs){
		std::swap(head_,rhs.head_);
		std::swap(size_,rhs.size_);
	}

	/*
	 * 
	 */
	size_type size() const {
		return size_;
		
		auto p = head_;
		size_type size = 0;
		while(p != nullptr){
			p = p->next_;
			size++;
		}
		return size;
	}

	/*
	 * empty - returns a bool indiciting whether or not the size of the list is zero
	 * precondition: none
	 * post: returns a true if the list is empty, otherwise false.
	 * exception: no-throw guarantee.
	 */
	bool empty() const {
	return !size_;  //just to kill error
	}

	/*
	 * 
	 */
	void clear(){

	}

	/*
	 * 
	 */
	void push_back(const value_type & item){

	}

	/*
	 * 
	 */
	value_type & pop_front(){

	}

	/*
	 * 
	 */
	template<typename OutputIterator>
	void get(OutputIterator dest) const{
		
	}

	/*
	 * 
	 */
	void reverse(){
		//3 pointer rotate
		//(head,head->next_,save)
	}

	/*
	 * 
	 */
	value_type & front(){
		value_type temp;
		return temp;

	}

	/*
	 * 
	 */
	const value_type & front() const{
		value_type temp;
		return temp;
	}

private:
	LLNode * head_;
	size_type size_ ; //Size of the list, avoids having to recalculate it

};//end of class SList

#endif