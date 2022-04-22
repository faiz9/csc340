//  Node.cpp
//  Created by Frank M. Carrano and Timothy M. Henry.
//	Updated by Duc Ta
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

#include "Node.h"
#include <iostream>

using namespace std;

//
//
// PLEASE DO NOT CHANGE THIS FILE
//
//

template<typename ItemType>
Node<ItemType>::Node() : item(), next(nullptr) {}

template<typename ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr) {}

template<typename ItemType>
Node<ItemType>::Node(const ItemType& anItem, shared_ptr<Node<ItemType>> nextNodePtr) :
	item(anItem), next(nextNodePtr) {} 

template<typename ItemType>
void Node<ItemType>::setItem(const ItemType& anItem) {
	item = anItem;
}

template<typename ItemType>
void Node<ItemType>::setNext(shared_ptr<Node<ItemType>> nextNodePtr) {
	next = nextNodePtr;
}

template<typename ItemType>
ItemType Node<ItemType>::getItem() const {
	return item;
}

template<typename ItemType>
shared_ptr<Node<ItemType>> Node<ItemType>::getNext() const {
	return next;
}


// Adding destructor for node
template<typename ItemType>
Node<ItemType>::~Node() {
  cout << "\n";
  cout << "Node " << (item) << " has been deleted" << endl;
}