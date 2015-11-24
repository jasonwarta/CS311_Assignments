// treesort.h
// Jason Warta and Jason Bright
// 24 Nov 2015
//
// For CS 311 Fall 2015
// Header for template treesort and associated structures and functions
// Used in Assignment 7
// ***********************
// Based off of code by 
// Glenn G. Chappell
// 19 Nov 2015
//
// For CS 311 Fall 2015
// Skeleton file for Assignment 7, Exercise A

#ifndef FILE_TREESORT_H_INCLUDED
#define FILE_TREESORT_H_INCLUDED

#include <type_traits>
using std::remove_reference;

/* Struct Node 
 * Creates a node that handles type N
 * Invariants:  
 * left_ = left node, if present, else nullptr
 * right_ = right version
 * data_ = the data contained in the node, of user type.
 * Note:  If you delete a node, it deletes all of it's children.
*/
template<typename Ntype>
struct Node{
	Ntype data_;
	Node<Ntype> * left_ = nullptr;
	Node<Ntype> * right_ = nullptr;
	
// Destructor
// Destroy a Node
// Pre:
//     None
// Post:
//     The node and all of it's children will be deleted
// Requirements on Types:
//     N/A
// Exception safety guarantee:
//     No throw guarantee;
	~Node() {
		if (left_ != nullptr)
			delete left_;
		if (right_ != nullptr)
			delete right_;
			
	}
// add
// Add a Node, non-recursive version.
// Pre:
//     Internal use only; pointer to root of tree, as well as a value to insert
// Post:
//     A node is added in the correct spot.
// Requirements on Types:
//     N/A - if you've already created a node, as lont as an error hasn't been thrown.
// Exception safety guarantee:
//     exception neutral;  Note that New is used, so it can throw.
	void add(Node<Ntype> * & root, Ntype item){  //recursion removed version
		auto * nPointer = root;
		while(1) { //Keep looping until we hit a return.
			if(item < nPointer->data_){
				if(nPointer->left_ != nullptr){
					nPointer = nPointer->left_ ; //Move to the left child
				}
				else {
					nPointer->left_ = new Node<Ntype>; //Empty spot found, adding node
					nPointer->left_->data_ = item; //put value in
					return; //New node added, leave function
				}
			}
			else{ //Item is greater than the node
				if(nPointer->right_ != nullptr){  //Node not empty
					nPointer = nPointer->right_; //Move to right child
				}
				else {
					nPointer->right_ = new Node<Ntype>;  //empty spot found, adding node
					nPointer->right_->data_ = item;  //put value in
					return; //New node added, leave function
				}
			}
		}
	}
// inorder
// Does an inorder sort on a tree.
// Pre:
//     Should only be called internally by treesort or recursively by itself
//		
// Post:
//     The data will be inorder sorted
// Requirements on Types:
//     The data must be comparable with the < operator and copy =, not have a throwing destructor.
// Exception safety guarantee:
//     Exception neutral
	template<typename FDIter>
	void inorder(Node<Ntype> * root, FDIter & itr){
		if(root->left_ != nullptr){
			inorder(root->left_,itr);
		}

		*itr++ = root->data_;

		if(root->right_ != nullptr){
			inorder(root->right_,itr);
		}
	}
};//end of struct Node


// treesort
// Sort a given range using Treesort.
// Pre:
//     Must be given valid forward iterators, last must be after first.
//		
// Post:
//     The data will be treesorted
// Requirements on Types:
//     The data must be comparable with the < operator and copy=, not have a throwing destructor.
// Exception safety guarantee:
//     Exception neutral
template<typename FDIter>
void treesort(FDIter first, FDIter last)
{
    // Get the type that FDIter points to
    using Value = typename remove_reference<decltype(*first)>::type;
		if (first == last)  //First = last, empty list
			return; //just return.
    FDIter current = first;
    Node<Value> * tree = new Node<Value>;
    tree->data_ = *first;//(tree,*first);
    current++;

    for(auto i = current; i != last; i++){
    	tree->add(tree,*i);
    }
    tree->inorder(tree,first);
		delete tree;
}

#endif //#ifndef FILE_TREESORT_H_INCLUDED

