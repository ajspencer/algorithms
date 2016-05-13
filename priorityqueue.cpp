#include<stdio.h>
#include <vector>
using namespace std;

/*
 * Author: Andrew Spencer
 * Description of program: implementon of a priority queue
 * Description of data structure:
 * A priority queue is a data structure that is often implemented in a heap. 
 *
 * TODO: figure out how to generalize this for data types other than an integer
 */ 

/**
 * Declaration of the priority queue
 */
class PriorityQueue {
    public: 
        PriorityQueue();
        void insert(int i);
        int maximum();
        int extractMax();
    private:
        vector<int> *a;
        void fixHeapProperty(int index);
};

/**
 * Constructor for the priority queue
 */
PriorityQueue::PriorityQueue() {
    vector<int> *vect = new vector<int>;
    this->a = vect;
}

/**
 * To insert into the priorty queue, we simply add the item we are inserting at the top and then ensure that the heap property is maintained. 
 */
void PriorityQueue::insert(int i) {
    a->insert(a->begin(), i);
    fixHeapProperty(0);
}

/**
 * To extract the top element, we simply replace it with the element at the end, and erase the other copy of that elemetn from our priority queue. We find the right place for this element by using the fix heap property method.
 */
int PriorityQueue::extractMax() {
    int toReturn = a->at(0);
    a->at(0) = a->at(a->size() - 1);
    a->erase(a->end() - 1);
    fixHeapProperty(0);
    return toReturn;
}

/**
 * This method takes a heap and fixes the heap property given an index. We assume that both children of the indicies are valid heaps.
 */
void PriorityQueue::fixHeapProperty(int index) {
    //If the index is a leaf, return since it does not violate the max heap property
    if(index > a->size()/2 - 1) return;
    int indexOfLargest = index;
    //See if the max is on the left
    if(2*index + 1 < a->size() && a->at(indexOfLargest) < a->at(2*(index) + 1)) indexOfLargest = 2*index + 1;
    //See if the max is on the right
    if(2*index + 2 < a->size() && a->at(indexOfLargest) < a->at(2*(index) + 2)) indexOfLargest = 2*index+2;
    //If the max is the index itself, we don't need to do anything
    if(indexOfLargest == index) return;
    //otherwise we need to fix the heap property of the subheap we swapped
    else {
        //Swap the values to make sure the heap property is satisfied
        int temp = a->at(indexOfLargest);
        a->at(indexOfLargest) = a->at(index);
        a->at(index) = temp;
        //Fix the heap property of the one we switched
        fixHeapProperty(indexOfLargest);
    }

}

/**
 * By the heap property, the maximum element will be the element at the first index.
 */
int PriorityQueue::maximum() {
    return a->at(0);
}


/**
 *Main code for testing
 */
int main() {
    PriorityQueue *p = new PriorityQueue();
    p->insert(1);
    p->insert(2);
    p->insert(3);
    p->insert(5);
    p->insert(6);
    printf("%d\n", p->maximum());
    p->extractMax();
    printf("%d\n", p->maximum());
    return 0;
}
