/*
 * da3.h
 * 
 * Jason Warta
 * 2015.09.30
 * 
 * Finished header for assignment 3
 */

// da3.h  UNFINISHED
// Glenn G. Chappell
// 25 Sep 2015
// 
// For CS 311 Fall 2015
// Header file for Assignment 3 Functions

#ifndef FILE_DA3_H_INCLUDED
#define FILE_DA3_H_INCLUDED

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <typeinfo>
using std::size_t;


// **************************************************************** // *
// Begin DO-NOT-CHANGE section                                      // *
// Do not alter the lines below                                     // *
// **************************************************************** // *
                                                                    // *
                                                                    // *
// struct LLNode                                                    // *
// Linked List node, with client-specified value type               // *
// Invariants:                                                      // *
//     Either _next is nullptr, or _next points to an LLNode,       // *
//      allocated with new, owned by *this.                         // *
// Requirements on Types:                                           // *
//     ValueType must have a copy ctor and a dctor.                 // *
template <typename ValueType>                                       // *
struct LLNode {                                                     // *
    ValueType _data;  // Data for this node                         // *
    LLNode * _next;   // Ptr to next node, or nullptr if none       // *
                                                                    // *
    // The following simplify creation & destruction                // *
                                                                    // *
    // 1- & 2-param ctor                                            // *
    // Pre:                                                         // *
    //     theNext, if passed, is either nullptr, or else it        // *
    //      points to an LLNode, allocated with new, with           // *
    //      ownership transferred to *this.                         // *
    // Post:                                                        // *
    //     _data == theData.                                        // *
    //     If _next passed, then _next == theNext. Otherwise,       // *
    //      _next is nullptr.                                       // *
    explicit LLNode(const ValueType & theData,                      // *
                    LLNode * theNext = nullptr)                     // *
        :_data(theData), _next(theNext)                             // *
    {}                                                              // *
                                                                    // *
    // dctor                                                        // *
    // Pre: None.                                                   // *
    // Post: None. (_next delete'd)                                 // *
    ~LLNode()                                                       // *
    { delete _next; }                                               // *
};                                                                  // *
                                                                    // *
                                                                    // *
// **************************************************************** // *
// End DO-NOT-CHANGE section                                        // *
// Do not alter the lines above                                     // *
// **************************************************************** // *


/*
 * listItem(const LLNode *, size_t) - gets the data at a given index of a linked list
 * pre: must pass the pointer to the head of a linked list, and an index
 * post: returns the value at the index, if the index is valid
 *       if the index is invalid, throws out_of_range exception
 */
template <typename ValueType>
ValueType listItem(const LLNode<ValueType> * head,
                   size_t index)
{   
    if(head == NULL) throw std::out_of_range("Empty list");
    if(index < 0) throw std::out_of_range("Index can't be negative.");

    size_t size = 0;
    auto p = head;
    
    while(p != nullptr){
        if(size == index) return p->_data;

        ++size;
        p = p->_next;
    }

    if(index > size-1) throw std::out_of_range("Index too large.");

    return p->_data;
}

/*
 * didItThrow(Func,bool &)
 * pre: must pass a function and bool by reference
 * post: calls function without parameters, and catches any exceptions
 *       bool will be set to true if the function threw an exception, false if not
 *       exception will be passed back to the calling code
 */
template <typename Func>
void didItThrow(Func f,
                bool & threw)
{   
    threw = true;
    try{
        f();
        threw = false;
    } catch (std::exception &e){
        threw = true;
        throw;
    } 
}

/*
 * countUnique(iterator,iterator) - counts unique items in a range of a collection
 * pre: must pass valid iterators
 *      behavior not defined for null or otherwise invalid iterators
 * post: returns the number of unique items in the range
 */
template <typename RAITer>
size_t countUnique(RAITer first,
                   RAITer last)
{   
    int count = 0;

    std::vector<RAITer> addresses; //vector of addresses

    for(auto iter = first; iter != last; ++iter){
    bool exists = false;

        for(int j = 0; j < addresses.size(); ++j){
            // this dereferences the address stored in the vector,
            // and compares to the dereferenced iterator
            if( *(addresses[j]) == (*iter) ){
                exists = true;  //
                break;
            }
        }
        if(!exists){
            addresses.push_back(iter); //store the address of the item in the vector
            count++;
        }
    }

    return count;
}

/*
 * gcd(int,int) - calculates the greatest common denominator of two numbers
 * pre: takes two ints
 * post: returns the greatest common denominator of the two numbers
 */
int gcd(int a,
        int b);


#endif  //#ifndef FILE_DA3_H_INCLUDED

