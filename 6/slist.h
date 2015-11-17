#ifndef SLIST_H_INCLUDED
#define SLIST_H_INCLUDED

#include <cstddef>
using std::size_t;
#include <algorithm>
using std::swap;



template<class SL>
class SList{

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
	 * 
	 */
	SList(){

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

	}

	/*
	 * 
	 */
	size_type size(){
		auto p = head_;
		size_type size = 0;
		while(p != nullptr){
			p = p->next_;
			size++;
		}
		return size;
	}

	/*
	 * 
	 */
	bool empty(){

	}

	/*
	 * 
	 */
	void clear(){

	}

	/*
	 * 
	 */
	void push_back(value_type & item){

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

	}

	/*
	 * 
	 */
	const value_type & front() const{

	}

private:
	LLNode * head_;

};//end of class SList

#endif