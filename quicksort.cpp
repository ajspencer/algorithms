
#include <iostream>
#include <fstream>
#include "stdlib.h"

//Because this makes small programs easier
using namespace std;
//Function prototypes
int partition(int a[], int startingIndex, int endingIndex);
void swap(int a[], int positionOne, int positionTwo);
void printArray(int a[], int length);

/**
 * Quicksort aims to partially sort sections of the array, then use itself on these partially sorted sections of the array. 
 * Eventually, quicksort brings the array into groups of completely sorted elements. Notice that 1 is a group of completely so
 * rted elements, and that the starting index must always be less than the ending index (prevents running off the edge in groups 
 * of one). Quicksort sorts sections by picking a "pivot" point and arranging all elements of the array such that each element 
 * on the left is less than or equal to the pivot point, and each element on the right is greater than or equal to the pivot point.
 * @param int a[] the array being sorted
 * @param int startingIndex the start of the (sub)array being sorted
 * @param int endingIndex the end of the (sub)array being sorted 
 */
void quicksort(int a[], int startingIndex, int endingIndex) {
   if(startingIndex < endingIndex) {
      int pivotMedian = partition(a, startingIndex, endingIndex);
      quicksort(a, startingIndex, pivotMedian);
      quicksort(a, pivotMedian + 1, endingIndex);
   }
}

/**
 * The partitioning function, which splits the array into one group of elements less than or equal to the partition and one 
 * group of elements greater than or equal to the partition. 
 * @param int a[] the array being sorted
 * @param int startingIndex the start of the (sub)array being sorted
 * @param int endingIndex the end of the (sub)array being sorted 
 * @return j the location of the 2nd pointer once 
 */
int partition(int a[], int startingIndex, int endingIndex) {
    //use a random value within the range of the (sub)array to avoid the worst case input
    int randomIndex = rand() % (endingIndex - startingIndex + 1) + startingIndex;
    swap(a, startingIndex, randomIndex);
    int pivot = a[startingIndex];
    int i = startingIndex; 
    int j = endingIndex; 
    //While the two pointers are on the correct side, switch values below the pivot to the left half and values above to the right half. 
    while(i < j) {
        if(a[j] >= pivot)                          j--; 
        if(a[i] < pivot)                           i++;
        if(a[j] < pivot && a[i] >= pivot && i < j) swap(a, j, i);
    }
    return j; 
}

/**
 * Helper function used to swap two variables. Notice, you can swap two variables without the use of a placeHolder variable, 
 * but this is not something you should do unless you have to! I like readable code and bitwise operators, in general, are 
 * less readable than creating one additional local variable. 
 * @param int a[] the array the variables are located in.
 * @param int positionOne the position of the first variable being swapped.
 * @param int positionTwo the position of the second variable being swapped. 
 */
void swap(int a[], int positionOne, int positionTwo) {
    int placeHolder = a[positionTwo];
    a[positionTwo] = a[positionOne];
    a[positionOne] = placeHolder; 
}

/**
 * Helper function to print the array
 * @param int a[] the array being printed
 * @param int length the length of the array being printed
 */
void printArray(int a[], int length) {
    for(int i = 0; i < length; i++) {
        cout << a[i] << " ";
    }
    cout << "\n";
}

int main(int argc, char *argv[]) {
    int a[1000000]; 
    for(int i = 0; i <1000000; i++) {
        a[i] = rand() % 100000;
    }
    quicksort(a, 0, sizeof(a)/sizeof(a[0]) - 1);
    printArray(a, sizeof(a)/sizeof(a[0]));
    return 0; 
}
