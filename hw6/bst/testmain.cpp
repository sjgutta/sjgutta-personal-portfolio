#include "print_bst.h"
#include <iostream>

using namespace std;

int main() {
    BinarySearchTree<int, int> bst;
    // pair<int, int> a(1, 1);
    pair<int, int> b(2, 2);
    pair<int, int> c(3, 3);
    pair<int, int> d(4, 4);
    pair<int, int> e(5, 5);
    pair<int, int> g(6, 6);
    pair<int, int> h(7, 7);
    pair<int, int> i(8, 8);
    //pair<int, int> j(9, 9);
    bst.insert(e);
    
    bst.insert(c);
    bst.insert(h);
    
    bst.insert(d);
    bst.insert(g);
    
    bst.insert(b);
    bst.insert(i);
    
    //bst.insert(a);
    //bst.insert(j);
    
    bst.print();
}