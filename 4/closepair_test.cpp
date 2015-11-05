// closepair_test.cpp
// VERSION 2
// Glenn G. Chappell
// 9 Oct 2015
// Updated: 14 Oct 2015
//
// For CS 311 Fall 2015
// Test program for function template closePair
// Used in Assignment 4, Exercise A
//
// History:
// - v2: Improved ambiguous 4-point test

// Includes for code to be tested
#include "closepair.h"  // For closePair
#include "closepair.h"  // Double inclusion test

// Includes for testing package & code common to all test programs
#include <iostream>     // for std::cout, std::endl, std::cin
#include <string>       // for std::string
#include <stdexcept>    // for std::runtime_error

// Additional includes for this test program
#include <utility>      // for std::pair, std::make_pair
#include <cstddef>      // for std::size_t
#include <vector>       // for std::vector


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


double ptDistSq(const std::pair<double, double> & a,
                const std::pair<double, double> & b)
{
    auto xd = a.first - b.first;
    auto yd = a.second - b.second;
    return xd*xd + yd*yd;
}


template<typename RAIter>
std::pair<std::size_t, std::size_t> closePair_bf(RAIter f,
                                                 RAIter l)
{
    std::size_t pi1 = std::size_t(0);
    std::size_t pi2 = std::size_t(1);
    double dsq = ptDistSq(f[pi1], f[pi2]);

    std::size_t n = l - f;
    for (std::size_t i = 0; i < n-1; ++i)
    {
        for (std::size_t k = i+1; k < n; ++k)
        {
            double ddsq = ptDistSq(f[i], f[k]);
            if (ddsq < dsq)
            {
                pi1 = i;
                pi2 = k;
                dsq = ddsq;
            }
        }
    }
    return std::make_pair(pi1, pi2);
}


template<typename RAIter>
void check_small(Tester & t,
                 RAIter f,
                 RAIter l,
                 const std::string & msg)
{
    auto pa = closePair(f, l);
    auto pb = closePair_bf(f, l);
    bool success = (pa == pb)
                || (pa.first == pb.second && pa.second == pb.first);
    t.test(success, msg);
}


std::vector<std::pair<double, double> > make_large(size_t k)
{
    std::vector<std::pair<double, double> > v;
    for (size_t i = 0; i < k; ++i)
    {
        for (size_t j = 0; j < k; ++j)
        {
            v.push_back(std::make_pair(i + j * 0.00001,
                                       j + i * 0.00001));
        }
    }
    return v;
}


bool near(const std::pair<double, double> & pt1,
          const std::pair<double, double> & pt2)
{
    double tol = 0.01;
    return pt1.first - pt2.first < tol
        && pt2.first - pt1.first < tol
        && pt1.second - pt2.second < tol
        && pt2.second - pt1.second < tol;
}


template<typename RAIter>
void check_large(Tester & t,
                 RAIter f,
                 RAIter l,
                 const std::pair<double, double> & pt1,
                 const std::pair<double, double> & pt2,
                 const std::string & msg)
{
    auto pa = closePair(f, l);
    bool success = (near(pt1, f[pa.first]) && near(pt2, f[pa.second]))
                || (near(pt2, f[pa.first]) && near(pt1, f[pa.second]));
    t.test(success, msg);
}


// ************************************************************************
// Test Suite Functions
// ************************************************************************


// test_closePair_base
// Test suite for closePair, base cases
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_closePair_base(Tester & t)
{
    std::cout << "Test Suite: closePair, base cases" << std::endl;

    std::vector<std::pair<double, double> > v;  // Holds points

    // 2 pts
    v.clear();
    v.push_back(std::make_pair(1., 2.));
    v.push_back(std::make_pair(2., 3.));
    check_small(t, v.begin(), v.end(), "2 pts");

    // 3 pts #1
    v.clear();
    v.push_back(std::make_pair(-1., 0.));
    v.push_back(std::make_pair(1., 0.0001));
    v.push_back(std::make_pair(-1.0001, 0.01));
    check_small(t, v.begin(), v.end(), "3 pts, #1");

    // 3 pts #2
    v.clear();
    v.push_back(std::make_pair(-1., 0.));
    v.push_back(std::make_pair(1., 0.0001));
    v.push_back(std::make_pair(1.0001, 0.01));
    check_small(t, v.begin(), v.end(), "3 pts, #2");

    // 3 pts #3
    v.clear();
    v.push_back(std::make_pair(-1., 0.));
    v.push_back(std::make_pair(1., 0.0001));
    v.push_back(std::make_pair(0., 1000.));
    check_small(t, v.begin(), v.end(), "3 pts, #3");

    // 3 pts #4
    v.clear();
    v.push_back(std::make_pair(-1., 0.));
    v.push_back(std::make_pair(1., 0.0001));
    v.push_back(std::make_pair(-1.0001, -0.01));
    check_small(t, v.begin(), v.end(), "3 pts, #4");

    // 3 pts #5
    v.clear();
    v.push_back(std::make_pair(-1., 0.));
    v.push_back(std::make_pair(1., 0.0001));
    v.push_back(std::make_pair(1.0001, -0.01));
    check_small(t, v.begin(), v.end(), "3 pts, #5");

    // 3 pts #6
    v.clear();
    v.push_back(std::make_pair(-1., 0.));
    v.push_back(std::make_pair(1., 0.0001));
    v.push_back(std::make_pair(0., -1000.));
    check_small(t, v.begin(), v.end(), "3 pts, #6");
}


// test_closePair_small
// Test suite for closePair, small datasets
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_closePair_small(Tester & t)
{
    std::cout << "Test Suite: closePair, small datasets" << std::endl;

    std::vector<std::pair<double, double> > v;  // Holds points

    // 4 pts #1
    v.clear();
    v.push_back(std::make_pair(-1., -0.9));
    v.push_back(std::make_pair(1., -1.));
    v.push_back(std::make_pair(-1., 0.9));
    v.push_back(std::make_pair(1., 1.));
    check_small(t, v.begin(), v.end(), "4 pts, #1");

    // 4 pts #2
    v.clear();
    v.push_back(std::make_pair(-0.9, -0.91));
    v.push_back(std::make_pair(1., -1.));
    v.push_back(std::make_pair(-1., 1.));
    v.push_back(std::make_pair(0.9, 0.9));
    check_small(t, v.begin(), v.end(), "4 pts, #2");

    // 5 pts #1
    v.clear();
    v.push_back(std::make_pair(-2., 1.));
    v.push_back(std::make_pair(-1., 0.));
    v.push_back(std::make_pair(-0.1, 0.9));
    v.push_back(std::make_pair(1., 0.0001));
    v.push_back(std::make_pair(2., 1.0001));
    check_small(t, v.begin(), v.end(), "5 pts, #1");

    // 5 pts #2
    v.clear();
    v.push_back(std::make_pair(-2., 1.));
    v.push_back(std::make_pair(-1., 0.));
    v.push_back(std::make_pair(0.1, 1.0001));
    v.push_back(std::make_pair(1., 0.0001));
    v.push_back(std::make_pair(2., 1.0002));
    check_small(t, v.begin(), v.end(), "5 pts, #2");

    // 6 pts #1
    v.clear();
    v.push_back(std::make_pair(0.99, 0.01));
    v.push_back(std::make_pair(0., 2.));
    v.push_back(std::make_pair(0, 4.));
    v.push_back(std::make_pair(-0.99, -0.01));
    v.push_back(std::make_pair(0., -2.));
    v.push_back(std::make_pair(0, -4.));
    check_small(t, v.begin(), v.end(), "6 pts, #1");

    // 6 pts #2
    v.clear();
    v.push_back(std::make_pair(-0.99, 0.01));
    v.push_back(std::make_pair(0., 2.));
    v.push_back(std::make_pair(0, 4.));
    v.push_back(std::make_pair(0.99, -0.01));
    v.push_back(std::make_pair(0., -2.));
    v.push_back(std::make_pair(0, -4.));
    check_small(t, v.begin(), v.end(), "6 pts, #2");

    // 6 pts #3
    v.clear();
    v.push_back(std::make_pair(-1., 0.011));
    v.push_back(std::make_pair(1., 0.01));
    v.push_back(std::make_pair(0., 2.));
    v.push_back(std::make_pair(-1., -0.011));
    v.push_back(std::make_pair(1., -0.01));
    v.push_back(std::make_pair(0., -2.));
    check_small(t, v.begin(), v.end(), "6 pts, #3");

    // 10 pts
    v = make_large(3);
    v.push_back(std::make_pair(1.1, 0.9));
    check_small(t, v.begin(), v.end(), "10 pts");

    // 17 pts
    v = make_large(4);
    v.push_back(std::make_pair(1.9, 1.1));
    check_small(t, v.begin(), v.end(), "17 pts");
}


// test_closePair_medium
// Test suite for closePair, medium-sized datasets
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_closePair_medium(Tester & t)
{
    std::cout << "Test Suite: closePair, medium-sized datasets" << std::endl;

    std::vector<std::pair<double, double> > v;  // Holds points

    // 101 pts
    v = make_large(10);
    v.push_back(std::make_pair(4.9, 4.1));
    check_small(t, v.begin(), v.end(), "101 pts");

    // 122 pts
    v = make_large(11);
    v.push_back(std::make_pair(3.9, 6.1));
    check_small(t, v.begin(), v.end(), "122 pts");

    // 145 pts
    v = make_large(12);
    v.push_back(std::make_pair(4.9, 10.9));
    check_small(t, v.begin(), v.end(), "145 pts");

    // 170 pts
    v = make_large(13);
    v.push_back(std::make_pair(5.1, 6.1));
    check_small(t, v.begin(), v.end(), "170 pts");

    // 197 pts
    v = make_large(14);
    v.push_back(std::make_pair(11.1, 6.9));
    check_small(t, v.begin(), v.end(), "197 pts");
}


// test_closePair_large
// Test suite for closePair, large datasets
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_closePair_large(Tester & t)
{
    std::cout << "Test Suite: closePair, large datasets" << std::endl;

    std::vector<std::pair<double, double> > v;  // Holds points

    // 2501 pts
    v = make_large(50);
    v.push_back(std::make_pair(25.1, 27.9));
    check_large(t, v.begin(), v.end(),
                std::make_pair(25.1, 27.9),
                std::make_pair(25., 28.),
                "2501 pts");

    // 8101 pts
    v = make_large(90);
    v.push_back(std::make_pair(23.9, 70.1));
    check_large(t, v.begin(), v.end(),
                std::make_pair(23.9, 70.1),
                std::make_pair(24., 70.),
                "8101 pts");

    // 40001 pts
    v = make_large(200);
    v.push_back(std::make_pair(6.1, 150.1));
    check_large(t, v.begin(), v.end(),
                std::make_pair(6.1, 150.1),
                std::make_pair(6., 150.),
                "40001 pts");

    // 90001 pts
    v = make_large(300);
    v.push_back(std::make_pair(101.9, 207.1));
    check_large(t, v.begin(), v.end(),
                std::make_pair(101.9, 207.1),
                std::make_pair(102., 207.),
                "90001 pts");
}


// test_closePair
// Test suite for closePair
// Uses other test-suite functions
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_closePair(Tester & t)
{
    // Do all the test suites
    std::cout << "TEST SUITES FOR closePair" << std::endl;
    test_closePair_base(t);
    test_closePair_small(t);
    test_closePair_medium(t);
    test_closePair_large(t);
}


// ************************************************************************
// Main program
// ************************************************************************


// main
// Runs closePair test suite, prints results to cout.
int main()
{
    Tester t;
    test_closePair(t);

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

