#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "../bst/print_bst.h"

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus 
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
	// Constructor/destructor.
	AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
	virtual ~AVLNode();

	// Getter/setter for the node's height.
	int getHeight() const;
	int getBalance() const;
	void setHeight(int height);

	// Getters for parent, left, and right. These need to be redefined since they 
	// return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
	// for more information.
	virtual AVLNode<Key, Value>* getParent() const override;
	virtual AVLNode<Key, Value>* getLeft() const override;
	virtual AVLNode<Key, Value>* getRight() const override;

protected:
	int mHeight;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a height of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
	: Node<Key, Value>(key, value, parent)
	, mHeight(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* Getter function for the height. 
*/
template<typename Key, typename Value>
int AVLNode<Key, Value>::getHeight() const
{
	return mHeight;
}

//function to calculate balance of a node
template<typename Key, typename Value>
int AVLNode<Key, Value>::getBalance() const
{
	int left_height = 0;
	int right_height = 0;
	if(this->mLeft!=nullptr){
		left_height = this->getLeft()->getHeight()+1;
	}
	if(this->mRight!=nullptr){
		right_height = this->getRight()->getHeight()+1;
	}
	return right_height - left_height;
}

/**
* Setter function for the height. 
*/
template<typename Key, typename Value>
void AVLNode<Key, Value>::setHeight(int height)
{
	mHeight = height;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
	// Methods for inserting/removing elements from the tree. You must implement
	// both of these methods. 
	virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
	void remove(const Key& key);

private:
	/* Helper functions are strongly encouraged to help separate the problem
	   into smaller pieces. You should not need additional data members. */
	void insert_fix(AVLNode<Key, Value>* node, AVLNode<Key, Value>* inserted);
	void remove_fix(AVLNode<Key, Value>* node);
	void fixHeights(AVLNode<Key, Value>* node);
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	// TODO
	if(this->mRoot==nullptr){
		AVLNode<Key,Value>* adding = new AVLNode<Key,Value>(keyValuePair.first,keyValuePair.second,nullptr);
		this->mRoot = adding;
		return;
	}
	AVLNode<Key,Value>* parent = nullptr;
	AVLNode<Key,Value>* current = static_cast<AVLNode<Key,Value>*>(this->mRoot);
	AVLNode<Key,Value>* adding;
	while(current!=nullptr){
		if(keyValuePair.first==current->getKey()){
			current->setValue(keyValuePair.second);
			return;
		}
		if(keyValuePair.first<current->getKey()){
			parent = current;
			current = current->getLeft();
			if(!current){
				adding = new AVLNode<Key,Value>(keyValuePair.first,
					keyValuePair.second,parent);
				parent->setLeft(adding);
			}
		}else{
			parent = current;
			current = current->getRight();
			if(!current){
				adding = new AVLNode<Key,Value>(keyValuePair.first,
					keyValuePair.second,parent);
				parent->setRight(adding);
			}
		}
	}
	fixHeights(adding->getParent());
	if(adding->getParent()->getBalance()!=0){
		insert_fix(adding->getParent(), adding);
	}
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::fixHeights(AVLNode<Key, Value>* node){
	if(node==nullptr){
		return;
	}
	if(node->getLeft()!=nullptr && node->getRight()==nullptr){
		node->setHeight(node->getLeft()->getHeight()+1);
	}else if(node->getLeft()==nullptr && node->getRight()!=nullptr){
		node->setHeight(node->getRight()->getHeight()+1);
	}else if(node->getLeft()!=nullptr && node->getRight()!=nullptr){
		if(node->getLeft()->getHeight()>node->getRight()->getHeight()){
			node->setHeight(node->getLeft()->getHeight()+1);
		}else{
			node->setHeight(node->getRight()->getHeight()+1);
		}
	}else{
		node->setHeight(0);
	}
	fixHeights(node->getParent());
}


/**
* Remove function for a given key. Finds the node, reattaches pointers, and then balances when finished. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
	// TODO
	AVLNode<Key, Value>* removing = static_cast<AVLNode<Key, Value>* >(BinarySearchTree<Key,Value>::internalFind(key));
	if(removing==nullptr){
		return;
	}
	AVLNode<Key, Value>* action_point = removing;
	if(removing->getRight()==nullptr || removing->getLeft()==nullptr){
		action_point = removing->getParent();
	}else{
		action_point = removing->getLeft();
		if(action_point->getRight()!=nullptr){
			while(action_point->getRight()!=nullptr){
				action_point = action_point->getRight();
			}
			action_point = action_point->getParent();
		}
	}
	BinarySearchTree<Key, Value>::remove(key);
	fixHeights(action_point);
	remove_fix(action_point);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::remove_fix(AVLNode<Key, Value>* node){
	if(node == nullptr){
		return;
	}
	int balance = node->getBalance();
	if(balance < -1){
		if(node->getLeft()->getBalance()<=0){
			//Left Left Case
			BinarySearchTree<Key, Value>::rotateRight(node);
			fixHeights(node);
		}else{
			//Left Right Case
			BinarySearchTree<Key, Value>::rotateLeft(node->getLeft());
			fixHeights(node->getLeft()->getLeft());
			BinarySearchTree<Key, Value>::rotateRight(node);
			fixHeights(node);
		}
	}
	if(balance > 1){
		if(node->getRight()->getBalance() >= 0){
			//Right Right Case
			BinarySearchTree<Key, Value>::rotateLeft(node);
			fixHeights(node);
		}else{
			//Right Left Case
			BinarySearchTree<Key, Value>::rotateRight(node->getRight());
			fixHeights(node->getRight()->getRight());
			BinarySearchTree<Key, Value>::rotateLeft(node);
			fixHeights(node);
		}
	}
	remove_fix(node->getParent());
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::insert_fix(AVLNode<Key, Value>* node, AVLNode<Key, Value>* inserted){
	if(node == nullptr){
		return;
	}
	int balance = node->getBalance();
	if(balance!=-1 && balance!= 1){
		if(balance < -1){
			if(inserted->getKey() < node->getLeft()->getKey()){
				//Left Left Case
				BinarySearchTree<Key, Value>::rotateRight(node);
				fixHeights(node);
			}else{
				//Left Right Case
				BinarySearchTree<Key, Value>::rotateLeft(node->getLeft());
				fixHeights(node->getLeft()->getLeft());
				BinarySearchTree<Key, Value>::rotateRight(node);
				fixHeights(node);
			}
		}else if(balance > 1){
			if(inserted->getKey() < node->getRight()->getKey()){
				//Right Left Case
				BinarySearchTree<Key, Value>::rotateRight(node->getRight());
				fixHeights(node->getRight()->getRight());
				BinarySearchTree<Key, Value>::rotateLeft(node);
				fixHeights(node);
			}else{
				//Right Right Case
				BinarySearchTree<Key, Value>::rotateLeft(node);
				fixHeights(node);
			}
		}
	}
	insert_fix(node->getParent(), inserted);
}

/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif
