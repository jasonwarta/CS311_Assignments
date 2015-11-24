// treesort.h  UNFINISHED
// Glenn G. Chappell
// 19 Nov 2015
//
// For CS 311 Fall 2015
// Skeleton file for Assignment 7, Exercise A

#ifndef FILE_TREESORT_H_INCLUDED
#define FILE_TREESORT_H_INCLUDED

#include <type_traits>
using std::remove_reference;
#include <algorithm>
using std::stable_sort;
using std::copy;
#include <vector>
using std::vector;
#include <iterator>
using std::distance;
#include <iostream>

// int count = 0;

template<typename N>
struct Node{
	N data_;
	Node<N> * left_ = nullptr;
	Node<N> * right_ = nullptr;
	// size_t size_;
	
	~Node() {
		if (left_ != nullptr)
			delete left_;
		if (right_ != nullptr)
			delete right_;
			
	}

	void add(Node<N> * & root, N item){  //recursion removed version
		auto * nPointer = root;
		while(1) { //Keep looping until we hit a return.
			if(item < nPointer->data_){
				if(nPointer->left_ != nullptr){
					nPointer = nPointer->left_ ; //Move to the left child
				}
				else {
					nPointer->left_ = new Node<N>; //Empty spot found, adding node
					nPointer->left_->data_ = item; //put value in
					return; //New node added, leave function
				}
			}
			else{ //Item is greater than the node
				if(nPointer->right_ != nullptr){  //Node not empty
					nPointer = nPointer->right_; //Move to right child
				}
				else {
					nPointer->right_ = new Node<N>;  //empty spot found, adding node
					nPointer->right_->data_ = item;  //put value in
					return; //New node added, leave function
				}
			}
		}
	}

	template<typename FDIter>
	void inorder(Node<N> * root, FDIter & itr){
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
//     ???
// Post:
//     ???
// Requirements on Types:
//     ???
// Exception safety guarantee:
//     ???
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

    // THE FOLLOWING IS DUMMY CODE. IT WILL PASS ALL TESTS. BUT IT DOES
    // NOT MEET THE REQUIREMENTS OF THE ASSIGNMENT.
    // vector<Value> buff(distance(first, last));
    // copy(first, last, buff.begin());
    // stable_sort(buff.begin(), buff.end());
    // copy(buff.begin(), buff.end(), first);
}

#endif //#ifndef FILE_TREESORT_H_INCLUDED

