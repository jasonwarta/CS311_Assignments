// tsmarray_test.cpp
// Glenn G. Chappell
// 1 Nov 2015
//
// For CS 311 Fall 2015
// Test program for class template TSmArray
// Used in Assignment 5, Exercise A

// Includes for code to be tested
#include "tsmarray.h"   // For class template TSmArray
#include "tsmarray.h"   // Double inclusion test

// Includes for testing package & code common to all test programs
#include <iostream>     // for std::cout, std::endl, std::cin
#include <string>       // for std::string
#include <stdexcept>    // for std::runtime_error

// Additional includes for this test program
#include <algorithm>    // for std::copy, std::equal
#include <stdexcept>    // for std::runtime_error
#include <string>       // for std::string
#include <cstddef>      // for std::size_t


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


// NONE


// ************************************************************************
// Test Suite Functions
// ************************************************************************


// test_class_TSmArray_types
// Test suite for class TSmArray, types
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_TSmArray_types(Tester & t)
{
    std::cout << "Test Suite: class TSmArray, types" << std::endl;

    bool correctType;  // result of type checking

    TSmArray<int> sti1(10);
    TSmArray<double> std1(10);
    const TSmArray<double> std2(10);

    // MEMBER TYPE value_type
    // Check existence
    // (Passes if code compiles)
    TSmArray<int>::value_type valtype1;
    t.test(true, "Member type value_type exists");

    // Check correctness
    correctType = TypeCheck<int>::check(valtype1);
    t.test(correctType, "Member type value_type is correct (#1)");

    TSmArray<double>::value_type valtype2;
    correctType = TypeCheck<double>::check(valtype2);
    t.test(correctType, "Member type value_type is correct (#2)");

    // MEMBER TYPE size_type
    // Check existence
    // (Passes if code compiles)
    TSmArray<int>::size_type sizetype1;
    t.test(true, "Member type size_type exists");

    // Check correctness
    // (Test fails if const is wrong; other problems cause compiler error)
    correctType = TypeCheck<std::size_t>::check(sizetype1);
    t.test(correctType, "Member type size_type is correct (#1)");

    TSmArray<double>::size_type sizetype2;
    correctType = TypeCheck<std::size_t>::check(sizetype2);
    t.test(correctType, "Member type size_type is correct (#2)");

    // MEMBER TYPE iterator
    // Check existence
    // (Passes if code compiles)
    TSmArray<int>::iterator iter1;
    t.test(true, "Member type iterator exists");

    // Check correctness
    correctType = TypeCheck<int *>::check(iter1);
    t.test(correctType, "Member type iterator is correct (#1)");

    TSmArray<double>::iterator iter2;
    correctType = TypeCheck<double *>::check(iter2);
    t.test(correctType, "Member type iterator is correct (#2)");

    // MEMBER TYPE const_iterator
    // Check existence
    // (Passes if code compiles)
    TSmArray<int>::iterator citer1;
    t.test(true, "Member type const_iterator exists");

    // Check correctness
    correctType = TypeCheck<int *>::check(citer1);
    t.test(correctType, "Member type const_iterator is correct (#1)");

    TSmArray<double>::iterator citer2;
    correctType = TypeCheck<double *>::check(citer2);
    t.test(correctType, "Member type const_iterator is correct (#2)");

    // MEMBER FUNCTION bracket op
    // Check return type
    TypeCheck<double>::check(std2[0]);
        // ignore const-ness
    t.test(true, "Return type, bracket operator (const)");

    correctType = TypeCheck<double>::check(std1[0]);
    t.test(correctType, "Return type, bracket operator (non-const #1)");

    correctType = TypeCheck<int>::check(sti1[0]);
    t.test(correctType, "Return type, bracket operator (non-const #2)");

    // MEMBER FUNCTION copy assignment op
    // Check return type
    TypeCheck<TSmArray<double> >::check(std1 = std2);
    t.test(true, "Return type, copy assignment operator");

    // MEMBER FUNCTION size
    // Check return type
    TypeCheck<TSmArray<double>::size_type>::check(std1.size());
        // ignore const-ness
    t.test(true, "Return type, function size");

    // MEMBER FUNCTION empty
    // Check return type
    TypeCheck<bool>::check(std1.empty());
        // ignore const-ness
    t.test(true, "Return type, function empty");

    // MEMBER FUNCTION begin
    // Check return type
    TypeCheck<TSmArray<double>::const_iterator>::check(std2.begin());
        // ignore const-ness
    t.test(true, "Return type, function begin (const)");

    TypeCheck<TSmArray<double>::iterator>::check(std1.begin());
        // ignore const-ness
    t.test(true, "Return type, function begin (non-const)");

    // MEMBER FUNCTION end
    // Check return type
    TypeCheck<TSmArray<double>::const_iterator>::check(std2.end());
        // ignore const-ness
    t.test(true, "Return type, function end (const)");

    TypeCheck<TSmArray<double>::iterator>::check(std1.end());
        // ignore const-ness
    t.test(true, "Return type, function end (non-const)");

    // MEMBER FUNCTION insert
    // Check return type
    TypeCheck<TSmArray<double>::iterator>::check(
        std1.insert(std1.begin(), 1.0));
    t.test(true, "Return type, function insert");

    // MEMBER FUNCTION remove
    // Check return type
    TypeCheck<TSmArray<double>::iterator>::check(std1.remove(std1.begin()));
    t.test(true, "Return type, function remove");
}


// test_class_TSmArray_size_empty_and_ctor_from_size
// Test suite for class TSmArray, functions size, empty, and ctor from size
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_TSmArray_size_empty_and_ctor_from_size(Tester & t)
{
    std::cout << "Test Suite: class TSmArray - function size, ctor from size"
              << std::endl;

    const TSmArray<int> sti1(0);
    t.test(sti1.size() == 0, "size, ctor from size (const) #1");
    t.test(sti1.empty(), "empty, ctor from size (const) #1");

    const TSmArray<int> sti2(10);
    t.test(sti2.size() == 10, "size, ctor from size (const) #2");
    t.test(!sti2.empty(), "empty, ctor from size (const) #2");

    const TSmArray<double> std(100);
    t.test(std.size() == 100, "size, ctor from size (const) #3)");
    t.test(!std.empty(), "empty, ctor from size (const) #3)");

    TSmArray<int> sti3(20);
    t.test(sti3.size() == 20, "size, ctor from size (non-const)");
    t.test(!sti3.empty(), "size, ctor from size (non-const)");
}


// test_class_TSmArray_default_ctor
// Test suite for class TSmArray, default ctor
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_TSmArray_default_ctor(Tester & t)
{
    std::cout << "Test Suite: class TSmArray - default ctor" << std::endl;

    const TSmArray<int> sti1;
    t.test(sti1.size() == 0, "default ctor, size");
    t.test(sti1.empty(), "default ctor, empty");
}


// test_class_TSmArray_bracket_op
// Test suite for class TSmArray, bracket operator
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_TSmArray_bracket_op(Tester & t)
{
    std::cout << "Test Suite: class TSmArray, bracket operator" << std::endl;

    const int theSize = 10;
    bool noErrors;  // True if no errors encountered
    int i;          // Loop index

    TSmArray<int> sti(theSize);
    for (i = 0; i < theSize; ++i)
        sti[i] = 15 - i * i;

    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (sti[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Bracket operator (non-const) #1");

    sti[2] = 1000;
    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (sti[i] != ((i == 2) ? 1000 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "Bracket operator (non-const) #2");

    // Make const version, no copy
    const TSmArray<int> & stiRef = sti;

    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (stiRef[i] != ((i == 2) ? 1000 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "Bracket operator (const)");
}


// test_class_TSmArray_copy_ctor
// Test suite for class TSmArray, copy ctor
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_TSmArray_copy_ctor(Tester & t)
{
    std::cout << "Test Suite: class TSmArray - copy ctor" << std::endl;

    const int theSize = 10;
    bool noErrors;  // True if no errors encountered
    int i;          // Counter

    TSmArray<int> sti(theSize);
    for (i = 0; i < theSize; ++i)
        sti[i] = 15 - i * i;

    // Make const version, no copy
    const TSmArray<int> & stiRef = sti;
    // Make copy (copy ctor)
    TSmArray<int> stiCopy(stiRef);

    t.test(stiCopy.size() == theSize, "Copy ctor - check size, copy");

    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (stiCopy[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Copy ctor - check values, copy");

    // Change original
    sti[2] = 1000;

    // Check original
    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (sti[i] != ((i == 2) ? 1000 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "Copy ctor - change original, check values, original");

    // Check copy
    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (stiCopy[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Copy ctor - change original, check values, copy");

    // Change copy
    stiCopy[3] = 2000;

    // Check original
    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (sti[i] != ((i == 2) ? 1000 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "Copy ctor - change copy, check values, original");

    // Check copy
    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (stiCopy[i] != ((i == 3) ? 2000 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "Copy ctor - change copy, check values, copy");
}


// test_class_TSmArray_copy_assn
// Test suite for class TSmArray, copy assignment
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_TSmArray_copy_assn(Tester & t)
{
    std::cout << "Test Suite: class TSmArray - copy assignment" << std::endl;

    const int theSize = 10;
    bool noErrors;  // True if no errors encountered
    int i;          // Counter

    TSmArray<int> sti(theSize);
    for (i = 0; i < theSize; ++i)
        sti[i] = 15 - i * i;

    // Make const version, no copy
    const TSmArray<int> & stiRef = sti;
    // Make copy (copy assignment)
    TSmArray<int> stiCopy(1);
    TSmArray<int> & stiReturnRef = (stiCopy = stiRef);

    t.test(&stiReturnRef == &stiCopy, "Copy assignment - return value");
    t.test(stiCopy.size() == theSize, "Copy assignment - check size, copy");

    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (stiCopy[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Copy assignment - check values, copy");

    // Change original
    sti[2] = 1000;

    // Check original
    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (sti[i] != ((i == 2) ? 1000 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors,
        "Copy assignment - change original, check values, original");

    // Check copy
    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (stiCopy[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Copy assignment - change original, check values, copy");

    // Change copy
    stiCopy[3] = 2000;

    // Check original
    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (sti[i] != ((i == 2) ? 1000 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "Copy assignment - change copy, check values, original");

    // Check copy
    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (stiCopy[i] != ((i == 3) ? 2000 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "Copy assignment - change copy, check values, copy");

    // Self-assignment
    TSmArray<int> & stiReturnRef2 = (stiCopy = stiCopy);
    t.test(&stiReturnRef2 == &stiCopy,
        "Copy assignment - self-assignment, return value");
    t.test(stiCopy.size() == theSize,
        "Copy assignment - self-assignment, check size");
    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (stiCopy[i] != ((i == 3) ? 2000 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "Copy assignment - self-assignment, check values");
}


// test_class_TSmArray_resize
// Test suite for class TSmArray, function resize
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_TSmArray_resize(Tester & t)
{
    std::cout << "Test Suite: class TSmArray - resize" << std::endl;

    const int theSize1 = 20;
    const int theSize2 = 10;
    const int theSize3 = 500;
    const int theSize4 = 100000;
    bool noErrors;  // True if no errors encountered
    int i;          // Loop index

    TSmArray<int> sti(theSize1);
    for (i = 0; i < theSize1; ++i)
        sti[i] = 15 - i * i;

    sti.resize(theSize2);
    t.test(sti.size() == theSize2, "Resize - reduce size, check size");
    t.test(!sti.empty(), "Resize - reduce size, check empty");

    noErrors = true;
    for (i = 0; i < theSize2; ++i)
    {
        if (sti[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Resize - reduce size, check values");

    sti.resize(theSize3);
    t.test(sti.size() == theSize3, "Resize - increase size, check size");
    t.test(!sti.empty(), "Resize - increase size, check empty");

    noErrors = true;
    for (i = 0; i < theSize2; ++i)
    {
        if (sti[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Resize - increase size, check values");

    sti.resize(theSize4);
    t.test(sti.size() == theSize4,
        "Resize - increase size greatly, check size");
    t.test(!sti.empty(), "Resize - increase size greatly, check empty");

    noErrors = true;
    for (i = 0; i < theSize2; ++i)
    {
        if (sti[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Resize - increase size greatly, check values");

    sti.resize(0);
    t.test(sti.size() == 0, "Resize - size zero, check size");
    t.test(sti.empty(), "Resize - size zero, check empty");
}


// test_class_TSmArray_begin_end
// Test suite for class TSmArray, functions begin & end
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_TSmArray_begin_end(Tester & t)
{
    std::cout << "Test Suite: class TSmArray - functions begin & end"
              << std::endl;

    const int theSize = 10;
    bool noErrors;      // True if no errors encountered
    int i;              // Loop index
    int * iter;         // iterator
    const int * citer;  // const_iterator

    TSmArray<int> sti(theSize);
    for (iter = sti.begin(), i = 0; iter != sti.end(); ++iter, ++i)
        *iter = 15 - i * i;

    // Non-const test
    t.test(sti.begin() != sti.end(), "begin/end - inequality (non-const)");
    t.test(sti.end() - sti.begin() == theSize,
        "begin/end - check difference (non-const)");
    noErrors = true;
    for (iter = sti.begin(), i = 0; iter != sti.end(); ++iter, ++i)
    {
        if (*iter != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "begin/end - check values (non-const)");

    // Dereference and use to assign
    *(sti.begin()) = 1001;
    *(sti.end() - 1) = 1002;
    noErrors = true;
    for (iter = sti.begin(), i = 0; iter != sti.end(); ++iter, ++i)
    {
        if (*iter != ((i == 0) ? 1001 : (i == theSize-1) ? 1002 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "begin/end - check modification of values (non-const)");

    // Make const version, no copy
    const TSmArray<int> & stiRef = sti;

    // Const test
    t.test(stiRef.begin() != stiRef.end(), "begin/end - inequality (const)");
    t.test(stiRef.end() - stiRef.begin() == theSize,
        "begin/end - check difference (const)");
    noErrors = true;
    for (citer = stiRef.begin(), i = 0; citer != stiRef.end(); ++citer, ++i)
    {
        if (*citer != ((i == 0) ? 1001 : (i == theSize-1) ? 1002 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "begin/end - check values (const)");

    const TSmArray<int> sti2;
    t.test(sti2.begin() == sti2.end(),
        "begin/end - equality, default constructed (const)");
    TSmArray<int> sti3;
    t.test(sti3.begin() == sti3.end(),
        "begin/end - equality, default constructed (non-const)");
}


// test_class_TSmArray_insert_remove
// Test suite for class TSmArray, functions insert & remove
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_TSmArray_insert_remove(Tester & t)
{
    std::cout << "Test Suite: class TSmArray - functions insert & remove"
              << std::endl;

    TSmArray<int>::iterator iter;
    bool correctReturn;  // For testing return values
    bool correctValues;  // For testing array values

    const int SIZE = 15;
    int arr1[SIZE] = { 10, 1, 15, 7, 13, 2, 11, 12, 6, 3, 8, 4, 15, 5, 9 };

    TSmArray<int> sti(SIZE);
    std::copy(arr1, arr1+SIZE, sti.begin());

    iter = sti.insert(sti.begin()+2, 101);
    int arr2[SIZE+1] =
        { 10, 1, 101, 15, 7, 13, 2, 11, 12, 6, 3, 8, 4, 15, 5, 9 };
    t.test(sti.size() == SIZE+1, "insert - check size");
    t.test(!sti.empty(), "insert - check empty");
    t.test(std::equal(sti.begin(), sti.end(), arr2), "insert - check values");
    t.test(iter == sti.begin()+2, "insert - check return value");

    iter = sti.remove(sti.begin()+5);
    int arr3[SIZE] = { 10, 1, 101, 15, 7, 2, 11, 12, 6, 3, 8, 4, 15, 5, 9 };
    t.test(sti.size() == SIZE, "remove - check size");
    t.test(!sti.empty(), "remove - check empty");
    t.test(std::equal(sti.begin(), sti.end(), arr3), "remove - check values");
    t.test(iter == sti.begin()+5, "remove - check return value");

    iter = sti.insert(sti.begin(), 102);
    int arr4[SIZE+1] =
        { 102, 10, 1, 101, 15, 7, 2, 11, 12, 6, 3, 8, 4, 15, 5, 9 };
    t.test(sti.size() == SIZE+1, "insert at beginning - check size");
    t.test(!sti.empty(), "insert at beginning - check empty");
    t.test(std::equal(sti.begin(), sti.end(), arr4),
        "insert at beginning - check values");
    t.test(iter == sti.begin(), "insert at beginning - check return value");

    iter = sti.insert(sti.end(), 103);
    int arr5[SIZE+2] =
        { 102, 10, 1, 101, 15, 7, 2, 11, 12, 6, 3, 8, 4, 15, 5, 9, 103 };
    t.test(sti.size() == SIZE+2, "insert at end - check size");
    t.test(!sti.empty(), "insert at end - check empty");
    t.test(std::equal(sti.begin(), sti.end(), arr5),
        "insert at end - check values");
    t.test(iter == sti.end()-1, "insert at end - check return value");

    iter = sti.remove(sti.begin());
    int arr6[SIZE+1] =
        { 10, 1, 101, 15, 7, 2, 11, 12, 6, 3, 8, 4, 15, 5, 9, 103 };
    t.test(sti.size() == SIZE+1, "remove at beginning - check size");
    t.test(!sti.empty(), "remove at beginning - check empty");
    t.test(std::equal(sti.begin(), sti.end(), arr6),
        "remove at beginning - check values");
    t.test(iter == sti.begin(), "remove at beginning - check return value");

    iter = sti.remove(sti.end()-1);
    int arr7[SIZE] = { 10, 1, 101, 15, 7, 2, 11, 12, 6, 3, 8, 4, 15, 5, 9 };
    t.test(sti.size() == SIZE, "remove at end - check size");
    t.test(!sti.empty(), "remove at end - check empty");
    t.test(std::equal(sti.begin(), sti.end(), arr7),
        "remove at end - check values");
    t.test(iter == sti.end(), "remove at end - check return value");

    // Multiple insert @ beginning
    const int SIZE2 = 5000;
    TSmArray<int> sti2;
    correctReturn = true;
    for (int i1 = 0; i1 < SIZE2; ++i1)
    {
        iter = sti2.insert(sti2.begin(), SIZE2-1-i1);
        if (iter != sti2.begin())
            correctReturn = false;
    }
    correctValues = true;
    for (int i2 = 0; i2 < SIZE2; ++i2)
    {
        if (sti2[i2] != i2)
            correctValues = false;
    }
    t.test(correctValues, "multiple insert @ beginning - check values");
    t.test(correctReturn, "multiple insert @ beginning - check return values");

    // Multiple insert @ end
    const int SIZE3 = 500000;
    TSmArray<int> sti3;
    correctReturn = true;
    for (int i1 = 0; i1 < SIZE3; ++i1)
    {
        iter = sti3.insert(sti3.end(), 100-i1);
        if (iter != sti3.end()-1)
            correctReturn = false;
    }
    correctValues = true;
    for (int i2 = 0; i2 < SIZE3; ++i2)
    {
        if (sti3[i2] != 100-i2)
            correctValues = false;
    }
    t.test(correctValues, "multiple insert @ end - check values");
    t.test(correctReturn, "multiple insert @ end - check return values");
}


// test_class_TSmArray_swap
// Test suite for class TSmArray, function swap
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_TSmArray_swap(Tester & t)
{
    std::cout << "Test Suite: class TSmArray - function swap" << std::endl;

    const int SIZE1 = 15;
    int arr1[SIZE1] = { 10, 1, 15, 7, 13, 2, 11, 12, 6, 3, 8, 4, 15, 5, 9 };
    TSmArray<int> sti1(SIZE1);
    std::copy(arr1, arr1+SIZE1, sti1.begin());

    const int SIZE2 = 5;
    int arr2[SIZE2] = { 6, 2, 3, 5, 1 };
    TSmArray<int> sti2(SIZE2);
    std::copy(arr2, arr2+SIZE2, sti2.begin());

    sti1.swap(sti2);

    // Check size & values of swapped TSmArray's
    t.test(sti1.size() == SIZE2, "swap - check size #1");
    t.test(sti2.size() == SIZE1, "swap - check size #2");
    t.test(std::equal(sti1.begin(), sti1.end(), arr2),
        "swap - check values #1");
    t.test(std::equal(sti2.begin(), sti2.end(), arr1),
        "swap - check values #2");
}


// test_class_TSmArray_ctor_dctor_count
// Test suite for class TSmArray, number of class to item type
//  ctor, dctor.
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_TSmArray_ctor_dctor_count(Tester & t)
{
    std::cout << "Test Suite: class TSmArray - ctor, dctor count" << std::endl;

    // Check number of value type ctor/dctor calls
    //  on array creation & destruction
    Counter::reset();
    int ctorCallCount;  // Holds number of default ctor calls
    { // Block, so we get dctor calls before function ends
        const TSmArray<Counter> stt(10);
        ctorCallCount = Counter::getCtorCount();
        t.test(ctorCallCount >= 10,
            "Counting default ctor calls due to array creation");

        Counter::reset();
    }
    t.test(Counter::getDctorCount() == ctorCallCount,
        "Counting dctor calls due to destruction");

    // Check number of value type ctor/dctor calls on swap
    TSmArray<Counter> stt3(10);
    TSmArray<Counter> stt4(10);
    Counter::reset();
    stt3.swap(stt4);
    t.test(Counter::getCtorCount() == 0,
        "Swap should generate no ctor calls");
    t.test(Counter::getDctorCount() == 0,
        "Swap should generate no dctor calls");
    t.test(Counter::getAssnCount() == 0,
        "Swap should generate no assignment calls");

    // Check number of value type dctor calls on reallocate-and-copy
    const int theSize1 = 10;
    Counter::reset();
    TSmArray<Counter> stt5(theSize1);
    ctorCallCount = Counter::getCtorCount();
    Counter::reset();
    stt5.resize(ctorCallCount + 100000);  // resize larger than capacity
    t.test(Counter::getDctorCount() == ctorCallCount,
        "Reallocate-and-copy - deallocate old data");
}


// test_class_TSmArray_exceptions
// Test suite for class TSmArray, exception handling
//  ctor, dctor.
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_TSmArray_exceptions(Tester & t)
{

    std::cout << "Test Suite: class TSmArray - exceptions" << std::endl;

    Counter::setCopyThrow(true);

    const std::size_t theSize1 = 10;
    const std::size_t bumpup = 100000;
    bool gotException;
    bool correctType;

    Counter::reset(true);
    TSmArray<Counter> stt1(theSize1);
    int oldCapacity = Counter::getCtorCount();
    // Copy Constructor Tests
    Counter::reset(true);
    gotException = false;
    correctType = false;
    try
    {
        // Copy construction. Should throw.
        const TSmArray<Counter> stt2(stt1);
    }
    catch (std::runtime_error & e)
    {
        gotException = true;
        correctType = true;
        t.test(std::string(e.what()) == "A",
            "Exceptions - copy ctor can fail - exception message");
    }
    catch (...)
    {
        gotException = true;
        correctType = false;
    }
    t.test(correctType, "Exceptions - copy ctor can fail - exception type");
    t.test(gotException, "Exceptions - copy ctor can fail - exception thrown");
    t.test(Counter::getCtorCount() == Counter::getDctorCount(),
        "Exceptions - copy ctor has no memory leak");

    // Copy Assignment Tests
    Counter::reset(true);
    gotException = false;
    correctType = false;
    try
    {
        // Copy assignment. Should throw.
        TSmArray<Counter> stt3;
        stt3 = stt1;
    }
    catch (std::runtime_error & e)
    {
        gotException = true;
        correctType = true;
        t.test(std::string(e.what()) == "A",
            "Exceptions - copy assn can fail - exception message");
    }
    catch (...)
    {
        gotException = true;
        correctType = false;
    }
    t.test(correctType, "Exceptions - copy assn can fail - exception type");
    t.test(gotException, "Exceptions - copy assn can fail - exception thrown");
    t.test(Counter::getCtorCount() == Counter::getDctorCount(),
        "Exceptions - copy assn has no memory leak");

    // Resize Tests
    Counter::reset(true);
    gotException = false;
    correctType = false;
    try
    {
        // Resize larger. Should throw, due to reallocate-and-copy.
        stt1.resize(oldCapacity + bumpup);
    }
    catch (std::runtime_error & e)
    {
        gotException = true;
        correctType = true;
        t.test(std::string(e.what()) == "A",
            "Exceptions - resize larger can fail - exception message");
        t.test(stt1.size() == theSize1,
            "Exceptions - resize larger can fail - Strong Guarantee");
    }
    catch (...)
    {
        gotException = true;
        correctType = false;
    }
    t.test(correctType,
        "Exceptions - resize larger can fail - exception type");
    t.test(gotException,
        "Exceptions - resize larger can fail - exception thrown");
    t.test(Counter::getCtorCount() == Counter::getDctorCount(),
        "Exceptions - resize larger has no memory leak");

    gotException = false;
    try
    {
        // Resize - not larger. Should NOT throw.
        stt1.resize(theSize1);
    }
    catch (...)
    {
        gotException = true;
    }
    t.test(!gotException, "Exceptions - resize, not larger, cannot fail");

    // Swap Tests
    gotException = false;
    try
    {
        TSmArray<Counter> stt4;
        stt4.swap(stt1);
    }
    catch (...)
    {
        gotException = true;
    }
    t.test(!gotException, "Exceptions - swap cannot fail");
}


// test_class_TSmArray
// Test suite for class TSmArray
// Uses other test-suite functions
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_TSmArray(Tester & t)
{
    // Do all the test suites
    std::cout << "TEST SUITES FOR CLASS TSmArray" << std::endl;
    test_class_TSmArray_types(t);
    test_class_TSmArray_size_empty_and_ctor_from_size(t);
    test_class_TSmArray_default_ctor(t);
    test_class_TSmArray_bracket_op(t);
    test_class_TSmArray_copy_ctor(t);
    test_class_TSmArray_copy_assn(t);
    test_class_TSmArray_resize(t);
    test_class_TSmArray_begin_end(t);
    test_class_TSmArray_insert_remove(t);
    test_class_TSmArray_swap(t);
    test_class_TSmArray_ctor_dctor_count(t);
    test_class_TSmArray_exceptions(t);
}


// ************************************************************************
// Main program
// ************************************************************************


// main
// Runs class Birthday test suite, prints results to cout.
int main()
{
    Tester t;
    test_class_TSmArray(t);

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

