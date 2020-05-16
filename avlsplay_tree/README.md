# Sajan Gutta - Implementing Trees - CSCI 104
This assignment was completed for my Data Structures Class. It was written in C++ and required me to implement classes for a Binary Search Tree, an AVL Tree, and a Splay Tree. The AVL and Splay Trees both inherited from the Binary Search Tree. Implementing these data structures from scratch was very intensive and not something usually required in a professional environment. However, it did help me to gain a better understanding of the data structures and practice my Object-Oriented Programming in C++.
## Binary Search Tree
* The implementation for the Binary Search Tree (BST) can be found in the 'bst' directory.
* This implementation just needs to be included in another file and then the BST class can be easily used in one's own program.
* The main functions provided in the interface of the BST for a user to use it in their own program are insert(), clear(), and print(). Everything else is used internally to help manage the data of the BST and becomes very important in the AVL and Splay trees.
* This BST class also has functions for performing rotations about specific nodes. These functions become useful in the AVL and Splay Trees.
## AVL tree
* This implementation can be found in the 'avl' directory.
* This class inherits from the BST class written above and overrides the necessary functions. It also uses a special AVLNode that stores height information to help when balancing the AVL tree. A number of functions such as fixHeights are used to maintain this balance.
* The main methods that were overridden are insert() and remove(). These are done in very specific ways in AVL Trees. Both of these functions utilize a number of internal functions that were written to make operations such as rotations in the tree easier to organize within those insert and remove functions.
## Splay Tree
* This implementation can be found in the 'splay' directory.
* This class also inherits from the BST class and overrides the necessary functions.
* The primary functions implemented that a user can call were insert() and remove().
* A splay function was also written that is used in the relevant cases throughout insert() and remove().
## The Analysis folder
In the analysis directory you will find some files that were used to analyze how these data structures function. The file there uses them to perform a number of operations by adding a long list of words to each tree type. It measures the length of time required by each tree to insert all of the words and arrange itself. The goal is to see if the runtimes returned by these data structures act how one would theoretically expect a BST, an AVL Tree, and a Splay Tree to act in those different cases. The README in that directory provides more information.
