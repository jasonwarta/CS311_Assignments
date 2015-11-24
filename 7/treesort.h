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

	void add(Node<N> * root, N item){
		if(item < root->data_){
			if(root->left_ != nullptr){
				add(root->left_,item);
			}
			else {
				root->left_ = new Node<N>;
				root->left_->data_ = item;
			}
		}
		else{
			if(root->right_ != nullptr){
				add(root->right_,item);
			}
			else {
				root->right_ = new Node<N>;
				root->right_->data_ = item;
			}
		}
	}

	template<typename FDIter>
	void inorder(Node<N> * root, FDIter & itr){
		std::cout << "doing inorder" << std::endl;
		if(root->left_ != nullptr){
			inorder(root->left_,itr);
		}

		*itr = root->data_;
		itr++;
		

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

    FDIter current = first;
    Node<Value> * tree;
    tree->data_ = *first;//(tree,*first);
    current++;

    for(auto i = current; i != last; i++){
    	tree->add(tree,*i);
    }

   	std::cout << "done copying to tree" << std::endl;

    tree->inorder(tree,first);

    std::cout << "done inorder" << std::endl;




    // THE FOLLOWING IS DUMMY CODE. IT WILL PASS ALL TESTS. BUT IT DOES
    // NOT MEET THE REQUIREMENTS OF THE ASSIGNMENT.
    // vector<Value> buff(distance(first, last));
    // copy(first, last, buff.begin());
    // stable_sort(buff.begin(), buff.end());
    // copy(buff.begin(), buff.end(), first);
}

#endif //#ifndef FILE_TREESORT_H_INCLUDED

