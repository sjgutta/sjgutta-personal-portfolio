#include "splay.h"
#include <iostream>

using namespace std;

int main() {
    SplayTree<int, int> bst;
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
    pair<int, int> fifteen(15, 15);
    pair<int, int> sixteen(16, 16);
    pair<int, int> seventeen(17, 17);
    pair<int, int> eighteen(18, 18);
    pair<int, int> nineteen(19, 19);
    //pair<int, int> j(9, 9);
    bst.insert(two);
    bst.insert(three);
    bst.insert(four);
    bst.insert(five);
    bst.insert(six);
    bst.insert(seven);
    bst.insert(one);
    /*bst.insert(seven);
    bst.insert(two);
    bst.insert(five);
    bst.insert(eight);
    bst.insert(six);*/
    //bst.insert(ten);
    //bst.insert(twelve);
    //bst.insert(fourteen);
    //bst.insert(eighteen);
    //bst.insert(sixteen);
    //bst.print();
    //bst.remove(11);
    //bst.remove(6);
    cout << bst.report() << endl;
    bst.print();
}