// da6_test.cpp
// Glenn G. Chappell
// 13 Nov 2015
//
// For CS 311 Fall 2015
// Test program for class templates SList, SLQueue
// Used in Assignment 6, Exercises A & B

// Includes for code to be tested
#include "slist.h"      // For class template SList
#include "slist.h"      // Double inclusion test
#include "slqueue.h"    // For class template SLQueue
#include "slqueue.h"    // Double inclusion test

// Includes for testing package & code common to all test programs
#include <iostream>     // for std::cout, std::endl, std::cin
#include <string>       // for std::string
#include <stdexcept>    // for std::runtime_error

// Additional includes for this test program
#include <cstddef>      // for std::size_t, std::ptrdiff_t
#include <deque>        // for std::deque
#include <iterator>     // for std::back_inserter
#include <list>         // for std::list
#include <algorithm>    // for std::equal, std::reverse


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


// inRange
// Checks whether v lies in [a,b].
// Pre: None.
// Post: Return value is true if a <= v and v <= b,
//     false otherwise.
// Does not throw (No-Throw Guarantee)
bool inRange(int v, int a, int b)
{
    return a <= v && v <= b;
}


// makeList
// Given an SList object and a range specified via iterators, uses
// SList::clear and SList::push_back to give the SList the same values
// as those in the given range.
// Pre:
//     [first, last) is a valid range.
// Post:
//     The values in theList are those from [first, last), in order.
// Requirements on Types:
//     ValType is a valid value type for SList.
//     InputIterator is an input iterator type.
//     The value type of InputIterator is ValType.
template <typename ValType, typename InputIterator>
void makeList(SList<ValType> & theList,
              InputIterator first,
              InputIterator last)
{
    theList.clear();
    for (auto it = first; it != last; ++it)
        theList.push_back(*it);
}


// makeQueue
// Given an SLQueue object and a range specified via iterators, uses
// SLQueue::op= and SLQueue::push to give the SLQueue the same values
// as those in the given range.
// Pre:
//     [first, last) is a valid range.
// Post:
//     The values in theQueue are those from [first, last), in order.
// Requirements on Types:
//     ValType is a valid value type for SLQueue.
//     InputIterator is an input iterator type.
//     The value type of InputIterator is ValType.
template <typename ValType, typename InputIterator>
void makeList(SLQueue<ValType> & theQueue,
              InputIterator first,
              InputIterator last)
{
    SLQueue<ValType> q;
    for (auto it = first; it != last; ++it)
        q.push(*it);
    theQueue = q;
}


// queueGet
// Given an SLQueue object and an output iterator, writes all items in the queue to the output iterator. Queue is emptied.
// Pre:
//     out references sufficient space to hold all items in theQueue.
// Post:
//     Values written to out are former values in theQueue, in order.
// Requirements on Types:
//     ValType is a valid value type for SLQueue.
//     OutputIterator is an output iterator type.
//     The value type of OutputIterator is ValType.
template <typename ValType, typename OutputIterator>
void queueGet(SLQueue<ValType> & theQueue,
              OutputIterator out)
{
    while (!theQueue.empty())
    {
        auto f = theQueue.front();
        theQueue.pop();
        *out++ = f;
    }
}


// ************************************************************************
// Test Suite Functions
// ************************************************************************


// test_class_SList_types
// Test suite for class SList, types
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SList_types(Tester & t)
{
    std::cout << "Test Suite: class SList, types" << std::endl;

    bool correctType1;  // result of type checking
    bool correctType2;  // result of type checking

    SList<double> sld;
    sld.push_back(4.2);
    sld.push_back(1.0);
    const SList<double> & csld(sld);
    SList<std::string> sls;
    sls.push_back("abc");
    sls.push_back(std::string("def"));
    const SList<std::string> & csls(sls);


    // MEMBER TYPE value_type
    t.test(TypeCheck<double>::check(SList<double>::value_type()),
        "value_type, SList<double>");
    t.test(TypeCheck<std::string>::check(SList<std::string>::value_type()),
        "value_type, SList<string>");

    // MEMBER TYPE size_type
    correctType1 =
        TypeCheck<std::size_t>::check(SList<double>::size_type());
    correctType2 =
        TypeCheck<std::ptrdiff_t>::check(SList<double>::size_type());
    t.test(correctType1 || correctType2,
        "size_type, SList<int>");
    correctType1 =
        TypeCheck<std::size_t>::check(SList<double>::size_type());
    correctType2 =
        TypeCheck<std::ptrdiff_t>::check(SList<std::string>::size_type());
    t.test(correctType1 || correctType2,
        "size_type, SList<string>");

    // MEMBER FUNCTION size, return type
    t.test(TypeCheck<SList<double>::size_type>::check(csld.size()),
        "Return type, function size");

    // MEMBER FUNCTION empty, return type
    t.test(TypeCheck<bool>::check(csld.empty()),
        "Return type, function empty");

    // MEMBER FUNCTION front, return type
    t.test(TypeCheck<double>::check(csld.front()),
        "Return type, function front, const");
    t.test(TypeCheck<double>::check(sld.front()),
        "Return type, function front, non-const");

    // MEMBER FUNCTION op=, return type
    t.test(TypeCheck<SList<std::string> >::check(sls = csls),
        "Return type, copy assignment operator");
}


// test_class_SList_default_ctor
// Test suite for class SList, default ctor
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SList_default_ctor(Tester & t)
{
    std::cout << "Test Suite: class SList, default ctor" << std::endl;

    const SList<int> csli1;
    t.test(csli1.size() == 0, "Default ctor, const - size is zero");
    t.test(csli1.empty(), "Default ctor, const - empty is true");

    std::deque<int> vi1;
    csli1.get(std::back_inserter(vi1));
    t.test(vi1.empty(), "Default ctor, const - get does nothing");

    SList<double> sld1;
    t.test(sld1.size() == 0, "Default ctor, non-const - size is zero");
    t.test(sld1.empty(), "Default ctor, const - empty is true");

    std::deque<double> vd1;
    sld1.get(std::back_inserter(vd1));
    t.test(vd1.empty(), "Default ctor, non-const - get does nothing");
}


// test_class_SList_push_pop
// Test suite for class SList, push_back, pop_front, front
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SList_push_pop(Tester & t)
{
    std::cout << "Test Suite: class SList, push_back, pop_front, front"
              << std::endl;

    SList<int> sli;
    const SList <int> & csli(sli);

    t.test(sli.size() == 0, "Start, size");
    t.test(sli.empty(), "Start, empty");

    sli.push_back(20);

    t.test(sli.size() == 1, "push_back, size");
    t.test(!sli.empty(), "push_back, empty");
    t.test(sli.front() == 20, "push_back, front");
    t.test(sli.front() == 20, "push_back, front (repeat)");
    t.test(csli.front() == 20, "push_back, front (const)");

    sli.push_back(10);

    t.test(sli.size() == 2, "push_back #2, size");
    t.test(!sli.empty(), "push_back #2, empty");
    t.test(sli.front() == 20, "push_back #2, front");
    t.test(sli.front() == 20, "push_back #2, front (repeat)");
    t.test(csli.front() == 20, "push_back #2, front (const)");

    sli.pop_front();

    t.test(sli.size() == 1, "pop_front, size");
    t.test(!sli.empty(), "pop_front, empty");
    t.test(sli.front() == 10, "pop_front, front");
    t.test(sli.front() == 10, "pop_front, front (repeat)");
    t.test(csli.front() == 10, "pop_front, front (const)");

    sli.push_back(7);
    sli.push_back(3);
    sli.push_back(4);
    sli.push_back(8);

    t.test(sli.size() == 5, "several push_back, size");
    t.test(!sli.empty(), "several push_back, empty");
    t.test(sli.front() == 10, "several push_back, front");
    t.test(sli.front() == 10, "several push_back, front (repeat)");
    t.test(csli.front() == 10, "several push_back, front (const)");

    sli.pop_front();

    t.test(sli.size() == 4, "pop_front #2, size");
    t.test(!sli.empty(), "pop_front #2, empty");
    t.test(sli.front() == 7, "pop_front #2, front");
    t.test(sli.front() == 7, "pop_front #2, front (repeat)");
    t.test(csli.front() == 7, "pop_front #2, front (const)");

    for (int i = 0; i < 100000; ++i)
        sli.push_back(i);

    t.test(sli.size() == 100004, "many push_back, size");
    t.test(!sli.empty(), "many push_back, empty");
    t.test(sli.front() == 7, "many push_back, front");
    t.test(sli.front() == 7, "many push_back, front (repeat)");
    t.test(csli.front() == 7, "many push_back, front (const)");

    for (int i = 0; i < 50004; ++i)
        sli.pop_front();

    t.test(sli.size() == 50000, "many pop_front, size");
    t.test(!sli.empty(), "many pop_front, empty");
    t.test(sli.front() == 50000, "many pop_front, front");
    t.test(sli.front() == 50000, "many pop_front, front (repeat)");
    t.test(csli.front() == 50000, "many pop_front, front (const)");

    for (int i = 0; i < 49999; ++i)
        sli.pop_front();

    t.test(sli.size() == 1, "many pop_front #2, size");
    t.test(!sli.empty(), "many pop_front #2, empty");
    t.test(sli.front() == 99999, "many pop_front #2, front");
    t.test(sli.front() == 99999, "many pop_front #2, front (repeat)");
    t.test(csli.front() == 99999, "many pop_front #2, front (const)");

    sli.pop_front();

    t.test(sli.size() == 0, "Empty again, size");
    t.test(sli.empty(), "Empty again, empty");

    sli.push_back(-1);

    t.test(sli.size() == 1, "push_back #3, size");
    t.test(!sli.empty(), "push_back #3, empty");
    t.test(sli.front() == -1, "push_back #3, front");
    t.test(sli.front() == -1, "push_back #3, front (repeat)");
    t.test(csli.front() == -1, "push_back #3, front (const)");
}


// test_class_SList_copy_ctor
// Test suite for class SList, copy ctor
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SList_copy_ctor(Tester & t)
{
    std::cout << "Test Suite: class SList, copy ctor" << std::endl;

    std::deque<int> dataout;

    // Empty list
    {
    const SList<int> s1;
    const SList<int> s2(s1);
    t.test(s2.empty(), "empty list, empty");
    t.test(s2.size() == 0, "empty list, size");
    dataout.clear();
    s2.get(std::back_inserter(dataout));
    t.test(dataout.empty(), "empty list, data");
    }

    // Small list #1
    {
    std::vector<int> data1 { 8 };
    SList<int> s1;
    makeList(s1, data1.begin(), data1.end());
    SList<int> s2(s1);
    t.test(!s2.empty(), "small list #1, empty");
    t.test(s2.size() == data1.size(), "small list #1, size");
    dataout.clear();
    s2.get(std::back_inserter(dataout));
    t.test(dataout.size() == data1.size(), "small list #1, data size");
    t.test(std::equal(data1.begin(), data1.end(), dataout.begin()),
        "small list #1, data values");
    t.test(s2.front() == s1.front(), "small list #1, fronts equal");
    s2.front() = 5;
    t.test(s2.front() != s1.front(), "small list #1, fronts unequal");
    data1[0] = 5;
    dataout.clear();
    s2.get(std::back_inserter(dataout));
    t.test(dataout.size() == data1.size(),
        "small list #1, data size (again)");
    t.test(std::equal(data1.begin(), data1.end(), dataout.begin()),
        "small list #1, data values (again)");
    }

    // Small list #2
    {
    std::vector<int> data1 { 2, 7, 5 };
    SList<int> s1;
    makeList(s1, data1.begin(), data1.end());
    const SList<int> s2(s1);
    t.test(!s2.empty(), "small list #2, empty");
    t.test(s2.size() == data1.size(), "small list #2, size");
    dataout.clear();
    s2.get(std::back_inserter(dataout));
    t.test(dataout.size() == data1.size(), "small list #2, data size");
    t.test(std::equal(data1.begin(), data1.end(), dataout.begin()),
        "small list #2, data values");
    }

    // Small list #3
    {
    std::vector<int> data1 { 5, 2, 4, 3, 8, 1, 6, 2, 7, 5 };
    SList<int> s1;
    makeList(s1, data1.begin(), data1.end());
    const SList<int> s2(s1);
    t.test(!s2.empty(), "small list #3, empty");
    t.test(s2.size() == data1.size(), "small list #3, size");
    dataout.clear();
    s2.get(std::back_inserter(dataout));
    t.test(dataout.size() == data1.size(), "small list #3, data size");
    t.test(std::equal(data1.begin(), data1.end(), dataout.begin()),
        "small list #3, data values");
    }

    // Large list
    {
    std::vector<int> data1;
    for (int i = 0; i < 100000; ++i)
        data1.push_back(i);
    SList<int> s1;
    makeList(s1, data1.begin(), data1.end());
    const SList<int> s2(s1);
    t.test(!s2.empty(), "large list, empty");
    t.test(s2.size() == data1.size(), "large list, size");
    dataout.clear();
    s2.get(std::back_inserter(dataout));
    t.test(dataout.size() == data1.size(), "large list, data size");
    t.test(std::equal(data1.begin(), data1.end(), dataout.begin()),
        "small list, data values");
    }
}


// test_class_SList_copy_assn
// Test suite for class SList, copy assn
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SList_copy_assn(Tester & t)
{
    std::cout << "Test Suite: class SList, copy assignment" << std::endl;

    std::deque<int> dataout;

    // Empty list
    {
    const SList<int> s1;
    SList<int> s2;
    s2 = s1;
    t.test(s2.empty(), "empty list, empty");
    t.test(s2.size() == 0, "empty list, size");
    dataout.clear();
    s2.get(std::back_inserter(dataout));
    t.test(dataout.empty(), "empty list, data");
    }

    // Small list #1
    {
    std::vector<int> data1 { 8 };
    SList<int> s1;
    makeList(s1, data1.begin(), data1.end());
    SList<int> s2;
    s2 = s1;
    t.test(!s2.empty(), "small list #1, empty");
    t.test(s2.size() == data1.size(), "small list #1, size");
    dataout.clear();
    s2.get(std::back_inserter(dataout));
    t.test(dataout.size() == data1.size(), "small list #1, data size");
    t.test(std::equal(data1.begin(), data1.end(), dataout.begin()),
        "small list #1, data values");
    t.test(s2.front() == s1.front(), "small list #1, fronts equal");
    s2.front() = 5;
    t.test(s2.front() != s1.front(), "small list #1, fronts unequal");
    data1[0] = 5;
    dataout.clear();
    s2.get(std::back_inserter(dataout));
    t.test(dataout.size() == data1.size(),
        "small list #1, data size (again)");
    t.test(std::equal(data1.begin(), data1.end(), dataout.begin()),
        "small list #1, data values (again)");
    }

    // Small list #2
    {
    std::vector<int> data1 { 2, 7, 5 };
    SList<int> s1;
    makeList(s1, data1.begin(), data1.end());
    SList<int> s2;
    s2 = s1;
    t.test(!s2.empty(), "small list #2, empty");
    t.test(s2.size() == data1.size(), "small list #2, size");
    dataout.clear();
    s2.get(std::back_inserter(dataout));
    t.test(dataout.size() == data1.size(), "small list #2, data size");
    t.test(std::equal(data1.begin(), data1.end(), dataout.begin()),
        "small list #2, data values");
    }

    // Small list #3
    {
    std::vector<int> data1 { 5, 2, 4, 3, 8, 1, 6, 2, 7, 5 };
    SList<int> s1;
    makeList(s1, data1.begin(), data1.end());
    SList<int> s2;
    s2 = s1;
    t.test(!s2.empty(), "small list #3, empty");
    t.test(s2.size() == data1.size(), "small list #3, size");
    dataout.clear();
    s2.get(std::back_inserter(dataout));
    t.test(dataout.size() == data1.size(), "small list #3, data size");
    t.test(std::equal(data1.begin(), data1.end(), dataout.begin()),
        "small list #3, data values");
    }

    // Large list
    {
    std::vector<int> data1;
    for (int i = 0; i < 100000; ++i)
        data1.push_back(i);
    SList<int> s1;
    makeList(s1, data1.begin(), data1.end());
    SList<int> s2;
    s2 = s1;
    t.test(!s2.empty(), "large list, empty");
    t.test(s2.size() == data1.size(), "large list, size");
    dataout.clear();
    s2.get(std::back_inserter(dataout));
    t.test(dataout.size() == data1.size(), "large list, data size");
    t.test(std::equal(data1.begin(), data1.end(), dataout.begin()),
        "small list, data values");
    }
}


// test_class_SList_item_counts
// Test suite for class SList, item counts
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SList_item_counts(Tester & t)
{
    std::cout << "Test Suite: class SList, item counts" << std::endl;

    const int DATASIZE = 10;

    {
    std::vector<Counter> data1;

    SList<Counter> slc1;
    for (int i = 0; i < DATASIZE; ++i)
        slc1.push_back(Counter());

    t.test(inRange(Counter::getExisting(), DATASIZE, DATASIZE+1),
        "default ctor - no items created");

    slc1.get(std::back_inserter(data1));
    t.test(inRange(Counter::getExisting(), DATASIZE*2, DATASIZE*2+1),
        "get - check number of items created");

    slc1.get(std::back_inserter(data1));
    t.test(inRange(Counter::getExisting(), DATASIZE*3, DATASIZE*3+1),
        "get again - check number of items created");

    SList<Counter> slc2(slc1);

    t.test(inRange(Counter::getExisting(), DATASIZE*4, DATASIZE*4+2),
        "copy ctor - check number of items created");
    }

    t.test(Counter::getExisting() == 0, "dctor - items destroyed");
}


// test_class_SList_reverse
// Test suite for class SList, reverse
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SList_reverse(Tester & t)
{
    std::cout << "Test Suite: class SList, reverse" << std::endl;

    // Data for reading
    const int DATA1SIZE = 10;
    std::vector<int> data1 { 5, 2, 4, 3, 9, 3, 6, 6, 8, 2 };

    // Get & reverse
    SList<int> sli1;
    makeList(sli1, data1.begin(), data1.end());
    sli1.reverse();
    std::reverse(data1.begin(), data1.end());
    t.test(sli1.size() == DATA1SIZE, "reverse - size");
    std::deque<int> vi1;
    sli1.get(std::back_inserter(vi1));
    t.test(vi1.size() == DATA1SIZE, "reverse - data size");
    t.test(std::equal(vi1.begin(), vi1.end(), data1.begin()),
        "reverse - data values");

    // Get & reverse, number of items
    const int DATA2SIZE = 20;
    std::vector<Counter> data2(DATA2SIZE);
    int numOps;
    {
    SList<Counter> slc1;
    makeList(slc1, data2.begin(), data2.end());
    numOps = Counter::getCtorCount()
           + Counter::getDctorCount()
           + Counter::getAssnCount();
    slc1.reverse();
    t.test(Counter::getCtorCount()
         + Counter::getDctorCount()
         + Counter::getAssnCount() == numOps,
        "reverse - no value-type operations performed");
    t.test(inRange(Counter::getExisting(), DATA2SIZE*2, DATA2SIZE*2+1),
        "reverse - number of items existing");

    data2.clear();
    slc1.get(std::back_inserter(data2));
    t.test(inRange(Counter::getExisting(), DATA2SIZE*2, DATA2SIZE*2+1),
        "reverse/get again - number of items existing");
    }
    t.test(Counter::getExisting() == DATA2SIZE,
        "reverse - dctor, items destroyed");
}


// test_class_SList
// Test suite for class SList
// Uses other test-suite functions
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SList(Tester & t)
{
    // Do all the test suites
    std::cout << "TEST SUITES FOR CLASS SList" << std::endl;
    test_class_SList_types(t);
    test_class_SList_default_ctor(t);
    test_class_SList_push_pop(t);
    test_class_SList_copy_ctor(t);
    test_class_SList_copy_assn(t);
    test_class_SList_item_counts(t);
    test_class_SList_reverse(t);
}


// test_class_SLQueue_types
// Test suite for class SLQueue, types
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SLQueue_types(Tester & t)
{
    std::cout << "Test Suite: class SLQueue, types" << std::endl;

    SLQueue<double> sqd;
    sqd.push(4.2);
    sqd.push(1.0);
    const SLQueue<double> & csqd(sqd);
    SLQueue<std::string> sqs;
    sqs.push("abc");
    sqs.push(std::string("def"));
    const SLQueue<std::string> & csqs(sqs);


    // MEMBER TYPE value_type
    t.test(TypeCheck<double>::check(SLQueue<double>::value_type()),
        "value_type, SLQueue<double>");
    t.test(TypeCheck<std::string>::check(SLQueue<std::string>::value_type()),
        "value_type, SLQueue<string>");

    // MEMBER FUNCTION empty, return type
    t.test(TypeCheck<bool>::check(csqd.empty()),
        "Return type, function empty");

    // MEMBER FUNCTION front, return type
    t.test(TypeCheck<double>::check(csqd.front()),
        "Return type, function front, const");
    t.test(TypeCheck<double>::check(sqd.front()),
        "Return type, function front, non-const");

    // MEMBER FUNCTION op=, return type
    t.test(TypeCheck<SLQueue<std::string> >::check(sqs = csqs),
        "Return type, copy assignment operator");
}


// test_class_SLQueue_default_ctor
// Test suite for class SLQueue, default ctor
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SLQueue_default_ctor(Tester & t)
{
    std::cout << "Test Suite: class SLQueue, default ctor" << std::endl;

    SLQueue<int> sqi1;
    t.test(sqi1.empty(), "Default ctor, const - empty is true");

    std::deque<int> vi1;
    queueGet(sqi1, std::back_inserter(vi1));
    t.test(vi1.empty(), "Default ctor, const - get does nothing");

    SLQueue<double> sqd1;
    t.test(sqd1.empty(), "Default ctor, const - empty is true");

    std::deque<double> vd1;
    queueGet(sqd1, std::back_inserter(vd1));
    t.test(vd1.empty(), "Default ctor, non-const - get does nothing");
}


// test_class_SLQueue_push_pop
// Test suite for class SLQueue, push, pop, front
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SLQueue_push_pop(Tester & t)
{
    std::cout << "Test Suite: class SLQueue, push, pop, front"
              << std::endl;

    SLQueue<int> sqi;
    const SLQueue <int> & csqi(sqi);

    t.test(sqi.empty(), "Start, empty");

    sqi.push(20);

    t.test(!sqi.empty(), "push, empty");
    t.test(sqi.front() == 20, "push, front");
    t.test(sqi.front() == 20, "push, front (repeat)");
    t.test(csqi.front() == 20, "push, front (const)");

    sqi.push(10);

    t.test(!sqi.empty(), "push #2, empty");
    t.test(sqi.front() == 20, "push #2, front");
    t.test(sqi.front() == 20, "push #2, front (repeat)");
    t.test(csqi.front() == 20, "push #2, front (const)");

    sqi.pop();

    t.test(!sqi.empty(), "pop, empty");
    t.test(sqi.front() == 10, "pop, front");
    t.test(sqi.front() == 10, "pop, front (repeat)");
    t.test(csqi.front() == 10, "pop, front (const)");

    sqi.push(7);
    sqi.push(3);
    sqi.push(4);
    sqi.push(8);

    t.test(!sqi.empty(), "several push, empty");
    t.test(sqi.front() == 10, "several push, front");
    t.test(sqi.front() == 10, "several push, front (repeat)");
    t.test(csqi.front() == 10, "several push, front (const)");

    sqi.pop();

    t.test(!sqi.empty(), "pop #2, empty");
    t.test(sqi.front() == 7, "pop #2, front");
    t.test(sqi.front() == 7, "pop #2, front (repeat)");
    t.test(csqi.front() == 7, "pop #2, front (const)");

    for (int i = 0; i < 100000; ++i)
        sqi.push(i);

    t.test(!sqi.empty(), "many push, empty");
    t.test(sqi.front() == 7, "many push, front");
    t.test(sqi.front() == 7, "many push, front (repeat)");
    t.test(csqi.front() == 7, "many push, front (const)");

    for (int i = 0; i < 50004; ++i)
        sqi.pop();

    t.test(!sqi.empty(), "many pop, empty");
    t.test(sqi.front() == 50000, "many pop, front");
    t.test(sqi.front() == 50000, "many pop, front (repeat)");
    t.test(csqi.front() == 50000, "many pop, front (const)");

    for (int i = 0; i < 49999; ++i)
        sqi.pop();

    t.test(!sqi.empty(), "many pop #2, empty");
    t.test(sqi.front() == 99999, "many pop #2, front");
    t.test(sqi.front() == 99999, "many pop #2, front (repeat)");
    t.test(csqi.front() == 99999, "many pop #2, front (const)");

    sqi.pop();

    t.test(sqi.empty(), "Empty again, empty");

    sqi.push(-1);

    t.test(!sqi.empty(), "push #3, empty");
    t.test(sqi.front() == -1, "push #3, front");
    t.test(sqi.front() == -1, "push #3, front (repeat)");
    t.test(csqi.front() == -1, "push #3, front (const)");
}


// test_class_SLQueue_copy_ctor
// Test suite for class SLQueue, copy ctor
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SLQueue_copy_ctor(Tester & t)
{
    std::cout << "Test Suite: class SLQueue, copy ctor" << std::endl;

    std::deque<int> dataout;

    // Empty list
    {
    const SLQueue<int> s1;
    SLQueue<int> s2(s1);
    t.test(s2.empty(), "empty list, empty");
    dataout.clear();
    queueGet(s2, std::back_inserter(dataout));
    t.test(dataout.empty(), "empty list, data");
    }

    // Small list #1
    {
    std::vector<int> data1 { 8 };
    SLQueue<int> s1;
    makeList(s1, data1.begin(), data1.end());
    SLQueue<int> s2(s1);
    t.test(!s2.empty(), "small list #1, empty");
    t.test(s2.front() == s1.front(), "small list #1, fronts equal");
    dataout.clear();
    queueGet(s2, std::back_inserter(dataout));
    t.test(dataout.size() == data1.size(), "small list #1, data size");
    t.test(std::equal(data1.begin(), data1.end(), dataout.begin()),
        "small list #1, data values");
    }

    // Small list #2
    {
    std::vector<int> data1 { 2, 7, 5 };
    SLQueue<int> s1;
    makeList(s1, data1.begin(), data1.end());
    SLQueue<int> s2(s1);
    t.test(!s2.empty(), "small list #2, empty");
    dataout.clear();
    queueGet(s2, std::back_inserter(dataout));
    t.test(dataout.size() == data1.size(), "small list #2, data size");
    t.test(std::equal(data1.begin(), data1.end(), dataout.begin()),
        "small list #2, data values");
    }

    // Small list #3
    {
    std::vector<int> data1 { 5, 2, 4, 3, 8, 1, 6, 2, 7, 5 };
    SLQueue<int> s1;
    makeList(s1, data1.begin(), data1.end());
    SLQueue<int> s2(s1);
    t.test(!s2.empty(), "small list #3, empty");
    dataout.clear();
    queueGet(s2, std::back_inserter(dataout));
    t.test(dataout.size() == data1.size(), "small list #3, data size");
    t.test(std::equal(data1.begin(), data1.end(), dataout.begin()),
        "small list #3, data values");
    }

    // Large list
    {
    std::vector<int> data1;
    for (int i = 0; i < 100000; ++i)
        data1.push_back(i);
    SLQueue<int> s1;
    makeList(s1, data1.begin(), data1.end());
    SLQueue<int> s2(s1);
    t.test(!s2.empty(), "large list, empty");
    dataout.clear();
    queueGet(s2, std::back_inserter(dataout));
    t.test(dataout.size() == data1.size(), "large list, data size");
    t.test(std::equal(data1.begin(), data1.end(), dataout.begin()),
        "small list, data values");
    }
}


// test_class_SLQueue_copy_assn
// Test suite for class SLQueue, copy assn
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SLQueue_copy_assn(Tester & t)
{
    std::cout << "Test Suite: class SLQueue, copy assignment" << std::endl;

    std::deque<int> dataout;

    // Empty list
    {
    const SLQueue<int> s1;
    SLQueue<int> s2;
    s2 = s1;
    t.test(s2.empty(), "empty list, empty");
    dataout.clear();
    queueGet(s2, std::back_inserter(dataout));
    t.test(dataout.empty(), "empty list, data");
    }

    // Small list #1
    {
    std::vector<int> data1 { 8 };
    SLQueue<int> s1;
    makeList(s1, data1.begin(), data1.end());
    SLQueue<int> s2;
    s2 = s1;
    t.test(!s2.empty(), "small list #1, empty");
    t.test(s2.front() == s1.front(), "small list #1, fronts equal");
    dataout.clear();
    queueGet(s2, std::back_inserter(dataout));
    t.test(dataout.size() == data1.size(), "small list #1, data size");
    t.test(std::equal(data1.begin(), data1.end(), dataout.begin()),
        "small list #1, data values");
    }

    // Small list #2
    {
    std::vector<int> data1 { 2, 7, 5 };
    SLQueue<int> s1;
    makeList(s1, data1.begin(), data1.end());
    SLQueue<int> s2;
    s2 = s1;
    t.test(!s2.empty(), "small list #2, empty");
    dataout.clear();
    queueGet(s2, std::back_inserter(dataout));
    t.test(dataout.size() == data1.size(), "small list #2, data size");
    t.test(std::equal(data1.begin(), data1.end(), dataout.begin()),
        "small list #2, data values");
    }

    // Small list #3
    {
    std::vector<int> data1 { 5, 2, 4, 3, 8, 1, 6, 2, 7, 5 };
    SLQueue<int> s1;
    makeList(s1, data1.begin(), data1.end());
    SLQueue<int> s2;
    s2 = s1;
    t.test(!s2.empty(), "small list #3, empty");
    dataout.clear();
    queueGet(s2, std::back_inserter(dataout));
    t.test(dataout.size() == data1.size(), "small list #3, data size");
    t.test(std::equal(data1.begin(), data1.end(), dataout.begin()),
        "small list #3, data values");
    }

    // Large list
    {
    std::vector<int> data1;
    for (int i = 0; i < 100000; ++i)
        data1.push_back(i);
    SLQueue<int> s1;
    makeList(s1, data1.begin(), data1.end());
    SLQueue<int> s2;
    s2 = s1;
    t.test(!s2.empty(), "large list, empty");
    dataout.clear();
    queueGet(s2, std::back_inserter(dataout));
    t.test(dataout.size() == data1.size(), "large list, data size");
    t.test(std::equal(data1.begin(), data1.end(), dataout.begin()),
        "small list, data values");
    }
}


// test_class_SLQueue
// Test suite for class SLQueue
// Uses other test-suite functions
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SLQueue(Tester & t)
{
    // Do all the test suites
    std::cout << "TEST SUITES FOR CLASS SLQueue" << std::endl;
    return;
    test_class_SLQueue_types(t);
    test_class_SLQueue_default_ctor(t);
    test_class_SLQueue_push_pop(t);
    test_class_SLQueue_copy_ctor(t);
    test_class_SLQueue_copy_assn(t);
}


// ************************************************************************
// Main program
// ************************************************************************


// main
// Runs class SList & class SLQueue test suites, prints results to cout.
int main()
{
    Tester t;
    test_class_SList(t);
    std::cout << std::endl;
    test_class_SLQueue(t);

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

