/*
 * closepair.h
 * 
 * Jason Warta
 * 2015.10.17
 * 
 * Header and function defenitions for assignment 4
 */

#ifndef CLOSEPAIR_H_INCLUDED
#define CLOSEPAIR_H_INCLUDED

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <vector>
using std::vector;
#include <utility>
using std::pair;
using std::make_pair;
#include <cstddef>
using std::size_t;
#include <algorithm>
using std::sort;
#include <cmath>
#include <limits>
#include <cfloat>
#include <ctime>

/* 
 * These functions implement the Closest Pair algorithm
 * 
 * They are designed to work together
 * Client code should call this function:
 * 		pair<size_t,size_t> closePair(RAIter first, RAIter last)
 * to get a return value, or the recursive version if passing a pair by reference
 */

using Pt2 = pair<float, float>;

/*
 * closePair_Recursive(RAIter, float, size_t, size_t, pair<size_t,size_t>)
 * recursive version of closest pair algorithm
 * Pre: takes an iterator to the start of a dataset with two or more items
 * 			takes a float by reference, for tracking the minimum calculated distance
 * 			takes two size_t variables containing the indexes of the values to be used
 * 			takes a pair<size_t,size_t> for tracking the pair of closest points found so far
 * Post: returns nothing
 * 			the minimum distance variable will be set to the minimum distance found
 * 			the pair<size_t,size_t> will contain the indexes of the closest pair of points
 */
template<typename RAIter>
void closePair_Recursive(RAIter first, float & minDist, size_t loIdx, size_t hiIdx, pair<size_t,size_t> &closestPair){

	//calculate size and set up variable for future calculuations of distance
	size_t size = hiIdx - loIdx;
	float dist = 0;

	//brute force when there are 7 or less items in the set of items
	//this avoids an issue with one of the 5 item sets
	//also, several timing trials seems to indicate that brute-forcing at approximately this point 
	//	is faster than using recursion to reduce the dataset further to sets of 3
	if(size <= 7){
		for(size_t i = loIdx; i < size; i++){
			for(size_t j = i+1; j < size; j++){
				dist = sqrt( pow((first[i].first - first[j].first),2) + pow((first[i].second - first[j].second),2) );
				if(dist < minDist){
					minDist = dist;
					closestPair.first = i;
					closestPair.second = j;
				}
			}
		}
		return;
	}
	
	//find mid index and midpoint value
	size_t midIdx = loIdx + (size/2);
	float midVal = ( first[(midIdx)].second + first[midIdx+1].second )/2;

	//split the dataset into two parts and recursively call against each half
	closePair_Recursive(first,minDist,midIdx+1,hiIdx,closestPair); //upper half
	closePair_Recursive(first,minDist,loIdx,midIdx,closestPair); //lower half

	vector<size_t> pointList;

	//check the middle of the dataset for vals within minDist of the middle value
	for(size_t i = midIdx; (i > loIdx) && (midVal - minDist < first[i].second); i--){
		pointList.push_back(i);
	}

	//check the middle of the dataset for vals within minDist of the middle value
	for(size_t i = midIdx+1; (i < hiIdx) && (midVal + minDist > first[i].second); i++){
		pointList.push_back(i);
	}

	//sort the vector of indexes
	sort(pointList.begin(), pointList.end(), 
		[=](size_t i1, size_t i2)
		{ return first[i1].first < first[i2].first; } 
	);

	//work through the vector of indexes of points in the center of the dataset
	//if any of them are less than the minimum distance found, 
	//	update the minimum distance and the closestPair
	for(size_t i = 0; i < pointList.size(); i++){
		for(size_t j = i+1; j < pointList.size(); j++){
			dist = sqrt(  pow((first[pointList[j]].first - first[pointList[i]].first),2) 
				           +pow((first[pointList[j]].second - first[pointList[i]].second),2) );
			if(dist < minDist){
				closestPair.first = pointList[i];
				closestPair.second = pointList[j];
				minDist = dist;
			}
		}
	}
	return;
}

/*
 * closePair(RAIter,RAIter)
 * wrapper function for closest pair algorithm
 * this function calls the recursive implementation of the algorithm
 * Pre: takes an iterator to the first value of a dataset
 * 			takes an iterator to the address just pass the last item in the dataset
 * Post: returns a pair<size_t,size_t> containing the indexes of the two closest points in the dataset
 */
template<typename RAIter>
pair<size_t, size_t> closePair(RAIter first, RAIter last){
	//sort list of points by y value
	std::sort(first, last, 
		[](const Pt2 & a, const Pt2 & b) 
		{ return a.second < b.second; }
	);

	//init variables to appropriate values
	float minDist = FLT_MAX;
	size_t size = last - first;
	pair<size_t,size_t> closestPair = {0,1};

	if(last-first > 3) closePair_Recursive(first,minDist,0,size,closestPair);
	else {
		float dist = 0;

		for(size_t i = 0; i < size; i++){
			for(size_t j = i+1; j < size; j++){
				dist = sqrt( pow((first[i].first - first[j].first),2) + pow((first[i].second - first[j].second),2) );
				if(dist < minDist){
					minDist = dist;
					closestPair.first = i;
					closestPair.second = j;
				}
			}
		}
	}

	return closestPair;
}

#endif