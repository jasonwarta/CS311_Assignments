// ssarray_test.cpp
// VERSION 2
// Glenn G. Chappell
// 19 Sep 2015
// Updated: 24 Sep 2015
//
// For CS 311 Fall 2015
// Test program for class template SSArray
// Used in Assignment 2, Exercise A

// Includes for code to be tested
#include "ssarray.h"    // For class SSArray
#include "ssarray.h"    // Double inclusion test

// Includes for testing package & code common to all test programs
#include <iostream>     // for std::cout, std::endl, std::cin
#include <string>       // for std::string
#include <stdexcept>    // for std::runtime_error

// Additional includes for this test program
#include <cstddef>      // for std::size_t, std::ptrdiff_t
#include <vector>       // for std::vector
#include <sstream>      // for std::ostringstream


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


// test_class_SSArray_types
// Test suite for class template SSArray, types
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SSArray_types(Tester & t)
{
    std::cout << "Test Suite: class template SSArray - types" << std::endl;

    bool correctType;  // result of type checking

    // value_type test #1: int
    SSArray<int>::value_type i1 = 0;
    correctType = TypeCheck<int>::check(i1);
    t.test(correctType, "value_type test #1");

    // value_type test #2: double
    SSArray<double>::value_type d1 = 0.;
    correctType = TypeCheck<double>::check(d1);
    t.test(correctType, "value_type test #2");

    // value_type check modifiability (only needs to compile)
    SSArray<double>::value_type d2;
    d2 = 0.;
    t.test(true, "value_type check modifiability");

    // size_type test
    SSArray<Counter>::size_type s1 = 0;
    correctType = TypeCheck<std::size_t>::check(s1)
               || TypeCheck<std::ptrdiff_t>::check(s1);
    t.test(correctType, "size_type test");

    // size_type check modifiability (only needs to compile)
    SSArray<Counter>::size_type s2;
    s2 = 0;
    t.test(true, "size_type check modifiability");
}


// test_class_SSArray_size_and_ctor_from_size
// Test suite for class template SSArray, function size and ctor from size
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SSArray_size_and_ctor_from_size(Tester & t)
{
    std::cout << "Test Suite: class template SSArray - "
              << "function size, ctor from size"
              << std::endl;

    bool correctType;  // result of type checking

    const SSArray<int> tai1(1);

    correctType = TypeCheck<SSArray<int>::size_type>::check(tai1.size());
    t.test(correctType, "size, return type");

    t.test(tai1.size() == 1, "ctor from size (const) #1, check size");

    const SSArray<int> tai2(10);
    t.test(tai2.size() == 10, "ctor from size (const) #2, check size");

    const SSArray<double> tad(100);
    t.test(tad.size() == 100, "ctor from size (const) #3, check size");

    SSArray<int> tai3(20);
    t.test(tai3.size() == 20, "ctor from size (non-const), check size");

    const SSArray<int> tai4(0);
    t.test(tai4.size() == 0, "ctor from size (size 0), check size");
}


// test_class_SSArray_default_ctor
// Test suite for class template SSArray, default ctor
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SSArray_default_ctor(Tester & t)
{
    std::cout << "Test Suite: class template SSArray - default ctor"
              << std::endl;

    const SSArray<int> tai1;
    t.test(tai1.size() == 10, "default ctor, size");
}


// test_class_SSArray_bracket_op
// Test suite for class template SSArray, bracket operator
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SSArray_bracket_op(Tester & t)
{
    std::cout << "Test Suite: class template SSArray, bracket operator"
              << std::endl;

    bool correctType;  // result of type checking

    const int theSize = 10;
    bool noErrors;  // True if no errors encountered
    int i;          // Counter

    SSArray<double> tad1;
    correctType = TypeCheck<SSArray<double>::value_type>::check(tad1[1]);
    t.test(correctType, "Bracket operator (non-const), return type");

    SSArray<int> tai(theSize);
    for (i = 0; i < theSize; ++i)
        tai[i] = 15 - i * i;

    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (tai[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Bracket operator (non-const) #1");

    tai[2] = 1000;
    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (tai[i] != ((i == 2) ? 1000 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "Bracket operator (non-const) #2");

    // Make const version, no copy
    const SSArray<int> & taiRef = tai;

    const SSArray<double> tad2;
    correctType = TypeCheck<SSArray<double>::value_type>::check(tad2[1]);
    t.test(correctType, "Bracket operator (const), return type");

    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (taiRef[i] != ((i == 2) ? 1000 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "Bracket operator (const)");

}


// test_class_SSArray_ctor_from_size_and_val
// Test suite for class template SSArray, ctor from size & value
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SSArray_ctor_from_size_and_val(Tester & t)
{
    std::cout << "Test Suite: class template SSArray - "
              << "ctor from size & value"
              << std::endl;

    const int theSize = 1000;
    bool noErrors;  // True if no errors encountered
    const double val = -3.2;

    SSArray<double> tad(theSize, val);

    // check size
    t.test(tad.size() == theSize, "Ctor from size & value - check size");

    // check values
    typedef SSArray<double>::size_type ST;
    noErrors = true;
    for (auto i = static_cast<ST>(0);
         i < tad.size();
         ++i)
    {
        if (tad[i] != val)
            noErrors = false;
    }
    t.test(noErrors, "Ctor from size & value - check values");
}


// test_class_SSArray_copy_ctor
// Test suite for class template SSArray, copy ctor
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SSArray_copy_ctor(Tester & t)
{
    std::cout << "Test Suite: class template SSArray - copy ctor"
              << std::endl;

    const int theSize = 10;
    bool noErrors;  // True if no errors encountered
    int i;          // Counter

    SSArray<int> tai(theSize);
    for (i = 0; i < theSize; ++i)
        tai[i] = 15 - i * i;

    // Make const version, no copy
    const SSArray<int> & taiRef = tai;
    // Make copy (copy ctor)
    SSArray<int> taiCopy(taiRef);

    t.test(taiCopy.size() == theSize, "Copy ctor - check size, copy");

    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (taiCopy[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Copy ctor - check values, copy");

    // Change original
    tai[2] = 1000;

    // Check original
    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (tai[i] != ((i == 2) ? 1000 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors,
      "Copy ctor - change original, check values, original");

    // Check copy
    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (taiCopy[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Copy ctor - change original, check values, copy");

    // Change copy
    taiCopy[3] = 2000;

    // Check original
    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (tai[i] != ((i == 2) ? 1000 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "Copy ctor - change copy, check values, original");

    // Check copy
    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (taiCopy[i] != ((i == 3) ? 2000 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "Copy ctor - change copy, check values, copy");
}


// test_class_SSArray_copy_assn
// Test suite for class template SSArray, copy assignment
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SSArray_copy_assn(Tester & t)
{
    std::cout << "Test Suite: class template SSArray - copy assignment"
              << std::endl;

    bool correctType;  // result of type checking

    const int theSize = 10;
    bool noErrors;  // True if no errors encountered
    int i;          // Counter

    SSArray<int> tai(theSize);
    for (i = 0; i < theSize; ++i)
        tai[i] = 15 - i * i;

    // Make const version, no copy
    const SSArray<int> & taiRef = tai;
    // Make copy (copy ctor)
    SSArray<int> taiCopy(1);
    taiCopy = taiRef;

    // Do copy assignment & check return type
    correctType = TypeCheck<SSArray<int> >::check(taiCopy = taiRef);
    t.test(correctType, "Copy assn - return type");

    t.test(taiCopy.size() == theSize, "Copy assn - check size, copy");

    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (taiCopy[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Copy assn - check values, copy");

    // Change original
    tai[2] = 1000;

    // Check original
    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (tai[i] != ((i == 2) ? 1000 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors,
      "Copy assn - change original, check values, original");

    // Check copy
    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (taiCopy[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Copy assn - change original, check values, copy");

    // Change copy
    taiCopy[3] = 2000;

    // Check original
    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (tai[i] != ((i == 2) ? 1000 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "Copy assn - change copy, check values, original");

    // Check copy
    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (taiCopy[i] != ((i == 3) ? 2000 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "Copy assn - change copy, check values, copy");

    // Check self-assignment
    taiCopy = taiCopy;

    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (taiCopy[i] != ((i == 3) ? 2000 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "Copy assn - values after self-assignment");
}


// test_class_SSArray_begin_end
// Test suite for class template SSArray, functions begin & end
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SSArray_begin_end(Tester & t)
{
    std::cout << "Test Suite: class template SSArray - "
              << "functions begin & end"
              << std::endl;

    bool correctType;  // result of type checking

    const int theSize = 10;
    bool noErrors;      // True if no errors encountered
    int i;              // Counter
    int * iter;         // iterator
    const int * citer;  // const_iterator

    SSArray<int> tai(theSize);
    for (iter = tai.begin(), i = 0; iter != tai.end(); ++iter, ++i)
        *iter = 15 - i * i;

    // Non-const test
    SSArray<double> tad1;

    correctType =
      TypeCheck<SSArray<double>::value_type *>::check(tad1.begin());
    t.test(correctType, "begin (non-const), return type");
    
    correctType =
      TypeCheck<SSArray<double>::value_type *>::check(tad1.end());
    t.test(correctType, "end (non-const), return type");

    t.test(tai.begin() != tai.end(), "begin/end - inequality (non-const)");
    t.test (tai.end() - tai.begin() == theSize,
      "begin/end - check difference (non-const)");
    noErrors = true;
    for (iter = tai.begin(), i = 0; iter != tai.end(); ++iter, ++i)
    {
        if (*iter != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "begin/end - check values (non-const)");

    // Make const version, no copy
    const SSArray<int> & taiRef = tai;

    // Const test
    const SSArray<double> tad2;

    correctType =
      TypeCheck<const SSArray<double>::value_type *>::check(tad2.begin());
    t.test(correctType, "begin (const), return type");
    
    correctType =
      TypeCheck<const SSArray<double>::value_type *>::check(tad2.end());
    t.test(correctType, "end (const), return type");
    
    t.test(taiRef.end() - taiRef.begin() == theSize,
      "begin/end - check difference (const)");
    noErrors = true;
    for (citer = taiRef.begin(), i = 0;
         citer != taiRef.end();
         ++citer, ++i)
    {
        if (*citer != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "begin/end - check values (const)");
}


// test_class_SSArray_equality_comparisons
// Test suite for class template SSArray, comparisons ==, !=
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SSArray_equality_comparisons(Tester & t)
{
    std::cout << "Test Suite: class template SSArray - "
              << "equality comparisons"
              << std::endl;

    bool correctType;  // result of type checking

    const int theSize = 10;
    int i;          // Counter

    SSArray<int> tai1(theSize);
    for (i = 0; i < theSize; ++i)
        tai1[i] = 15 - i * i;
    const SSArray<int> & tai1Ref = tai1;
    SSArray<int> tai1Copy(tai1Ref);
    SSArray<int> tai2(theSize-1);
    for (i = 0; i < theSize-1; ++i)
        tai2[i] = 15 - i * i;
    const SSArray<int> & tai2Ref = tai2;
    
    // operator== return type
    correctType = TypeCheck<bool>::check(tai1 == tai1Copy);
    t.test(correctType, "operator==, return type");

    // operator!= return type
    correctType = TypeCheck<bool>::check(tai1 != tai1Copy);
    t.test(correctType, "operator!=, return type");

    // Check equality of copies
    t.test(tai1 == tai1Copy, "Equality of copies");

    // Check inequality of copies
    t.test(!(tai1 != tai1Copy), "Inequality of copies");

    // Check equality of different sizes #1
    //  (compilation checks constness of op==)
    t.test(!(tai1Ref == tai2Ref), "Equality of different sizes #1");

    // Check inequality of different sizes #1
    //  (compilation checks constness of op!=)
    t.test(tai1Ref != tai2Ref, "Inequality of different sizes #1");

    // Check equality of different sizes #2
    t.test(!(tai2Ref == tai1Ref), "Equality of different sizes #2");

    // Check inequality of different sizes #2
    t.test(tai2Ref != tai1Ref, "Inequality of different sizes #2");

    // Modify copy
    ++tai1Copy[theSize-1];

    // Check equality of modification of copy
    t.test(!(tai1 == tai1Copy), "Equality of modification of copy");

    // Check inequality of modification of copy
    t.test(tai1 != tai1Copy, "Inequality of modification of copy");
}


// test_class_SSArray_order_comparisons
// Test suite for class template SSArray, comparisons <, <=, >, >=
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SSArray_order_comparisons(Tester & t)
{
    std::cout << "Test Suite: class template SSArray - order comparisons"
              << std::endl;

    bool correctType;  // result of type checking

    // Make vector of 10 SSArray<int> objects, in ascending order
    auto NUM_ARRAYS = static_cast<std::size_t>(10);
    std::vector<SSArray<int> > vv(NUM_ARRAYS);

    vv[0] = SSArray<int>(0);

    vv[1] = SSArray<int>(1);
    vv[1][0] = -1;

    vv[2] = SSArray<int>(2);
    vv[2][0] = -1;
    vv[2][1] = -1;

    vv[3] = SSArray<int>(99);
    for (auto & x : vv[3])
        x = -1;
        
    vv[4] = SSArray<int>(100);
    for (auto & x : vv[4])
        x = -1;

    vv[5] = SSArray<int>(100);
    for (auto & x : vv[5])
        x = -1;
    vv[5][90] = 1;

    vv[6] = SSArray<int>(2);
    vv[6][0] = -1;
    vv[6][1] = 1;

    vv[7] = SSArray<int>(1);
    vv[7][0] = 1;

    vv[8] = SSArray<int>(2);
    vv[8][0] = 1;
    vv[8][1] = -1;

    vv[9] = SSArray<int>(2);
    vv[9][0] = 1;
    vv[9][1] = 1;

    // operator< return type
    correctType = TypeCheck<bool>::check(vv[0] < vv[1]);
    t.test(correctType, "operator<, return type");

    // operator<= return type
    correctType = TypeCheck<bool>::check(vv[0] <= vv[1]);
    t.test(correctType, "operator<=, return type");

    // operator> return type
    correctType = TypeCheck<bool>::check(vv[0] > vv[1]);
    t.test(correctType, "operator>, return type");

    // operator>= return type
    correctType = TypeCheck<bool>::check(vv[0] >= vv[1]);
    t.test(correctType, "operator>=, return type");

    for (std::size_t i = 0; i < NUM_ARRAYS; ++i)
    {
        for (std::size_t j = 0; j < NUM_ARRAYS; ++j)
        {
            std::ostringstream os;
            os << ", test " << i << "," << j;
            t.test((vv[i] < vv[j]) == (i < j),
              "operator<" + os.str());
            t.test((vv[i] <= vv[j]) == (i <= j),
              "operator<=" + os.str());
            t.test((vv[i] > vv[j]) == (i > j),
              "operator>" + os.str());
            t.test((vv[i] >= vv[j]) == (i >= j),
              "operator>=" + os.str());
            t.test((vv[i] == vv[j]) == (i == j),
              "operator==" + os.str());
            t.test((vv[i] != vv[j]) == (i != j),
              "operator!=" + os.str());
        }
    }
}


// test_class_SSArray_ctor_dctor_count
// Test suite for class template SSArray, number of class to item type
//  ctor, dctor.
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SSArray_ctor_dctor_count(Tester & t)
{
    std::cout << "Test Suite: class template SSArray - ctor, dctor count"
              << std::endl;

    // Check number of value type ctor/dctor calls
    //  on array creation & destruction
    Counter::reset();
    { // Block, so we get dctor calls before function ends
        const SSArray<Counter> tacc(10);

        t.test(Counter::getCtorCount() == 10,
          "Counting default ctor calls due to array creation");

        Counter::reset();
    }
    t.test(Counter::getDctorCount() == 10,
      "Counting dctor calls due to destruction");

/*
    // Check correct number of value type ctor & dctor calls
    //  on self-assignment
    SSArray<Counter> tacc2(10);
    Counter::reset();
    tacc2 = tacc2;
    int i1 = Counter::getCtorCount() + Counter::getDctorCount();
    t.test(i1 == 0 || i1 == 20, "Self-assignment ctor/dctor calls");
*/
}


// test_class_SSArray
// Test suite for class template SSArray
// Uses other test-suite functions
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SSArray(Tester & t)
{
    // Do all the test suites
    std::cout << "TEST SUITES FOR CLASS SSArray" << std::endl;
    test_class_SSArray_types(t);
    test_class_SSArray_size_and_ctor_from_size(t);
    test_class_SSArray_default_ctor(t);
    test_class_SSArray_bracket_op(t);
    test_class_SSArray_ctor_from_size_and_val(t);
    test_class_SSArray_copy_ctor(t);
    test_class_SSArray_copy_assn(t);
    test_class_SSArray_begin_end(t);
    test_class_SSArray_equality_comparisons(t);
    test_class_SSArray_order_comparisons(t);
    test_class_SSArray_ctor_dctor_count(t);
}


// ************************************************************************
// Main program
// ************************************************************************


// main
// Runs class SSArray test suite, prints results to cout.
int main()
{
    Tester t;
    test_class_SSArray(t);

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

