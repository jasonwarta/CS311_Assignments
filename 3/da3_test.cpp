// da3_test.cpp
// Glenn G. Chappell
// 27 Sep 2015
//
// For CS 311 Fall 2015
// Test program for Assignment 3 Functions & Function Templates
// Used in Assignment 3, Exercises A, B, C, D

// Includes for code to be tested
#include "da3.h"        // For Assignment 3 Functions & Templates
#include "da3.h"        // Double inclusion test

// Includes for testing package & code common to all test programs
#include <iostream>     // for std::cout, std::endl, std::cin
#include <string>       // for std::string
#include <stdexcept>    // for std::runtime_error

// Additional includes for this test program
#include <sstream>      // for std::ostringstream
#include <stdexcept>    // for std::out_of_range
#include <iterator>     // for std::advance
#include <vector>       // for std::vector
#include <deque>        // for std::deque


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


// thisThrows
// Throws a std::runtime_error. For passing to function doesItThrow.
// Pre: None.
// Post: None.
// Will throw std::runtime_error.
void thisThrows()
{
    throw std::runtime_error("Hi!");
}

// thisThrowsStrangely
// Throws an int. For passing to function doesItThrow.
// Pre: None.
// Post: None.
// Will throw int.
void thisThrowsStrangely()
{
    throw -42;
}

// thisDoesNotThrow
// Does nothing. For passing to function doesItThrow.
// Pre: None.
// Post: None.
// Does not throw.
void thisDoesNotThrow()
{}


// class FuncObj
// Class for do-nothing function objects.
// Do "FuncObj x;", and then we can do "x();".
// The operator() returns nothing and does not throw.
// Invariants: None.
class FuncObj {

// ***** FuncObj: ctors, dctor, op= *****
public:

    // Compiler-generated default ctor, copy ctor, op=, dctor are used

// ***** FuncObj: public operators *****
public:

    // operator()
    // Makes an object of this class callable like a function.
    // Pre: None.
    // Post: None.
    // Does not throw.
    void operator()() const
    {}

};  // end class FuncObj


// gcd_single_test
// Helper function for testing function gcd
// Pre:
//     a, b are nonnegative, not both zero.
//     c is the GCD of a, b.
// Post:
//     gcd(a, b) == c has been tested.
//     Pass/fail status has been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee
void gcd_single_test(Tester & t,
                     int a,
                     int b,
                     int c)
{
    std::ostringstream oss;
    int result = gcd(a, b);
    oss << "gcd(" << a << ", " << b << ") = " << c;
    if (c != result)
        oss << " [actual return value: " << result << "]";
    t.test(result == c, oss.str());
}


// ************************************************************************
// Test Suite Functions
// ************************************************************************


// test_function_listItem
// Test suite for function template listItem
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_function_listItem(Tester & t)
{
    std::cout << "Test Suite: function template listItem (Exercise A)"
              << std::endl;

    LLNode<int> * headi;     // Head ptr for all int Linked Lists
    LLNode<double> * headd;  // Head ptr for all double Linked Lists
    
    // Empty list tests
    headi = 0;

    // Empty list, index 0
    try
    {
        /* int ii = */ listItem(headi, 0);
        t.test(false, "Empty list, index 0 - throws out_of_range");
    }
    catch (std::out_of_range & e)
    {
        t.test(true, "Empty list, index 0 - throws out_of_range");
        t.test(std::string("") != e.what(),
            "Empty list, index 0 - what() nonempty");
    }
    catch (...)
    {
        t.test(false, "Empty list, index 0 - throws out_of_range");
    }

    // Empty list, index 1
    try
    {
        /* int ii = */ listItem(headi, 1);
        t.test(false, "Empty list, index 1 - throws out_of_range");
    }
    catch (std::out_of_range & e)
    {
        t.test(true, "Empty list, index 1 - throws out_of_range");
        t.test(std::string("") != e.what(), "Empty list, index 1 - what() nonempty");
    }
    catch (...)
    {
        t.test(false, "Empty list, index 1 - throws out_of_range");
    }

    /*
    // Empty list, index -1
    try
    {
        int ii = listItem(headi, -1);
        t.test(false, "Empty list, index -1 - throws out_of_range");
    }
    catch (std::out_of_range & e)
    {
        t.test(true, "Empty list, index -1 - throws out_of_range");
        t.test(std::string("") != e.what(),
            "Empty list, index -1 - what() nonempty");
    }
    catch (...)
    {
        t.test(false, "Empty list, index -1 - throws out_of_range");
    }
    delete headi;  // Not really necessary, but why not?
    */

    // Size 1 list tests
    headd = 0;
    headd = new LLNode<double>(3.2, headd);

    // List of size 1, index 0
    try
    {
        bool correctType = TypeCheck<double>::check(listItem(headd, 0));
        t.test(correctType, "List of size 1, index 0 - return type");
        double dd = listItem(headd, 0);
        t.test(true, "List of size 1, index 0 - does not throw");
        t.test(dd == 3.2, "List of size 1, index 0 - return value");
    }
    catch (...)
    {
        t.test(false, "List of size 1, index 0 - does not throw");
    }

    // List of size 1, index 1
    try
    {
        listItem(headd, 1);
        t.test(false, "List of size 1, index 1 - throws out_of_range");
    }
    catch (std::out_of_range & e)
    {
        t.test(true, "List of size 1, index 1 - throws out_of_range");
        t.test(std::string("") != e.what(), "List of size 1, index 1 - what() nonempty");
    }
    catch (...)
    {
        t.test(false, "List of size 1, index 1 - throws out_of_range");
    }

    /*
    // Empty list, index -1
    try
    {
        listItem(headd, -1);
        t.test(false, "List of size 1, index -1 - throws out_of_range");
    }
    catch (std::out_of_range & e)
    {
        t.test(true, "List of size 1, index -1 - throws out_of_range");
        t.test(std::string("") != e.what(),
            "List of size 1, index -1 - what() nonempty");
    }
    catch (...)
    {
        t.test(false, "List of size 1, index -1 - throws out_of_range");
    }
    delete headd;
    */

    // Size 9 list tests
    headi = 0;
    headi = new LLNode<int>(64, headi);
    headi = new LLNode<int>(49, headi);
    headi = new LLNode<int>(36, headi);
    headi = new LLNode<int>(25, headi);
    headi = new LLNode<int>(16, headi);
    headi = new LLNode<int>(9, headi);
    headi = new LLNode<int>(4, headi);
    headi = new LLNode<int>(1, headi);
    headi = new LLNode<int>(0, headi);

    // List of size 9, index 0
    try
    {
        bool correctType = TypeCheck<int>::check(listItem(headi, 0));
        t.test(correctType, "Larger list, index 0 - return type");
        int ii = listItem(headi, 0);
        t.test(true, "Larger list, index 0 - does not throw");
        t.test(ii == 0, "Larger list, index 0 - return value");
    }
    catch (...)
    {
        t.test(false, "Larger list, index 0 - does not throw");
    }

    // List of size 9, index 5
    try
    {
        bool correctType = TypeCheck<int>::check(listItem(headi, 5));
        t.test(correctType, "Larger list, index in middle - return type");
        int ii = listItem(headi, 5);
        t.test(true, "Larger list, index in middle - does not throw");
        t.test(ii == 25, "Larger list, index in middle - return value");
    }
    catch (...)
    {
        t.test(false, "Larger list, index in middle - does not throw");
    }

    // List of size 9, index 8
    try
    {
        bool correctType = TypeCheck<int>::check(listItem(headi, 8));
        t.test(correctType, "Larger list, last index - return type");
        int ii = listItem(headi, 8);
        t.test(true, "Larger list, last index - does not throw");
        t.test(ii == 64, "Larger list, last index - return value");
    }
    catch (...)
    {
        t.test(false, "Larger list, last index - does not throw");
    }

    /*
    // Empty list, index -1
    try
    {
        listItem(headi, -1);
        t.test(false, "Larger list, index -1 - throws out_of_range");
    }
    catch (std::out_of_range & e)
    {
        t.test(true, "Larger list, index -1 - throws out_of_range");
        t.test(std::string("") != e.what(),
            "Larger list, index -1 - what() nonempty");
    }
    catch (...)
    {
        t.test(false, "Larger list, index -1 - throws out_of_range");
    }
    */

    // List of size 9, index 9
    try
    {
        listItem(headi, 9);
        t.test(false, "Larger list, index beyond end - throws out_of_range");
    }
    catch (std::out_of_range & e)
    {
        t.test(true, "Larger list, index beyond end - throws out_of_range");
        t.test(std::string("") != e.what(),
            "Larger list, index beyond end - what() nonempty");
    }
    catch (...)
    {
        t.test(false, "Larger list, index beyond end - throws out_of_range");
    }
    delete headi;

}


// test_function_didItThrow
// Test suite for function template didItThrow
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_function_didItThrow(Tester & t)
{
    std::cout << "Test Suite: function template didItThrow (Exercise B)"
              << std::endl;

    bool didThrow;  // Whether function throws or not

    // Function throws standard exception class
    didThrow = false;
    try
    {
        didItThrow(thisThrows, didThrow);
        t.test(false,
            "Throwing function #1 - should re-throw same exception");
    }
    catch (std::runtime_error & e)
    {
        t.test(std::string("Hi!") == e.what(),
            "Throwing function #1 - should re-throw same exception");
    }
    catch (...)
    {
        t.test(false,
            "Throwing function #1 - should re-throw same exception");
    }
    t.test(didThrow, "Throwing function #1 - bool param is true");

    // Function throws int
    didThrow = false;
    try
    {
        didItThrow(thisThrowsStrangely, didThrow);
        t.test(false, "Throwing function #2 - should re-throw same exception");
    }
    catch (int & e)
    {
        t.test(e == -42, "Throwing function #2 - should re-throw same exception");
    }
    catch (...)
    {
        t.test(false, "Throwing function #2 - should re-throw same exception");
    }
    t.test(didThrow, "Throwing function #2 - bool param is true");

    // Function object, does not throw
    didThrow = true;
    try
    {
        didItThrow(FuncObj(), didThrow);
        t.test(true, "Non-throwing function object - should not throw");
    }
    catch (...)
    {
        t.test(false, "Non-throwing function object - should not throw");
    }
    t.test(!didThrow, "Non-throwing function object - bool param is false");
}


// test_function_countUnique
// Test suite for function template countUnique
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_function_countUnique(Tester & t)
{
    std::cout << "Test Suite: function template countUnique (Exercise C)"
              << std::endl;

    std::deque<int> di {
        1, 1, 2, 1, 2, 2, 3, -1, -1, -1, 5, 3, 3, 3, 2, 2, 1, 1, 1
    };
    std::deque<int> dic;

    // Check return type of countUnique
    dic = di;
    t.test(TypeCheck<std::size_t>::check(
               countUnique(dic.begin(), dic.end())),
           "countUnique: return type");

    dic = di;
    t.test(countUnique(dic.rbegin(), dic.rbegin()) == 0,
        "Empty range");

    dic = di;
    t.test(countUnique(dic.rbegin()+3, dic.rbegin()+4) == 1,
        "Size 1");

    dic = di;
    t.test(countUnique(dic.rbegin()+3, dic.rbegin()+5) == 1,
        "Size 2, equal integers");

    dic = di;
    t.test(countUnique(dic.rbegin()+4, dic.rbegin()+6) == 2,
        "Size 2, distinct integers");

    dic = di;
    t.test(countUnique(dic.rbegin()+9, dic.rbegin()+12) == 1,
        "Size 3, equal integers");

    dic = di;
    t.test(countUnique(dic.rbegin()+7, dic.rbegin()+10) == 3,
        "Size 3, distinct integers");

    dic = di;
    t.test(countUnique(dic.rbegin()+8, dic.rbegin()+11) == 2,
        "Size 3, two values");

    dic = di;
    t.test(countUnique(dic.rbegin()+5, dic.rbegin()+13) == 3,
        "Longer test #2");

    dic = di;
    t.test(countUnique(dic.rbegin()+3, dic.rbegin()+15) == 4,
        "Longer test #2");

    dic = di;
    t.test(countUnique(dic.rbegin(), dic.rend()) == 5,
        "Longer test #3");

    {
    std::deque<int> di2(100000, 3);
    t.test(countUnique(di2.rbegin(), di2.rend()) == 1,
        "Very long test #1");
    }

    {
    std::deque<int> di2(100000, 4);
    di2[40000] = 3;
    t.test(countUnique(di2.rbegin(), di2.rend()) == 2,
        "Very long test #2");
    }

    {
    std::deque<int> di2(100000, 4);
    for (size_t i = 0; i != 100000; i += 2)
        di2[i] = 3;
    t.test(countUnique(di2.rbegin(), di2.rend()) == 2,
        "Very long test #3");
    }

    {
    std::vector<std::string> vs { "abc", "abc" };
    t.test(countUnique(vs.begin(), vs.end()) == 1,
        "Strings, equal");
    }

    {
    std::vector<std::string> vs { "abc", "def" };
    t.test(countUnique(vs.begin(), vs.end()) == 2,
        "Strings, distinct");
    }
}


// test_function_gcd
// Test suite for function gcd
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_function_gcd(Tester & t)
{
    std::cout << "Test Suite: function template gcd (Exercise D)"
              << std::endl;

    // Check return type of gcd
    t.test(TypeCheck<int>::check(gcd(2, 3)), "gcd: return type");

    // GCD function data
    // Three integers: a, b, GCD of a & b
    std::vector<std::vector<int> > gcd_data {
        {       0,      1,    1 },
        {       1,      0,    1 },
        {       1,      1,    1 },
        {       3,     10,    1 },
        {      10,      3,    1 },
        {       6,     15,    3 },
        {      15,      6,    3 },
        {       5, 100000,    5 },
        {  100000,      5,    5 },
        {       5, 100001,    1 },
        {  100001,      5,    1 },
        {     910,     42,   14 },
        {      42,    910,   14 },
        {  311850, 429975, 4725 },
        {  429975, 311850, 4725 },
        {  196418, 317811,    1 },
        {  317811, 196418,    1 },
        {  196418, 317812,    2 },
        {  317812, 196418,    2 },
    };

    // Test function gcd using the above vector
    for (const auto & v : gcd_data)
    {
        gcd_single_test(t, v[0], v[1], v[2]);
    }
}


// test_da3_functions
// Test suite for Assignment 3 functions & function templates
// Uses other test-suite functions
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_da3_functions(Tester & t)
{
    // Do all the test suites
    std::cout
        << "TEST SUITES FOR ASSIGNMENT 3, EXERCISES A, B, C, D"
        << std::endl;
    test_function_listItem(t);
    test_function_didItThrow(t);
    test_function_countUnique(t);
    test_function_gcd(t);
}


// ************************************************************************
// Main program
// ************************************************************************


// main
// Runs Assignment 3 test suite, prints results to cout.
int main()
{
    Tester t;
    test_da3_functions(t);

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

