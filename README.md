# Deque (Circular Array) C++ Class

Author: Jalin A. Brown

Email: JalinBrownWorks@gmail.com

## Brief Description

This is an implementation of a circular array, also known as a Deque (Double-Ended Queue). A Deque is an array that supports efficient insertions and removals from both ends. The Deque is implemented with circular wrap-around logic, allowing for optimal memory usage.

**Important Note:**

The key operation `e = (e + 1) % capacity` is crucial for maintaining the circular array property.

## Features

- Circular array implementation for efficient double-ended insertions and removals.
- Supports standard Deque operations: push_back, pop_back, push_front, pop_front, and more.
- Memory-efficient circular wrap-around logic.
- Custom reverse and copy operations.
- Provides operator overloads for index access and concatenation.

## Usage

1. Include the `deque.h` header in your C++ project.
2. Create a Deque object using one of the provided constructors.
3. Use Deque methods to perform various operations such as inserting, removing, reversing, and copying elements.
4. Utilize operator overloads for index access and concatenation.

## Example Usage

```cpp
#include <iostream>
#include "deque.h"

int main() {
    // Create a Deque with an initial size of 5
    int initialArray[] = {1, 2, 3, 4, 5};
    WrapBuffer::Deque deque(initialArray, 5);

    // Print the original Deque
    std::cout << "Original Deque: ";
    std::cout << deque << std::endl;

    // Push elements to the front and back
    deque.Push_back(6);
    deque.Push_front(0);

    // Print the modified Deque
    std::cout << "Deque after pushing elements: ";
    std::cout << deque << stdendl;

    // Pop elements from the front and back
    int poppedFront = deque.Pop_front();
    int poppedBack = deque.Pop_back();

    // Print the Deque after popping elements
    std::cout << "Deque after popping elements: ";
    std::cout << deque << std::endl;

    // Reverse the Deque
    deque.reverse();

    // Print the reversed Deque
    std::cout << "Reversed Deque: ";
    std::cout << deque << std::endl;

    // Create a new Deque that is a copy of the original Deque but with reversed elements
    WrapBuffer::Deque reversedDeque = ~deque;

    // Print the reversed copy Deque
    std::cout << "Reversed Copy Deque: ";
    std::cout << reversedDeque << std::endl;

    return 0;
}
```
