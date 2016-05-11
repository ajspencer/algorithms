#include<stdio.h>
#include <vector>
using namespace std;
/*
 * Author: Andrew Spencer
 * Description of program: implementation of heapsort
 * Description of algorithm:
 * The heap sort algorithm is an algoritm that takes an array and sorts it by first building a maxheap out of the array, and then constructing a sorted list from the max heap.
 */ 
void fixHeapProperty(vector<int>& a, int index, int heapSize) {
    //If the index is a leaf, return since it does not violate the max heap property
    if(index > heapSize/2 - 1) return;
    int indexOfLargest = index;
    //See if the max is on the left
    if(2*index + 1 < heapSize && a.at(indexOfLargest) < a.at(2*(index) + 1)) indexOfLargest = 2*index + 1;
    //See if the max is on the right
    if(2*index + 2 < heapSize && a.at(indexOfLargest) < a.at(2*(index) + 2)) indexOfLargest = 2*index+2;
    //If the max is the index itself, we don't need to do anything
    if(indexOfLargest == index) return;
    //otherwise we need to fix the heap property of the subheap we swapped
    else {
        //Swap the values to make sure the heap property is satisfied
        int temp = a.at(indexOfLargest);
        a.at(indexOfLargest) = a.at(index);
        a.at(index) = temp;
        //Fix the heap property of the one we switched
        fixHeapProperty(a, indexOfLargest, heapSize);
    }

}

/*
 * The make max heap algorithm works by assuming that the child of an element are valid max heaps, but the element itself may violate the max heap property. We use our fixHeapProperty method to ensure that the remaining node doesn't violate the max heap property. We start to construction halfway through the array, since the leaves of the array are all valid max heaps. 
 */
void makeMaxHeap(vector<int>& a) {
    for(int i = a.size()/2 - 1; i >= 0; i--) {
        fixHeapProperty(a, i, a.size()); 
        for(int i = 0; i < a.size(); i++) {
             printf("%d ", a.at(i));
        }
        printf("\n");
    }
}

/**
 * For the heap sort algorithm, we know that we can find the largest element at the top of the max heap, so we continually exchange that element with the last one and resume the max heap property.
 */
void heapSort(vector<int>&a) {
    makeMaxHeap(a);
    int currentHeapSize = a.size();
    for(int i = 0; i <a.size(); i++) {
        //Grab small element
        int temp = a.at(currentHeapSize - 1);
        //set the largest element in the back
        a.at(--currentHeapSize) = a.at(0);
        //Set the root to be small element
        a.at(0) = temp;
        //Fix the heap property
        fixHeapProperty(a, 0, currentHeapSize);
    }
}

/**
 *Main code for testing
 */
int main() {
    vector<int> vect;
    vect.push_back(0);
    vect.push_back(1);
    vect.push_back(3);
    vect.push_back(4);
    vect.push_back(2);
    heapSort(vect);
    for(int i = 0; i < vect.size(); i++) {
         printf("%d ", vect.at(i));
    }
    printf("\n");
    return 0;
}
