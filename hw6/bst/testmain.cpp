#include "print_bst.h"
#include <iostream>

using namespace std;

int main() {
    BinarySearchTree<int, int> bst;
    pair<int, int> one(1, 1);
    pair<int, int> two(2, 2);
    pair<int, int> three(3, 3);
    pair<int, int> four(4, 4);
    pair<int, int> five(5, 5);
    pair<int, int> six(6, 6);
    pair<int, int> seven(7, 7);
    pair<int, int> eight(8, 8);
    pair<int, int> nine(9, 9);
    pair<int, int> ten(10, 10);
    pair<int, int> eleven(11, 11);
    pair<int, int> twelve(12, 12);
    pair<int, int> thirteen(13, 13);
    pair<int, int> fourteen(14, 14);
    pair<int, int> sixteen(16, 16);
    pair<int, int> eighteen(18, 18);
    pair<int, int> nineteen(19, 19);
    //pair<int, int> j(9, 9);
    bst.insert(ten);
    bst.insert(fourteen);
    bst.insert(thirteen);
    bst.insert(eighteen);
    bst.insert(twelve);
    bst.insert(sixteen);
    bst.insert(nineteen);
    bst.print();
    //bst.remove(14);
    //bst.remove(11);
    bst.print();
}