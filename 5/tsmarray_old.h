// smarray.h  UNFINISHED
// VERSION 3
// Glenn G. Chappell
// 26 Oct 2015
// Updated: 30 Oct 2015
//
// For CS 311 Fall 2015
// Header for class SmArray
// Smart Array of ints
//
// History:
// - v1: Wrote:
//   - Skeleton forms of package header & source.
//   - Class SmArray definition (exists, but is not finished).
//   - Definitions of all member types.
//   - Declarations of all data members.
//   - Comments indicating class invariants.
//   - Prototypes & dummy definitions (at least) for all package
//     functions.
//   - Corrent (maybe) definitions for all package functions that do not
//     involve any kind of copying of resizing of the array.
// - v2:
//   - Wrote copy ctor.
//   - Documented exception-safety guarantees for all functions written.
// - v3:
//   - Added _capacity data member

#ifndef FILE_SMARRAY_H_INCLUDED
#define FILE_SMARRAY_H_INCLUDED

#include <cstddef>
using std::size_t;
#include <algorithm>
using std::copy;


// *********************************************************************
// class SmArray - Class definition
// *********************************************************************


// class SmArray
// Smart array of ints
// Invariants:
//     _capacity >= _size >= 0.
//     _capacity >= MINCAP.
//     _data points to an int array, allocated with new [], owned by
//      *this, holding at least _capacity ints.
class SmArray {

// ***** SmArray: types & constants *****
public:

    using value_type = int;              // Type of data item in array
    using size_type = size_t;            // For array size & indices
    using iterator = value_type *;       // Iterator types, as in STL
    using const_iterator = const value_type *;

private:
 
    static const size_type MINCAP = 16;  // Minimum value of _capacity

// ***** SmArray: ctors, op=, dctor  *****
public:

    // Default ctor & ctor from size
    // Pre:
    // Post:
    // Strong Guarantee
    explicit SmArray(size_type size=0)
        :_capacity(size < MINCAP ? MINCAP : size),
         _size(size),
         _data(new value_type[_capacity])
        // _capacity must be declared before _data
    {}

    // Copy ctor
    // Pre:
    // Post:
    // Strong Guarantee
    SmArray(const SmArray & other)
        :_capacity(other._capacity),
         _size(other._size),
         _data(new value_type[other._capacity])
    { copy(other.begin(), other.end(), begin()); }

    // Copy assignment (defined in .cpp file)
    // Pre:
    // Post:
    // ??? Guarantee
    SmArray & operator=(SmArray rhs);

    // Dctor
    // Pre:
    // Post:
    // No-Throw Guarantee
    ~SmArray()
    { delete [] _data; }

// ***** SmArray: public operators *****
public:

    // operator[] (non-const & const)
    // Pre:
    // Post:
    // No-Throw Guarantee
    value_type & operator[](size_type index)
    { return _data[index]; }
    const value_type & operator[](size_type index) const
    { return _data[index]; }

// ***** SmArray: public functions *****
public:

    // size
    // Pre:
    // Post:
    // No-Throw Guarantee
    size_type size() const
    { return _size; }

    // empty
    // Pre:
    // Post:
    // No-Throw Guarantee
    bool empty() const
    { return _size == 0; }

    // begin (non-const & const)
    // Pre:
    // Post:
    // No-Throw Guarantee
    iterator begin()
    { return _data; }
    const_iterator begin() const
    { return _data; }

    // end (non-const & const)
    // Pre:
    // Post:
    // No-Throw Guarantee
    iterator end()
    { return _data + size(); }
    const_iterator end() const
    { return _data + size(); }

    // resize (defined in .cpp file)
    // Pre:
    // Post:
    // ??? Guarantee
    void resize(size_type newsize);

    // insert (defined in .cpp file)
    // Pre:
    // Post:
    // ??? Guarantee
    iterator insert(iterator pos,
                    const value_type & item);

    // remove (defined in .cpp file)
    // Pre:
    // Post:
    // ??? Guarantee
    iterator remove(iterator pos);

    // swap (defined in .cpp file)
    // Pre:
    // Post:
    // ??? Guarantee
    void swap(SmArray & other);

// ***** SmArray: data members *****
private:

    // _capacity must be declared before _data
    size_type _capacity;  // Size of allocated space
    size_type _size;      // Number of data items stored
    value_type * _data;   // Pointer to our array

}; // End class SmArray


#endif //#ifndef FILE_SMARRAY_H_INCLUDED

