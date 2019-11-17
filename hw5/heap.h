//implementation of templated minheap

template <typename T>
class MinHeap {
    private:
    struct Node{
            Node(T data, int priority, int position);
            T data;
            int priority;
            int position;
        }

    public:
    MinHeap (int d);
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
        std::vector<Node*> order

};

template <typename T>
MinHeap<T>::MinHeap(int d){
    this->d = d;
    this->current_call = 0;
}

template <typename T>
MinHeap<T>::~MinHeap(){
    for(int i=0; i<order.size();i++){
        delete order[i];
    }
}

template <typename T>
MinHeap<T>::Node::Node(T item, int priority, int position):data(item), 
    priority(priority), position(position){

}

template <typename T>
int MinHeap<T>::add(T item, int priority){
    Node* temp = new Node(item, priority, heap.size());
    heap.push_back(temp);
    order.push_back(temp);
    trickleUp(heap.size()-1);
}

template <typename T>
const T & MinHeap<T>::peek () const{
    return heap[0]->data;
}

template <typename T>
void MinHeap<T>::remove(){
    swap(0, heap.size()-1);
    heap[heap.size()-1]->position = -1;
    heap.pop_back();
    trickleDown(0);
}

template <typename T>
bool MinHeap<T>::isEmpty(){
    if(heap.empty()){
        return True;
    }else{
        return False;
    }
}

template <typename T>
void MinHeap<T>::swap(int pos1, int pos2){
    Node* temp = heap[pos1];
    temp->position = pos2;
    heap[pos1] = heap[pos2];
    heap[pos1]->position = pos1;
    heap[pos2] = temp;
}

template <typename T>
void MinHeap<T>::update(int nth, int priority){
    Node* temp = order[nth];
    if(temp->position==-1){
        return;
    }
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
    if (pos > 0 && heap[pos]->priority < heap[(pos-1)/d]->priority){
        swap(pos, (pos-1)/d);
        trickleUp((pos-1)/d);
    }
}

template <typename T>
void MinHeap<T>::trickleDown(int pos){
    if(d*pos+1<heap.size()){
        int smallest_child = pos*d + 1;
        for(int j=1; j<d; j++){
            if(pos*d+1+j<heap.size()){
                if(heap[pos*d+1+j]->priority < heap[smallest_child]->priority){
                    smallest_child = pos*d+1+j;
                }
            }
        }
        if (heap[smallest_child]->priority < heap[pos]->priority){
            swap(smallest_child, pos);
            trickleDown(smallest_child);
        }
    }
}