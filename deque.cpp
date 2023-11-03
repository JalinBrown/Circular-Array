/*!*****************************************************************************
*\file     deque.cpp
*\author   Jalin A. Brown
*\email    JalinBrownWorks@gmail.com

*\brief Description:
  Implementation of a circular array - an array that supports efficient insert
  on both ends.

  NOTE: e = (e + 1) % capacity;

  1) Increment "e" by 1: 
  The current value of "e" is incremented by 1. 
  This step is essential for moving to the next position in the data structure.

  2) Calculate the remainder: 
  After incrementing "e," calculate the remainder when dividing the updated
  "e" by the "capacity."

  3) Assign the result to "e": 
  The calculated remainder, which represents the new position of "e" within 
  the data structure, is then assigned back to "e." This step ensures that 
  "e" wraps around to the beginning of the data structure when it reaches its 
  capacity, creating a circular wrap-around effect for efficient data storage.

******************************************************************************/

//-----------------------------------------------------------------------------
// Includes:
//-----------------------------------------------------------------------------

#include "deque.h"
#include <iostream>
#include <iomanip>

//-----------------------------------------------------------------------------
// Public Structures:
//-----------------------------------------------------------------------------

namespace WrapBuffer {

  //-----------------------------------------------------------------------------
  // Public Functions:
  //-----------------------------------------------------------------------------

  // Default CTOR
  Deque::Deque() : b(0), e(0), size(0), capacity(0), array(nullptr) {}

  //-------------------------------------------------------------------------

  // Parameterized CTOR
  Deque::Deque(int* array_, unsigned int size_) : b(0), e(size_), size(e), capacity(size), array(new int[size]) 
  {
    for (int i = 0; i < e; ++i) 
    {
      array[i] = array_[i];
    }
  }

  //-------------------------------------------------------------------------

  // Copy CTOR
  Deque::Deque(const Deque& rhs) : b(0), e(rhs.size), size(e), capacity(size), array(size ? new int[size] : nullptr) 
  {
    for (int i = 0; i < e; ++i) 
    {
      array[i] = rhs[i];
    }
  }

  //-------------------------------------------------------------------------

  // Assignment CTOR
  Deque& Deque::operator=(Deque rhs) 
  {
    swap(rhs);
    return *this;
  }

  //-------------------------------------------------------------------------

  // DTOR
  Deque::~Deque() 
  {
    delete[] array;
  }

  //-------------------------------------------------------------------------

  // Get the size of the Deque
  int Deque::Size() const 
  {
    return size;
  }

  //-------------------------------------------------------------------------

  // Check if the Deque is empty
  bool Deque::Empty() const 
  {
    return (size == 0);
  }

  //-------------------------------------------------------------------------

  // Clear the Deque
  void Deque::Clear() 
  {
    for (int i = 0; i < size; ++i) 
    {
      array[(b + i) % capacity] = 0;
    }
    size = 0;
    b = 0;
    e = 0;
  }

  //-------------------------------------------------------------------------

  // Get the capacity of the Deque
  int Deque::Capacity() const 
  {
    return capacity;
  }

  //-------------------------------------------------------------------------

  // Push a value to the back of the Deque
  void Deque::Push_back(int val) 
  {
    // Check if the Deque is full and needs reallocation
    if (size == capacity) {
      reallocate(capacity ? capacity * 2 : 1);
    }

    // Add the new value to the back of the Deque
    array[e] = val;

    // Update the end index while considering circular wrap-around
    e = (e + 1) % capacity;

    // Increase the size to reflect the added element
    size++;
  }

  //-------------------------------------------------------------------------

  // Pop the value from the back of the Deque
  int Deque::Pop_back() 
  {
    if (size == 0) 
    {
      return 0;
    }

    if (size == capacity / 4) 
    {
      reallocate(capacity / 2);
    }

    e = (e - 1 + capacity) % capacity;
    int removedValue = array[e];
    size--;

    return removedValue;
  }

  //-------------------------------------------------------------------------

  // Index Operator with Reference
  int& Deque::operator[](unsigned int pos) 
  {
    if (size == 0 || pos >= size) 
    {
      throw std::out_of_range("Index out of range");
    }
    return array[(b + pos) % capacity];
  }

  //-------------------------------------------------------------------------

  // Index Operator
  int Deque::operator[](unsigned int pos) const 
  {
    if (size == 0 || pos >= size) 
    {
      throw std::out_of_range("Index out of range");
    }
    return array[(b + pos) % capacity];
  }

  //-------------------------------------------------------------------------

  // Swap two Deques
  void Deque::swap(Deque& other) 
  {
    std::swap(b, other.b);
    std::swap(e, other.e);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(array, other.array);
  }

  //-------------------------------------------------------------------------

  // Push a value to the front of the Deque
  void Deque::Push_front(int val) 
  {
    if (size == capacity) 
    {
      reallocate(capacity ? capacity * 2 : 1);
    }

    // If the array is currently empty (nullptr), initialize it with a single element.
    if (array == nullptr) 
    {
      capacity = 1;
      array = new int[capacity];
      array[0] = val;
      b = 0;
      e = 1;
      size = 1;
    }
    else 
    {
      // Calculate the new begin (b) index and insert the value at that position.
      b = (b - 1 + capacity) % capacity;
      array[b] = val;
      size++;
    }
  }

  //-------------------------------------------------------------------------

  // Pop a value from the front of the Deque
  int Deque::Pop_front() 
  {
    if (size == capacity / 4) 
    {
      reallocate(capacity / 2);
    }

    if (size == 0) 
    {
      return 0;
    }

    int removedValue = array[b];
    b = (b + 1) % capacity;
    size--;

    return removedValue;
  }

  //-------------------------------------------------------------------------

  // Addition and assignment operator +=
  Deque& Deque::operator+=(const Deque& rhs) 
  {
    if (!rhs.Empty()) 
    {
      int totalSize = size + rhs.size;

      // If the combined size exceeds the current capacity, reallocate the array to accommodate the new elements.
      if (totalSize > capacity) 
      {
        reallocate(totalSize);
      }

      //1. Copy the elements from the rhs Deque to the current Deque, ensuring correct positioning based on indices.
      for (int i = 0; i < rhs.size; ++i) 
      {
        //2. Calculate the proper indices for appending, considering the circular nature of the Deque.
        array[(e + i) % capacity] = rhs.array[(rhs.b + i) % rhs.capacity];
      }

      //3. Update the size and the end (e) index of the current Deque to reflect the combined Deque.
      size = totalSize;
      e = (e + rhs.size) % capacity;
    }

    // Return a reference to the modified Deque 
    return *this;
  }

  //-------------------------------------------------------------------------

  // Addition Operator +
  Deque Deque::operator+(const Deque& rhs) const 
  {
    Deque result(*this);
    result += rhs;
    return result;
  }

  //-------------------------------------------------------------------------

  // Reverse the values of the Deque
  Deque& Deque::reverse() 
  {
    // Check if there are at least two elements in the Deque to reverse.
    if (size > 1) 
    {
      int i = 0;        // Initialize the left index.
      int j = size - 1; // Initialize the right index.

      // Swap elements at indices 'i' and 'j' to reverse their positions.
      while (i < j) {
        int temp = array[(b + i) % capacity];
        array[(b + i) % capacity] = array[(b + j) % capacity];
        array[(b + j) % capacity] = temp;
        i++;  // Move the left index to the right.
        j--;  // Move the right index to the left.
      }
    }

    return *this;
  }

  //-------------------------------------------------------------------------

  // Copy, Flip, and Return a Deque array
  Deque Deque::operator~() const 
  {
    Deque flipped(*this);
    int i = 0;        // Initialize the left index.
    int j = size - 1; // Initialize the right index.

    while (i < j) 
    {
      // Swap elements in the flipped Deque to reverse their order.
      int temp = flipped.array[(flipped.b + i) % flipped.capacity];
      flipped.array[(flipped.b + i) % flipped.capacity] = flipped.array[(flipped.b + j) % flipped.capacity];
      flipped.array[(flipped.b + j) % flipped.capacity] = temp;
      i++;
      j--;
    }

    return flipped;
  }

  //-------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Private Functions:
//-----------------------------------------------------------------------------

  // Reallocation of the Deque
  void Deque::reallocate(int new_capacity) 
  {
    // If new_capacity is zero, delete the array and reset the Deque.
    if (new_capacity == 0) 
    {
      delete[] array;
      array = nullptr;
      b = 0;
      e = 0;
      size = 0;
      capacity = 0;
    }
    else 
    {
      // If new_capacity is non-zero, 
      // allocate a new array with the specified capacity
      int* new_array = new int[new_capacity];

      // Copy the existing elements to it,  
      for (int i = 0; i < size; ++i) 
      {
        new_array[i] = array[(b + i) % capacity];
      }
      delete[] array;

      // Update indices and capacity accordingly.
      array = new_array;
      b = 0;
      e = size;
      capacity = new_capacity;
    }
  }

  //-------------------------------------------------------------------------

  // Stream Operator Overload
  std::ostream& operator<<(std::ostream& os, const Deque& d) 
  {
    // Iterate through the Deque and prints its elements separated by spaces.
    for (int i = 0; i < d.Size(); ++i) 
    {
      os << d[i] << " ";
    }
    return os;
  }

  //-------------------------------------------------------------------------

}

//-----------------------------------------------------------------------------