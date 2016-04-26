
#include <iostream>
#include <fstream>
#include "stdlib.h"

//Because this makes small programs easier
using namespace std;
//function prototype for print array
void printArray(int a[], int length, int start, int end);

/*
 * Merge sort is a divide and conquer algorithm. It breaks the array into smaller sub arrays, sorts them, and then combines the results.
 * When it combines the results, it makes a sorted array out of the two sorted halves. The array is broken down until there are sub arrays of length 1. 
 * The sub arrays of length 1 are combined, sorted, and then the length of each sub array doubles every step up until the whole is sorted.
 * @param array, the array being sorted
 * @param start, the start of the sub array being sorted. 0 initially.
 * @param end, the end of the sub array being sorted. array.length - 1 initially.
 */
void mergesort(int array[], int start, int end) {
    //Compute the middle of the array so you can divide the array into two seperate halves to be sorted
    int middle = (end + start)/2;
    //If the start is greater than or equal to the end (the length is 1), this is a base case, and we will return. 
    if(start >= end) {
        return;
    }
    else {
        //divide and sort two sub arrays
        mergesort(array, start, middle);
        mergesort(array, middle + 1, end);
    }
    //At this point the two subarray will always be sorted, so we combine them, ensuring that the result is sorted. 
    int firstHalf[middle - start + 1], secondHalf[end - middle];
    //This constructs a copy of the first half and the 2nd half of the array, which are the two sub arrays. 
    for(int i = start; i < end + 1; i++) {
        if(i <= middle) {
            firstHalf[i - start] = array[i];
        }
        else {
            secondHalf[i - middle - 1] = array[i];
        }
    }
    //Pointers for use in filling the array with the sorted results
    int currentPositionInFirstHalf = 0; 
    int currentPositionInSecondHalf = 0; 
    int currentPositionInArray = start; 
    //Go while the current position in the array is less than the length of the array being filled
    while(currentPositionInArray < start + end - start + 1) {
        //If the second half pointer is out off bounds, or the first half is in bounds and the first half element is smaller than the 2nd, move the first half. 
        //It is worth noting that both pointers will never be out of bounds
        if(currentPositionInSecondHalf >= end - middle || (currentPositionInFirstHalf < middle - start + 1 && firstHalf[currentPositionInFirstHalf] < secondHalf[currentPositionInSecondHalf])) {
            //I did not do that in one line because #cleanCodeIsCool
            array[currentPositionInArray] = firstHalf[currentPositionInFirstHalf];
            currentPositionInFirstHalf++;
        }
        else {
            array[currentPositionInArray] = secondHalf[currentPositionInSecondHalf];
            currentPositionInSecondHalf++;
        }
        currentPositionInArray++;
    }
}
/*
 * Helper function to print the array
 */
void printArray(int a[], int length, int start, int end) {
    for(int i = start; i < end + 1; i++) {
        cout << a[i] << " ";
    }
    cout << "\n";
    cout.flush();
}

int main(int argc, char *argv[]) {
    //testing 
    int b[1000000]; 
    for(int i = 0; i <1000000; i++) {
        b[i] = rand() % 100000;
    }
    //int b[] = {3, 3, 9, 1, 3, 9, 11};
    mergesort(b, 0, sizeof(b)/sizeof(b[0]) - 1);
    printArray(b, sizeof(b)/sizeof(b[0]), 0, sizeof(b)/sizeof(b[0]) - 1);
    return 0; 
}
