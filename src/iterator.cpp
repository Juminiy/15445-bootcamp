/**
 * @file iterator.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code on the usage and creation of iterators.
 */

// C++ iterators are objects that point to an element inside a container.
// They can be used to iterate through the objects of that container.
// One example of an iterator that you know is a pointer. A pointer
// can be used to iterate through a C style array. Take the following
// C-style code snippet:
// int *array = malloc(sizeof(int) * 10);
// int *iter = array;
// int zero_elem = *iter;
// iter++;
// int first_elem = *iter;
// As we can see, the ++ operator can be used to iterate through the
// C style array, and the derefence operator returns the value at the
// iterator.

// The main components of a C++ iterator are its main two operators. The
// dereference operator (*) on an iterator should return the value of the
// element at the current position of the iterator. The ++ (postfix increment)
// operator should increment the iterator's position by 1. As you can see, this
// is true with the pointer being used to iterate through a C style array.

// There are a few examples about how to use iterators to access elements
// in C++ STL containers in vectors.cpp, sets.cpp, unordered_maps.cpp, 
// and auto.cpp. This is because using iterators in C++ to access and modify
// elements in C++ STL containers is considered good style, and worth
// mentioning in these files. 

// This file will mainly focus on the implementation of iterators. In this
// file, we demonstrate implementing C++ iterators by writing a basic doubly
// linked list (DLL) iterator.

// Includes std::cout (printing) for demo purposes.
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <new>
#include <ostream>

// This is the definition of the Node struct, used in our DLL.
struct Node {
  Node(int val) 
    : next_(nullptr)
    , prev_(nullptr)
    , value_(val) {}

  Node* next_;
  Node* prev_;
  int value_;
};

// This class implements a C++ style iterator for the doubly linked list class 
// DLL. This class's constructor takes in a node that marks the start of the
// iterating. It also implements several operators that increment the iterator
// (i.e. accessing the next element in the DLL) and test for equality between
// two different iterators by comparing their curr_ pointers.
class DLLIterator {
  public:
    DLLIterator(Node* head) 
      : curr_(head) {}

    // Implementing a prefix increment operator (++iter).
    DLLIterator& operator++() {
      curr_ = curr_->next_;
      return *this;
    }

    DLLIterator& operator--() {
      curr_ = curr_->prev_;
      return *this;
    }

    // Implementing a postfix increment operator (iter++). The difference
    // between a prefix and postfix increment operator is the return value
    // of the operator. The prefix operator returns the result of the
    // increment, while the postfix operator returns the iterator before
    // the increment.
    DLLIterator operator++(int) {
      DLLIterator temp = *this;
      ++*this;
      return temp;
    }

    DLLIterator operator--(int) {
      DLLIterator temp = *this;
      --*this;
      return temp;
    }

    DLLIterator operator[](size_t _off) {
      DLLIterator it = *this;
      if (_off > 0) {
        while(_off > 0 && it.curr_){
          it++;
          _off--;
        }
      } else if (_off < 0) {
        while(_off < 0 && it.curr_) {
          it--;
          _off++;
        }
      }
      return it;
    }

    // This is the equality operator for the DLLIterator class. It
    // tests that the current pointers are the same.
    bool operator==(const DLLIterator &itr) const {
      return itr.curr_ == this->curr_;
    }

    // This is the inequality operator for the DLLIterator class. It
    // tests that the current pointers are not the same.
    bool operator!=(const DLLIterator &itr) const {
      return itr.curr_ != this->curr_;
    }

    // This is the dereference operator for the DLLIterator class. It
    // returns the value of the element at the current position of the
    // iterator. The current position of the iterator is marked by curr_,
    // and we can access the value of curr_ by accessing its value field.
    int operator*() {
      return curr_->value_;
    }

    friend std::ostream& operator<<(std::ostream& _os, DLLIterator const & dll) {
      _os << "{" << uintptr_t(dll.curr_) << "}";
      return _os;
    }

  private:
    Node* curr_;
};

// This is a basic implementation of a doubly linked list. It also includes
// iterator functions Begin and End, which return DLLIterators that can be
// used to iterate through this DLL instance.
class DLL {
  public:
    // DLL class constructor.
    DLL() 
    : head_(nullptr)
    , size_(0) {}

    // Destructor should delete all the nodes by iterating through them.
    ~DLL() {
      Node *current = head_;
      while(current != nullptr) {
        Node *next = current->next_;
        delete current;
        current = next;
      }
      head_ = nullptr;
    }

    // Function for inserting val at the head of the DLL.
    void InsertAtHead(int val) {
      Node *new_node = new Node(val);
      new_node->next_ = head_;

      if (head_ != nullptr) {
        head_->prev_ = new_node;
      } else {
        tail_ = new_node;
      }

      head_ = new_node;
      size_ += 1;
    }

    void InsertAtTail(int val) {
      Node *new_node = new Node(val);
      new_node->prev_ = tail_;

      if(tail_ != nullptr) {
        tail_->next_ = new_node;
      } else {
        head_ = new_node;
      }

      tail_ = new_node;
      size_ += 1;
    }

    // The Begin() function returns an iterator to the head of the DLL,
    // which is the first element to access when iterating through.
    DLLIterator Begin() const {
      return DLLIterator(head_);
    }

    // The End() function returns an iterator that marks the one-past-the-last
    // element of the iterator. In this case, this would be an iterator with
    // its current pointer set to nullptr.
    DLLIterator End() const {
      return DLLIterator(tail_);
    }

    size_t size() const {
      return size_;
    }

  private: 
    Node* head_{nullptr};
    Node* tail_{nullptr};
    size_t size_;
};

// The main function shows the usage of the DLL iterator.
int main() {
  // Creating a DLL and inserting elements into it.
  DLL dll;
  dll.InsertAtHead(6);
  dll.InsertAtHead(5);
  dll.InsertAtHead(4);
  dll.InsertAtHead(3);
  dll.InsertAtHead(2);
  dll.InsertAtHead(1);
  // 1<-->2<-->3<-->4<-->5<-->6

  // We can iterate through our DLL via both our prefix and postfix operators.
  // std::cout << "Printing elements of the DLL dll via prefix increment operator\n";
  for (DLLIterator iter = dll.Begin(); iter != nullptr; ++iter) {
    std::cout << *iter << " <--> "; // 1 2 3 4 5 6 
  } std::cout << "nullptr\n";

  // std::cout << "Printing elements of the DLL dll via postfix increment operator\n";
  for (DLLIterator iter = dll.Begin(); iter != nullptr; iter++) {
    std::cout << *iter << " <--> "; // 1 2 3 4 5 6 
  } std::cout << "nullptr\n";

  for (DLLIterator iter = dll.Begin(); iter != nullptr; iter[+3]) {
    std::cout << *iter << " <--> "; // 6 5 4 3 2 1
  } std::cout << "nullptr\n";

  // reverse iterate
  for (DLLIterator iter = dll.End(); iter != nullptr; iter--) {
    std::cout << *iter << " <--> "; // 6 5 4 3 2 1
  } std::cout << "nullptr\n";

  // reverse iterate
  for (DLLIterator iter = dll.End(); iter != nullptr; --iter) {
    std::cout << *iter << " <--> "; // 6 5 4 3 2 1
  } std::cout << "nullptr\n";

  for (DLLIterator iter = dll.End(); iter != nullptr; iter[-3]) {
    std::cout << *iter << " <--> "; // 6 5 4 3 2 1
  } std::cout << "nullptr\n";

  return 0;
}