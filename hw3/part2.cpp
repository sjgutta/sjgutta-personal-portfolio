#include <iostream>

struct Node {
    int value;
    Node *next;
};

Node* funcB(Node* in) {
   if (in->next != nullptr) {
    funcB(in->next)->next = in;
   }
   return in;
}

Node* funcA(Node* in) {
    Node *out = in;
    while (out->next != nullptr) {
    out = out->next;
    }
    funcB(in)->next = NULL;
    return out;
}

int main(){
    Node* first = new Node;
    first->value = 1;
    Node* second = new Node;
    second->value = 2;
    Node* third = new Node;
    third->value = 3;
    Node* fourth = new Node;
    fourth->value = 4;
    Node* fifth = new Node;
    fifth->value = 5;
    first->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = fifth;
    fifth->next = nullptr;
    Node* result = funcA(first);
    while(result->next != nullptr){
        std::cout << result->value << std::endl;
        result = result->next;
    }
    std::cout << result->value << std::endl;
}