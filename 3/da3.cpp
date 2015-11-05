/*
 * da3.cpp
 * 
 * Jason Warta
 * 2015.09.30
 * 
 * Finished source code for assignment 3
 */

// da3.cpp  UNFINISHED
// Glenn G. Chappell
// 25 Sep 2015
// 
// For CS 311 Fall 2015
// Source file for Assignment 3 Functions

#include "da3.h"  // For Assignment 3 prototypes & templates

int gcd(int a,
        int b)
{	
	if(b==0) return a; //avoid div by 0 error
	return gcd(b,a%b);
}