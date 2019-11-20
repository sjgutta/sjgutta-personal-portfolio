//implementation of templated minheap
#include <vector>
#include <stdexcept>

template <typename T>
class MinHeap {
    private:
    struct Node{
            Node(T data, int priority_val, int position_val);
            T data;
            int priority;
            int position;
        };

    public:
    MinHeap (int d_val);
    /* Constructor that builds a d-ary Min Heap
        This should work for any d >= 2,
        but doesn't have to do anything for smaller d.*/

    ~MinHeap ();

    int add (T item, int priority);
        /* adds the item to the heap, with the given priority. 
        multiple identical items can be in the heap simultaneously. 
        Returns the number of times add has been called prior to this
        call (for use with the update function).*/

    const T & peek () const;
        /* returns the element with smallest priority.  
        If two elements have the same priority, use operator< on the 
        T data, and return the one with smaller data.*/

    void remove ();
        /* removes the element with smallest priority, with the same tie-breaker
        as peek. */

    void update (int nth, int priority);
        /* finds the nth item (where nth is 0-based) that has ever been added 
        to the heap (the node that was created on the nth call to add), 
        and updates its priority accordingly. */

    bool isEmpty ();
        /* returns true iff there are no elements on the heap. */

    protected:
    //helper functions to be used in other interface functions
    void trickleUp(int pos);

    void swap(int pos1, int pos2);

    void trickleDown(int pos);

   private:
      // whatever you need to naturally store things.
      // You may also add helper functions here.
        std::vector<Node*> heap;
        int d;
        //vector used for updating priority
        //tracks order of being added
        std::vector<Node*> order;

};

template <typename T>
MinHeap<T>::MinHeap(int d_val){
    //construct with proper value for the d-ary heap
    if(d<2){
        throw std::invalid_argument("MinHeap must have a d value of 2 or more");
    }
    this->d = d_val;
}

template <typename T>
MinHeap<T>::~MinHeap(){
    //clean up memory
    //order vector holds all nodes that were added to the heap
    for(int i=0; i<int(order.size());i++){
        delete order[i];
    }
}

template <typename T>
MinHeap<T>::Node::Node(T item, int priority_val, int position_val):data(item), 
    priority(priority_val), position(position_val){

}

template <typename T>
int MinHeap<T>::add(T item, int priority){
    //dynamically allocate new node, add to actual heap and order vector
    Node* temp = new Node(item, priority, int(heap.size());
    heap.push_back(temp);
    order.push_back(temp);
    //now trickle up to put in proper place
    trickleUp(int(heap.size())-1);
    //return number of add calls before this one
    return int(order.size())-1;
}

template <typename T>
const T & MinHeap<T>::peek () const{
    //use first item in the vector for peek to return top of heap
    if(!heap.empty()){
        return heap[0]->data;
    }else{
        throw std::logic_error("MinHeap is empty. There is nothing to peek at.");
    }
}

template <typename T>
void MinHeap<T>::remove(){
    if(heap.empty()){
        throw std::logic_error("There is nothing to remove");
    }
    //swap top to bottom
    swap(0, int(heap.size())-1);
    //effectively remove the node by setting position to -1
    //pop it from back of the actual heap vector as well
    heap[heap.size()-1]->position = -1;
    heap.pop_back();
    //take node swapped to top and put it back where it belongs
    trickleDown(0);
}

template <typename T>
bool MinHeap<T>::isEmpty(){
    //use heap vector to determine if heap is empty
    if(heap.empty()){
        return true;
    }else{
        return false;
    }
}

template <typename T>
void MinHeap<T>::swap(int pos1, int pos2){
    //swaps position members and indices of nodes at pos1 and pos2
    Node* temp = heap[pos1];
    temp->position = pos2;
    heap[pos1] = heap[pos2];
    heap[pos1]->position = pos1;
    heap[pos2] = temp;
}

template <typename T>
void MinHeap<T>::update(int nth, int priority){
    if(nth<0 || nth>=int(order.size())){
        throw std::invalid_argument("Tried to update an invalid node");
    }
    //change priority using order array to find proper node
    Node* temp = order[nth];
    //if position is -1, the node was previously removed so nothing happens
    if(temp->position==-1){
        return;
    }
    //trickle the item up or down based on if priority was raised or lowered
    if(priority > temp->priority){
        temp->priority = priority;
        trickleDown(temp->position);
    }
    if(priority < temp->priority){
        temp->priority = priority;
        trickleUp(temp->position);
    }
}

template <typename T>
void MinHeap<T>::trickleUp(int pos){
    //determine if node has lower priority than parent and trickle up
    //call recursively if this happens
    //use the T item as a tiebreaker value
    if ((pos > 0 && heap[pos]->priority < heap[(pos-1)/d]->priority) || 
        (heap[pos]->priority == heap[(pos-1)/d]->priority &&  heap[pos]->data < heap[(pos-1)/d]->data)){
        swap(pos, (pos-1)/d);
        trickleUp((pos-1)/d);
    }
}

template <typename T>
void MinHeap<T>::trickleDown(int pos){
    //make sure not a child node being trickled
    if(d*pos+1<int(heap.size())){
        //find the smallest child priority to swap with
        //use T item as a tiebreaker
        int smallest_child = pos*d + 1;
        for(int j=1; j<d; j++){
            if(pos*d+1+j<int(heap.size())){
                if(heap[pos*d+1+j]->priority < heap[smallest_child]->priority || 
                    (heap[pos*d+1+j]->priority == heap[smallest_child]->priority && 
                    heap[pos*d+1+j]->data < heap[smallest_child]->data)){
                    smallest_child = pos*d+1+j;
                }
            }
        }
        //once smallest child is found, make swap if necessary
        //use T item as tiebreaker
        //recursively call trickle down
        if (heap[smallest_child]->priority < heap[pos]->priority || 
            (heap[smallest_child]->priority == heap[pos]->priority &&
            heap[smallest_child]->data < heap[pos]->data)){
            swap(smallest_child, pos);
            trickleDown(smallest_child);
        }
    }
}