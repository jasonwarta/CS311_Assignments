// treesort_test.cpp
// Glenn G. Chappell
// 19 Nov 2015
// Updated: 23 Nov 2015
//
// For CS 311 Fall 2015
// Test program for function treesort
// Used in Assignment 7, Exercise A

// Includes for code to be tested
#include "treesort.h"   // For treesort
#include "treesort.h"   // Double inclusion test

// Includes for testing package & code common to all test programs
#include <iostream>     // for std::cout, std::endl, std::cin
#include <string>       // for std::string
#include <stdexcept>    // for std::runtime_error

// Additional includes for this test program
#include <vector>       // for std::vector
#include <list>         // for std::list
#include <forward_list> // for std::forward_list
#include <algorithm>    // for std::stable_sort, std::equal
#include <iterator>     // for std::advance
#include <cmath>        // for std::sqrt, std::floor
#include <cstddef>      // for std::size_t
#include <cassert>      // for assert


// ************************************************************************
// Testing Package:
//     Class Tester - For Tracking Tests
// ************************************************************************


// class Tester
// For extremely simple unit testing.
// Keeps track of number of tests and number of passes.
// Use test (with success/failure parameter) to do a test.
// Get results with numTests, numPassed, numFailed, allPassed.
// Restart testing with reset.
// Invariants:
//     countTests_ == number of tests (calls to test) since last reset.
//     countPasses_ == number of times function test called with true param
//      since last reset.
//     0 <= countPasses_ <= countTests_.
//     tolerance_ >= 0.
class Tester {

// ***** Tester: ctors, dctor, op= *****
public:

    // Default ctor
    // Sets countTests_, countPasses_ to zero, tolerance_ to given value
    // Pre: None.
    // Post:
    //     numTests == 0, countPasses == 0, tolerance_ == abs(theTolerance)
    // Does not throw (No-Throw Guarantee)
    Tester(double theTolerance = 0.0000001)
        :countTests_(0),
         countPasses_(0),
         tolerance_(theTolerance >= 0 ? theTolerance : -theTolerance)
    {}

    // Compiler-generated copy ctor, copy op=, dctor are used

// ***** Tester: general public functions *****
public:

    // test
    // Handles single test, param indicates pass/fail
    // Pre: None.
    // Post:
    //     countTests_ incremented
    //     countPasses_ incremented if (success)
    //     Message indicating test name (if given)
    //      and pass/fail printed to cout
    // Does not throw (No-Throw Guarantee)
    //  - Assuming exceptions have not been turned on for cout.
    void test(bool success,
              const std::string & testName = "")
    {
        ++countTests_;
        if (success) ++countPasses_;

        std::cout << "    ";
        if (testName != "")
        {
            std::cout << "Test: "
                      << testName
                      << " - ";
        }
        std::cout << (success ? "passed" : "********** FAILED **********")
                  << std::endl;
    }

    // ftest
    // Does single floating-point test.
    // Tests passes iff difference of first two values is <= tolerance.
    // Pre: None.
    // Post:
    //     countTests_ incremented
    //     countPasses_ incremented if (abs(val1-val2) <= tolerance_)
    //     Message indicating test name (if given)
    //      and pass/fail printed to cout
    // Does not throw (No-Throw Guarantee)
    void ftest(double val1,
               double val2,
               const std::string & testName = "")
    { test(val1-val2 <= tolerance_ && val2-val1 <= tolerance_, testName); }

    // reset
    // Resets *this to default constructed state
    // Pre: None.
    // Post:
    //     countTests_ == 0, countPasses_ == 0
    // Does not throw (No-Throw Guarantee)
    void reset()
    {
        countTests_ = 0;
        countPasses_ = 0;
    }

    // numTests
    // Returns the number of tests that have been done since last reset 
    // Pre: None.
    // Post:
    //     return == countTests_
    // Does not throw (No-Throw Guarantee)
    int numTests() const
    { return countTests_; }

    // numPassed
    // Returns the number of tests that have passed since last reset
    // Pre: None.
    // Post:
    //     return == countPasses_
    // Does not throw (No-Throw Guarantee)
    int numPassed() const
    { return countPasses_; }

    // numFailed
    // Returns the number of tests that have not passed since last reset
    // Pre: None.
    // Post:
    //     return + countPasses_ == numTests_
    // Does not throw (No-Throw Guarantee)
    int numFailed() const
    { return countTests_ - countPasses_; }

    // allPassed
    // Returns true if all tests since last reset have passed
    // Pre: None.
    // Post:
    //     return == (countPasses_ == countTests_)
    // Does not throw (No-Throw Guarantee)
    bool allPassed() const
    { return countPasses_ == countTests_; }

    // setTolerance
    // Sets tolerance_ to given value
    // Pre: None.
    // Post:
    //     tolerance_ = abs(theTolerance)
    // Does not throw (No-Throw Guarantee)
    void setTolerance(double theTolerance)
    { tolerance_ = (theTolerance >= 0 ? theTolerance : -theTolerance); }

// ***** Tester: data members *****
private:

    int countTests_;    // Number of tests done since last reset
    int countPasses_;   // Number of tests passed since last reset
    double tolerance_;  // Tolerance for floating-point near-equality tests

};  // end class Tester


// ************************************************************************
// Testing Package:
//     Class TypeCheck - Helper Class for Type Checking
// ************************************************************************


// class TypeCheck
// This class exists in order to have static member function check, which
// takes a parameter of a given type, by reference. Objects of type
// TypeCheck<T> cannot be created.
// Usage:
//     TypeCheck<MyType>::check(x)
//     returns true if the type of x is (MyType) or (const MyType),
//     otherwise false.
// Invariants: None.
// Requirements on Types: None.
template<typename T>
class TypeCheck {

private:

    // Uncopyable class. Do not define copy ctor, copy assn.
    TypeCheck(const TypeCheck &);
    TypeCheck<T> & operator=(const TypeCheck &);

    // Compiler-generated dctor is used (but irrelevant).

public:

    // check
    // The function and function template below simulate a single function
    // that takes a single parameter, and returns true iff the parameter has
    // type T or (const T).

    // check (reference-to-const T)
    // Pre: None.
    // Post:
    //     Return is true.
    // Does not throw (No-Throw Guarantee)
    static bool check(const T & param)
    { return true; }

    // check (reference-to-const non-T)
    // Pre: None.
    // Post:
    //     Return is false.
    // Requirements on types: None.
    // Does not throw (No-Throw Guarantee)
    template <typename OtherType>
    static bool check(const OtherType & param)
    { return false; }

};  // End class TypeCheck


// ************************************************************************
// Testing Package:
//     Class Counter - Helper Class for Counting Calls & Objects, Throwing
// ************************************************************************


// class Counter
// Item type for counting ctor, dctor, op= calls, counting existing
//  objects, and possibly throwing on copy. Has operator< (which always
//  returns false), allowing it to be the value type of a sorted container.
// If static member copyThrow_ is set, then copy ctor and copy assn throw
//  std::runtime_error. Exception object's "what" member is set to "C" by
//  the copy ctor and "A" by copy assn.
// Increments static data member ctorCount_ on default construction and
//  successful copy construction. Increments static data member assnCount_
//  on successful copy assignment. Increments static data member
//  dctorCount_ on destruction.
// Increments static data member existing_ on construction, and decrements
//  it on destruction.
// Static data member maxExisting_ is highest value of existing_ since last
//  reset, or start of program if reset has never been called.
// Invariants:
//     Counter::existing_ is number of existing objects of this class.
//     Counter::ctorCount_ is number of successful ctor calls since
//      most recent call to reset, or start of program if reset has never
//      been called.
//     Counter::dctorCount_ is (similarly) number of dctor calls.
//     Counter::assnCount_ is (similarly) number of copy assn calls.
//     Counter::maxExisting_ is (similarly) highest value existing_ has
//      assumed.
class Counter {

// ***** Counter: Ctors, dctor, op= *****
public:

    // Default ctor
    // Pre: None.
    // Post:
    //     (ctorCount_ has been incremented.)
    //     (existing_ has been incremented.)
    // Does not throw (No-Throw Guarantee)
    Counter()
    {
        ++existing_;
        if (existing_ > maxExisting_)
            maxExisting_ = existing_;
        ++ctorCount_;
    }

    // Copy ctor
    // Throws std::runtime_error if copyThrow_.
    // Pre: None.
    // Post:
    //     (ctorCount_ has been incremented.)
    //     (existing_ has been incremented.)
    // May throw std::runtime_error
    // Strong Guarantee
    Counter(const Counter & other)
    {
        if (copyThrow_)
            throw std::runtime_error("C");
        ++existing_;
        if (existing_ > maxExisting_)
            maxExisting_ = existing_;
        ++ctorCount_;
    }

    // Copy assignment
    // Throws std::runtime_error if copyThrow_.
    // Pre: None.
    // Post:
    //     Return value is *this.
    //     (assnCount_ has been incremented.)
    // May throw std::runtime_error
    // Strong Guarantee
    Counter & operator=(const Counter & rhs)
    {
        if (copyThrow_)
            throw std::runtime_error("A");
        ++assnCount_;
        return *this;
    }

    // Dctor
    // Pre: None.
    // Post:
    //     (dctorCount_ has been incremented.)
    //     (existing_ has been decremented.)
    // Does not throw (No-Throw Guarantee)
    ~Counter()
    {
        --existing_;
        ++dctorCount_;
    }

// ***** Counter: Functions dealing with count *****
public:

    // reset
    // Pre: None.
    // Post:
    //     maxExisting_ == existing_.
    //     ctorCount_ == 0.
    //     dctorCount_ == 0.
    //     assnCount_ == 0.
    //     copyThrow_ == shouldThrow.
    // Does not throw (No-Throw Guarantee)
    static void reset(bool shouldThrow = false)
    {
        maxExisting_ = existing_;
        ctorCount_ = 0;
        dctorCount_ = 0;
        assnCount_ = 0;
        copyThrow_ = shouldThrow;
    }

    // getExisting
    // Pre: None.
    // Post:
    //     return == existing_.
    // Does not throw (No-Throw Guarantee)
    static int getExisting()
    { return existing_; }

    // getMaxExisting
    // Pre: None.
    // Post:
    //     return == maxExisting_.
    // Does not throw (No-Throw Guarantee)
    static int getMaxExisting()
    { return maxExisting_; }

    // getCtorCount
    // Pre: None.
    // Post:
    //     return == ctorCount_.
    // Does not throw (No-Throw Guarantee)
    static int getCtorCount()
    { return ctorCount_; }

    // getDctorCount
    // Pre: None.
    // Post:
    //     return == dctorCount_.
    // Does not throw (No-Throw Guarantee)
    static int getDctorCount()
    { return dctorCount_; }

    // getAssnCount
    // Pre: None.
    // Post:
    //     return == assnCount_.
    // Does not throw (No-Throw Guarantee)
    static int getAssnCount()
    { return assnCount_; }

    // setCopyThrow
    // Pre: None.
    // Post:
    //     copyThrow_ == shouldThrow
    // Does not throw (No-Throw Guarantee)
    static void setCopyThrow(bool shouldThrow)
    { copyThrow_ = shouldThrow; }

// ***** Counter: Data Members *****
private:

    static int existing_;     // # of existing objects
    static int maxExisting_;  // Max # of existing objects
    static int ctorCount_;    // # of successful (non-throwing) ctor calls
    static int dctorCount_;   // # of dctor calls
    static int assnCount_;    // # of successful (non-throwing) copy = calls
    static bool copyThrow_;   // true if copy operations (ctor, =) throw

};  // End class Counter

// Definition of static data member of class Counter
int Counter::existing_ = 0;
int Counter::maxExisting_ = 0;
int Counter::ctorCount_ = 0;
int Counter::dctorCount_ = 0;
int Counter::assnCount_ = 0;
bool Counter::copyThrow_ = false;


// operator< (Counter)
// Dummy-ish operator<, forming a strict weak order for Counter class
// Returns false (which is legal for a strict weak order; all objects of
//  type Counter are equivalent).
// Pre: None.
// Post:
//     Return value == false.
// Does not throw (No-Throw Guarantee)
bool operator<(const Counter & a,
               const Counter & b)
{ return false; }


// ************************************************************************
// Helper Functions/Classes for This Test Program
// ************************************************************************


// class MyPair
// Holds pair of ints
// operator== as usual, operator< only compairs first item in each pair.
// Invariants: None.
class MyPair {

public:

    // Default ctor, ctor from 1 int, ctor from 2 ints
    // Sets _x, _y to given values; 0 if not given.
    // Pre: None.
    // Post:
    //     _x, _y set as indicated.
    // Does not throw (No-Throw Guarantee)
    MyPair(int theX = 0,
           int theY = 0)
        :_x(theX),
         _y(theY)
    {}

    // Compiler-generated copy ctor, copy =, dctor used

    // getX
    // returns _x
    // Pre: None.
    // Post:
    //     Return value == _x.
    // Does not throw (No-Throw Guarantee)
    int getX() const
    { return _x; }

    // getY
    // returns _y
    // Pre: None.
    // Post:
    //     Return value == _y.
    // Does not throw (No-Throw Guarantee)
    int getY() const
    { return _y; }

private:

    int _x;  // First item in pair
    int _y;  // Second item in pair

};  // End class MyPair


// operator== (MyPair)
// The usual == op for a pair: compares both items.
// Pre: None.
// Post:
//     Return value == (a._x == b._x && a._y == b._y).
bool operator==(const MyPair & a,
                const MyPair & b)
{ return a.getX() == b.getX() && a.getY() == b.getY(); }


// operator< (MyPair)
// Calls op< on _x only.
// Pre: None.
// Post:
//     Return value == (a._x == b._x).
bool operator<(const MyPair & a,
               const MyPair & b)
{ return a.getX() < b.getX(); }


// ************************************************************************
// Test Suite Functions
// ************************************************************************


// test_treesort_type_requirements
// Test suite for function treesort, type requirements
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_treesort_type_requirements(Tester & t)
{
    std::cout << "Test Suite: function treesort, type requirements"
              << std::endl;

    // Works with minimal-functionality type (passes if it compiles)
    std::vector<Counter> v(100);
    treesort(v.begin(), v.end());
    t.test(true, "Allows value type with minimal functionality");

    std::forward_list<int> fl(100);
    t.test(true, "Allows iterator type with minimal functionality");
}


// test_treesort_basic_int
// Test suite for function treesort, basics, sorting ints
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_treesort_basic_int(Tester & t)
{
    std::cout << "Test Suite: function treesort, basics - sorting ints"
              << std::endl;

    // Value type for this test suite
    typedef int val;

    const int DATASIZE = 20;
    const std::vector<val> dataCheck
        { 3, 6, 19, -2, 8, 6, 7, 1, 141, -2,
          -200, 4, 6, 6, 11, -5, 32, 2, 7, 0 };
    assert (dataCheck.size() == std::size_t(DATASIZE));

    // Make copies of data
    std::list<val> data_l(dataCheck.begin(), dataCheck.end());
    std::forward_list<val> data_fl(dataCheck.begin(), dataCheck.end());

    // Sorted data (all but first, last)
    std::vector<val> dataSorted1(dataCheck.begin(), dataCheck.end());
    std::stable_sort(dataSorted1.begin()+1, dataSorted1.end()-1);

    // Sorted data (all)
    std::vector<val> dataSorted2(dataCheck.begin(), dataCheck.end());
    std::stable_sort(dataSorted2.begin(), dataSorted2.end());

    // Tests with std::list

    std::list<val>::iterator lit1, lit2;

    // Test: list empty range
    lit1 = data_l.begin();
    std::advance(lit1, 3);
    lit2 = data_l.begin();
    std::advance(lit2, 3);
    treesort(lit1, lit2);
    t.test(std::equal(data_l.begin(), data_l.end(), dataCheck.begin()),
        "list: empty range");

    // Test: list one item
    ++lit2;
    treesort(lit1, lit2);
    t.test(std::equal(data_l.begin(), data_l.end(), dataCheck.begin()),
        "list: one item");

    // Test: list nearly all
    lit1 = data_l.begin();
    ++lit1;
    lit2 = data_l.begin();
    std::advance(lit2, DATASIZE-1);
    treesort(lit1, lit2);
    t.test(std::equal(data_l.begin(), data_l.end(), dataSorted1.begin()),
        "list: nearly all");

    // Test: list all
    treesort(data_l.begin(), data_l.end());
    t.test(std::equal(data_l.begin(), data_l.end(), dataSorted2.begin()),
        "list: all");

    // Tests with std::forward_list

    std::forward_list<val>::iterator flit1, flit2;

    // Test: forward_list empty range
    flit1 = data_fl.begin();
    std::advance(flit1, 3);
    flit2 = data_fl.begin();
    std::advance(flit2, 3);
    treesort(flit1, flit2);
    t.test(std::equal(data_fl.begin(), data_fl.end(), dataCheck.begin()),
        "forward_list: empty range");

    // Test: forward_list one item
    ++flit2;
    treesort(flit1, flit2);
    t.test(std::equal(data_fl.begin(), data_fl.end(), dataCheck.begin()),
        "forward_list: one item");

    // Test: forward_list nearly all
    flit1 = data_fl.begin();
    ++flit1;
    flit2 = data_fl.begin();
    std::advance(flit2, DATASIZE-1);
    treesort(flit1, flit2);
    t.test(std::equal(data_fl.begin(), data_fl.end(), dataSorted1.begin()),
        "forward_list: nearly all");

    // Test: forward_list all
    treesort(data_fl.begin(), data_fl.end());
    t.test(std::equal(data_fl.begin(), data_fl.end(), dataSorted2.begin()),
        "forward_list: all");
}


// test_treesort_basic_double
// Test suite for function treesort, basics, sorting doubles
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_treesort_basic_double(Tester & t)
{
    std::cout << "Test Suite: function treesort, basics - sorting doubles"
              << std::endl;

    // Value type for this test suite
    typedef double val;

    const int DATASIZE = 20;
    const std::vector<val> dataCheck
        { 3.1, 6.2, 19.3, -2.4, 8.5, 6.6, 7.7, 1.8, 141.9, -2.0,
          -200.1, 4.2, 6.3, 6.4, 11.5, -5.6, 32.7, 2.8, 7.9, 0.0 };
    assert (dataCheck.size() == std::size_t(DATASIZE));

    // Make copies of data
    std::list<val> data_l(dataCheck.begin(), dataCheck.end());
    std::forward_list<val> data_fl(dataCheck.begin(), dataCheck.end());

    // Sorted data (all but first, last)
    std::vector<val> dataSorted1(dataCheck.begin(), dataCheck.end());
    std::stable_sort(dataSorted1.begin()+1, dataSorted1.end()-1);

    // Sorted data (all)
    std::vector<val> dataSorted2(dataCheck.begin(), dataCheck.end());
    std::stable_sort(dataSorted2.begin(), dataSorted2.end());

    // Tests with std::list

    std::list<val>::iterator lit1, lit2;

    // Test: list empty range
    lit1 = data_l.begin();
    std::advance(lit1, 3);
    lit2 = data_l.begin();
    std::advance(lit2, 3);
    treesort(lit1, lit2);
    t.test(std::equal(data_l.begin(), data_l.end(), dataCheck.begin()),
        "list: empty range");

    // Test: list one item
    ++lit2;
    treesort(lit1, lit2);
    t.test(std::equal(data_l.begin(), data_l.end(), dataCheck.begin()),
        "list: one item");

    // Test: list nearly all
    lit1 = data_l.begin();
    ++lit1;
    lit2 = data_l.begin();
    std::advance(lit2, DATASIZE-1);
    treesort(lit1, lit2);
    t.test(std::equal(data_l.begin(), data_l.end(), dataSorted1.begin()),
        "list: nearly all");

    // Test: list all
    treesort(data_l.begin(), data_l.end());
    t.test(std::equal(data_l.begin(), data_l.end(), dataSorted2.begin()),
        "list: all");

    // Tests with std::forward_list

    std::forward_list<val>::iterator flit1, flit2;

    // Test: forward_list empty range
    flit1 = data_fl.begin();
    std::advance(flit1, 3);
    flit2 = data_fl.begin();
    std::advance(flit2, 3);
    treesort(flit1, flit2);
    t.test(std::equal(data_fl.begin(), data_fl.end(), dataCheck.begin()),
        "forward_list: empty range");

    // Test: forward_list one item
    ++flit2;
    treesort(flit1, flit2);
    t.test(std::equal(data_fl.begin(), data_fl.end(), dataCheck.begin()),
        "forward_list: one item");

    // Test: forward_list nearly all
    flit1 = data_fl.begin();
    ++flit1;
    flit2 = data_fl.begin();
    std::advance(flit2, DATASIZE-1);
    treesort(flit1, flit2);
    t.test(std::equal(data_fl.begin(), data_fl.end(), dataSorted1.begin()),
        "forward_list: nearly all");

    // Test: forward_list all
    treesort(data_fl.begin(), data_fl.end());
    t.test(std::equal(data_fl.begin(), data_fl.end(), dataSorted2.begin()),
        "forward_list: all");
}


// test_treesort_object_count
// Test suite for function treesort, object counts
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_treesort_object_count(Tester & t)
{
    std::cout << "Test Suite: function treesort, object counts"
              << std::endl;

    const int SIZE = 100;
    std::vector<Counter> vc(SIZE);
    Counter::reset();
    int base_existing = Counter::getExisting();

    treesort(vc.begin(), vc.end());
    t.test(Counter::getMaxExisting() >= base_existing + SIZE,
        "at least n additional objects used in sorting");
    t.test(Counter::getExisting() == base_existing,
        "all additional objects destroyed");

}


// test_treesort_stability
// Test suite for function treesort, stability
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_treesort_stability(Tester & t)
{
    std::cout << "Test Suite: function treesort, stability"
              << std::endl;

    const int SIZE = 16;

    std::vector<int> dataX
        { 8, 7, 7, 6, 2, 3, 2, 4, 8, 3, 1, 1, 4, 5, 6, 5 };
    assert (dataX.size() == std::size_t(SIZE));
    std::vector<int> dataY
        { 1, 1, 2, 1, 1, 1, 2, 1, 2, 2, 1, 2, 2, 1, 2, 2 };
    assert (dataY.size() == std::size_t(SIZE));

    std::vector<MyPair> vp1(SIZE);
    std::vector<MyPair> vp2;

    // Test #1
    for (int i = 0; i < SIZE; ++i)
        vp1[i] = MyPair(dataX[i], dataY[i]);
    vp2 = vp1;

    treesort(vp1.begin(), vp1.end());
    std::stable_sort(vp2.begin(), vp2.end());
    t.test(std::equal(vp1.begin(), vp1.end(), vp2.begin()),
        "treesort is stable, test #1");

    // Test #2
    for (int i = 0; i < SIZE; ++i)
        vp1[i] = MyPair(9-dataX[i], 3-dataY[i]);
    vp2 = vp1;

    treesort(vp1.begin(), vp1.end());
    std::stable_sort(vp2.begin(), vp2.end());
    t.test(std::equal(vp1.begin(), vp1.end(), vp2.begin()),
        "treesort is stable, test #2");
}


// test_treesort_large
// Test suite for function treesort, large list
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_treesort_large(Tester & t)
{
    std::cout << "Test Suite: function treesort, larger list"
              << std::endl;

    // Value type for this test suite
    typedef int val;

    const int DATASIZE = 50000;
    std::vector<val> data;
    const double phi = (1.+std::sqrt(5.))/2.;

    for (int i = 0; i < DATASIZE; ++i)
    {
        double pp = phi * double(i);
        int n = int((pp-std::floor(pp))*double(DATASIZE));
        data.push_back(n);
    }
    std::vector<val> data2 = data;

    treesort(data.begin(), data.end());
    std::stable_sort(data2.begin(), data2.end());

    t.test(std::equal(data.begin(), data.end(), data2.begin()),
        "larger list");
}


// test_treesort
// Test suite for function treesort
// Uses other test-suite functions
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_treesort(Tester & t)
{
    // Do all the test suites
    std::cout << "TEST SUITES FOR FUNCTION treesort" << std::endl;
    test_treesort_type_requirements(t);
    test_treesort_basic_int(t);
    test_treesort_basic_double(t);
    test_treesort_object_count(t);
    test_treesort_stability(t);
    test_treesort_large(t);
}


// ************************************************************************
// Main program
// ************************************************************************


// main
// Runs function treesort test suite, prints results to cout.
int main()
{
    Tester t;
    test_treesort(t);

    std::cout << std::endl;
    if (t.allPassed())
    {
        std::cout << "All tests successful" 
                  << std::endl;
    }
    else
    {
        std::cout << "Tests ********** UNSUCCESSFUL **********"
                  << std::endl;
    }
    std::cout << std::endl;

    // Wait for user
    std::cout << "Press ENTER to quit ";
    while (std::cin.get() != '\n') ;

    return 0;
}
