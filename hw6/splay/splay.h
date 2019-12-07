#ifndef SPLAY_H
#define SPLAY_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "../bst/print_bst.h"

/**
* A templated binary search tree implemented as a Splay tree.
*/
template <class Key, class Value>
class SplayTree : public BinarySearchTree<Key, Value>
{
public:
	// Methods for inserting/removing elements from the tree. You must implement
	// both of these methods.
	SplayTree();
	virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
	void remove(const Key& key);
	int report() const;

private:
	/* You'll need this for problem 5. Stores the total number of inserts where the
	   node was added at level strictly worse than 2*log n (n is the number of nodes
	   including the added node. The root is at level 0). */
	void splay(Node<Key, Value>* node);
	int badInserts;
	int numNodes;
	/* Helper functions are encouraged. */
};

/*
--------------------------------------------
Begin implementations for the SplayTree class.
--------------------------------------------
*/

template<typename Key, typename Value>
SplayTree<Key, Value>::SplayTree() : badInserts(0), numNodes(0) { }

template<typename Key, typename Value>
int SplayTree<Key, Value>::report() const {
	return badInserts;
}

/**
* Insert function for a key value pair. Finds location to insert the node and then splays it to the top.
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	// TODO
	if(BinarySearchTree<Key, Value>::internalFind(keyValuePair.first)==nullptr){
		this->numNodes+=1;
	}
	BinarySearchTree<Key, Value>::insert(keyValuePair);
	Node<Key, Value>* inserted = BinarySearchTree<Key, Value>::internalFind(keyValuePair.first);
	Node<Key,Value>* current = this->mRoot;
	int added_height = 0;
	while(current!=nullptr){
		if(keyValuePair.first==current->getKey()){
			break;
		}
		if(keyValuePair.first<current->getKey()){
			current = current->getLeft();
			added_height+=1;
		}else{
			current = current->getRight();
			added_height+=1;
		}
	}
	if(added_height > 2*log2(this->numNodes)){
		this->badInserts+=1;
	}
	splay(inserted);
}

/**
* Remove function for a given key. Finds the node, reattaches pointers, and then splays the parent
* of the deleted node to the top.
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::remove(const Key& key)
{
	// TODO
	Node<Key, Value>* removing = BinarySearchTree<Key, Value>::internalFind(key);
	Node<Key, Value>* action_point = removing;
	if(removing->getRight()==nullptr){
		action_point = removing->getParent();
	}else{
		action_point = removing->getRight();
		if(action_point->getLeft()!=nullptr){
			while(action_point->getLeft()!=nullptr){
				action_point = action_point->getLeft();
			}
			action_point = action_point->getParent();
		}
	}
	BinarySearchTree<Key, Value>::remove(key);
	splay(action_point);
	this->numNodes-=1;
}

//function to splay a node after inserting or before removing
template<typename Key, typename Value>
void SplayTree<Key, Value>::splay(Node<Key, Value>* node)
{
	// TODO
	if(node==this->mRoot){
		return;
	}
	if(node->getParent()==this->mRoot){
		if(node->getParent()->getRight()==node){
			BinarySearchTree<Key, Value>::rotateLeft(node->getParent());
		}else{
			BinarySearchTree<Key, Value>::rotateRight(node->getParent());
		}
		return;
	}
	Node<Key, Value>* parent = node->getParent();
	Node<Key, Value>* grandparent = node->getParent()->getParent();
	if(parent->getLeft()==node){
		if(grandparent->getLeft()==parent){
			BinarySearchTree<Key, Value>::rotateRight(grandparent);
			BinarySearchTree<Key, Value>::rotateRight(parent);
		}else if(grandparent->getRight()==parent){
			BinarySearchTree<Key, Value>::rotateRight(parent);
			BinarySearchTree<Key, Value>::rotateLeft(grandparent);
		}
	}else if(parent->getRight()==node){
		if(grandparent->getRight()==parent){
			BinarySearchTree<Key, Value>::rotateLeft(grandparent);
			BinarySearchTree<Key, Value>::rotateLeft(parent);
		}else if(grandparent->getLeft()==parent){
			BinarySearchTree<Key, Value>::rotateLeft(parent);
			BinarySearchTree<Key, Value>::rotateRight(grandparent);
		}
	}
	splay(node);
}

/*
------------------------------------------
End implementations for the SplayTree class.
------------------------------------------
*/

#endif
