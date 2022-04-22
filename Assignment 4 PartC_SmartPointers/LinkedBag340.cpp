//	LinkedBag340.cpp
//	Created by: CSC340

/*
===>					<===
===>  PLEASE ADD CODE	<===
===>					<===
*/
#include <cstddef>
#include "Node.h"
#include "LinkedBag.h"
#include <string>
#include <stdlib.h>
#include <time.h>


using namespace std;

template<typename ItemType>
bool LinkedBag<ItemType>::removeSecondNode340() {
  if (getCurrentSize() < 2) {
    // Size less than 2, it cannot remove the 2nd node
    return false;
  }
  // Size > 2
  shared_ptr<Node<ItemType>> head = this->headPtr;
  shared_ptr<Node<ItemType>> secondNode = head->getNext();
  head->setNext(secondNode->getNext());

  return true; //removes the second node 
}

// inserts the new node at the end of the Linked Bag.
template<typename ItemType>
bool LinkedBag<ItemType>::addEnd340(const ItemType& newEntry) {
    // Create new node
    shared_ptr<Node<ItemType>> newNode = make_shared<Node<ItemType>>(newEntry);
    // Case: List is empty
    if (headPtr == nullptr) {
      headPtr = newNode;
    } else {
      // List is not empty. Traversal until the last node
      shared_ptr<Node<ItemType>>lastNode = headPtr;
      while (lastNode->getNext() != nullptr) {
        lastNode = lastNode->getNext();
      }
      // Link newNode into the last node
      lastNode->setNext(newNode);
    }
    return true;
}

//function 3: counts the number of nodes in the Linked Bag iteratively
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Iterative() const {
    int countItems = 0;
    shared_ptr<Node<ItemType>> curr = headPtr;
  while (curr != nullptr) {
    countItems++;
    curr = curr->getNext();
  }
  return countItems;
}

//function 4: counts the number of nodes in the Linked Bag recursively.
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Recursive() const {
  return getCurrentSize340RecursiveHelper(headPtr);
}

//helper for function 4. Test 5 passed
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveHelper(shared_ptr<Node<ItemType>> item) const {
  // Base case:
  if (item == nullptr) {
    return 0;
  }
  return 1 + getCurrentSize340RecursiveHelper(item->getNext());
}


template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveNoHelper() const {
  // Base case:
  if (headPtr == nullptr) {
    return 0;
  }
  if (headPtr->getNext() == nullptr) {
    return 1;
  }

  shared_ptr<Node<ItemType>> secondNode = headPtr->getNext();
  headPtr ->setNext(secondNode->getNext());
  int bagSize = 1 + getCurrentSize340RecursiveNoHelper();
  headPtr->setNext(secondNode);
  return bagSize;
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340Recursive(const ItemType& item) const {
  return getFrequencyOf340RecursiveHelper(headPtr, item);
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveHelper(shared_ptr<Node<ItemType>>curr, const ItemType& item) const {
  // Base case
  if (curr == nullptr) {
    return 0;
  }
  if (curr->getItem() == item) {
    return 1 + getFrequencyOf340RecursiveHelper(curr->getNext(), item);
  } else {
    return getFrequencyOf340RecursiveHelper(curr->getNext(), item);
  } 
}

//7 no helper
template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveNoHelper(const ItemType& item) const {
    // Base case
  if (headPtr == nullptr) {
    return 0;
  }
  if (headPtr->getNext() == nullptr) {
    return headPtr->getItem() == item;
  }
  shared_ptr<Node<ItemType>> secondNode = headPtr->getNext();
  headPtr->setNext(secondNode->getNext());
  int countItems;
  if (secondNode->getItem() == item) {
    countItems = 1+ getFrequencyOf340RecursiveNoHelper(item);
  } else {
    countItems = getFrequencyOf340RecursiveNoHelper(item);
  }
  headPtr->setNext(secondNode);
  return countItems;
}

//9 need random index to remove random entry
template<typename ItemType>
ItemType LinkedBag<ItemType>::removeRandom340() {
  srand(time(NULL));
  int currentSize = getCurrentSize340Iterative();
  // Generate random number
  int removedItemId = rand() % currentSize + 1;

  shared_ptr<Node<ItemType>> prevNode = nullptr;
  shared_ptr<Node<ItemType>> currNode = headPtr;
  int curNodeId = 0;
  while (currNode != nullptr) {
    curNodeId++;
    shared_ptr<Node<ItemType>>nextNode = currNode->getNext();

    if (curNodeId == removedItemId) {
      // Remove the node
      if (prevNode == nullptr) {
        headPtr = nextNode;  // Remove at head
      } else {
        prevNode->setNext(nextNode);
      }
      ItemType result = currNode->getItem();
      //delete currNode;
      return result;
      
    }
    prevNode = currNode;
    currNode = nextNode;
  }
  return ItemType();
}


