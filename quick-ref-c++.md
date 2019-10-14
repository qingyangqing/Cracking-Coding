For string, += and append() are more efficient than + for concatenating two strings. 
The +=/append() operator relies on the resizable array, whereas the + operator copies two strings into a third new string. 

Object * myObj = new Object; vs. Object myObj;
The new Object function is for dynamic allocation, and myObj will still live until explicitly deleting it. For Object myObj, it will be destroyed automatically when it goes out of scope.
Thus, use new Object when the object is needed to outlive the current scope.

A static data member in the class definition is a shared data member across all the objects of this class.

The "runner" technique in the linked list. 
The "fast" pointer might be ahead by a fixed amount, or it might hop multiple nodes for each one node that the "slow" pointer interates through. 
For example, to find the middle point for a linked list whose length is unknown.

Most common tree traversal methods.
In-order: left--root--right. In a binary search tree, in-order traversal gets data in sorted order.
Pre-order: root--left--right. The pre-order traversal is a topologically sorted one.
Post-order: left--right--root. 

Heap can be implemented using array. 
Heap insert: insert at rightmost, bubble up in O(log(n)) time.
Heap pop: swap the root with the rightmost, bubble down in O(log(n)) time.

DFS is recursive, while BFS is NOT recursive.
The major difference between the tree search and graph search is that, for graph search, we need to track the exploring history to avoid infinite loop. 

The arithmetic right shift (>>) essentially divides by two, while the logical right shift (>>>) does what is visually seen as shifting the bits.
Use the shift operators to get masks for bit manipulation with bit operators (&, |), such as get bit, set bit, clear bit and update bit.

The merge sort: runtime O(nlog(n)), memory O(n)+O(log(n)) = O(n).
The quick sort: runtime O(nlog(n)), memory O(log(n)).
In the two sorting methods, memory O(log(n)) is for the recursive function calls.

All data members and methods are private by default in C++.

One usage of virtual function is when we can't (don't want to) implement a method in the parent class.
By defining a pure virtual function (e.g., virtual int foo() = 0) in a class, the class will be an abstract class which cannot be instantiated.

The difference between pass-by-reference and pass-by-pointer is that pointers can be nullptr or reassigned whereas references cannot.


