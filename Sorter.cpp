#include <iostream>
#include "Sorter.h"

// Compares consecutive items, if item one is bigger than item two, swap the values
// repeat this process until the array has been sorted.
void Sorter::bubbleSort(int * a, int length) {
    int outer, inner;
    // Counting down from the size of the array
    for(outer = length - 1; outer > 0; outer--){
        // Count up to the size of the array comparing pairs
        for(inner = 0; inner < outer; inner++){
            // If item one is bigger than item two swap the values around
            if(a[inner] > a[inner + 1]){
                int temp = a[inner];
                a[inner] = a[inner + 1];
                a[inner + 1] = temp;
            }
        }
    }
}

// Iterate over the array, each time keeping track of current minimum number from the unsorted
// partition of the array. We compare the current minimum to the current item in the unsorted partition
// we are on, if it's smaller the item becomes the new minimum. At the end of each iteration the minimum gets swapped
// with the start of the unsorted array eventually causing the array to be sorted.
void Sorter::selectionSort(int * a, int length) {
    int outer, inner, min;
    // Count up to the size of the array
    for(outer = 0; outer < length - 1; outer++){
        // The current index becomes the minimum as it is the start of the unsorted partition
        min = outer;
        // Compare the minimum to each item in the unsorted partition, if the item is less than the minimum
        // it becomes the new minimum
        for(inner = outer + 1; inner < length; inner++){
            if(a[inner] < a[min]){
                min = inner;
            }
        }
        // Swap the minimum with the start of the unsorted partition
        int temp = a[outer];
        a[outer] = a[min];
        a[min] = temp;
    }
}

// Iterate over the array comparing the current item to the item on its left, if the item on the left is larger
// we swap the values and compare to the left again. We do this until the item on the left is smaller at
// which point we increment the loop
void Sorter::insertionSort(int *a, int length) {
    int i, j, tmp;
    // Counting up to the size of the array
    for(i = 1; i < length; i++){
        j = i;
        // Keep looping while the item to the left of the current item is larger, swapping the values each time.
        while(j > 0 && a[j - 1] > a[j]){
            tmp = a[j];
            a[j] = a[j - 1];
            a[j - 1] = tmp;
            j--;
        }
    }
}

// Sort the array by using comparing elements in the array similar to insertion sort except
// using a gap between the items. This lets us sort the array without having to move every item each time.
void Sorter::shellSort(int *a, int length) {
    int i, j, gap, temp;

    // Set the starting gap to be half the array, reduce the size of the gap each iteration by half
    for(gap = length / 2; gap > 0; gap /= 2){

        // Essentially doing a insertion sort with a gap between numbers
        for(i = gap; i < length; i++){

            // Save the value of the item at i for later insertion
            temp = a[i];

            // Loop comparing items at j - gap to our saved value, if the item on the left is larger
            // swap it with the item at j until the item to the left is smaller
            for(j = i; j >= gap; j -= gap){
                if(temp < a[j - gap]){
                    a[j] = a[j - gap];
                }
                else {
                    break;
                }
            }

            // Put our saved value at j and begin the next loop
            a[j] = temp;
        }
    }
}

// This just gives us a method to call that doesn't require a second array
void Sorter::mergeSort(int *a, int length) {
    int arr[length];
    mergeSort(a, 0, length, arr);
}

// Sort the array by recursively breaking it up into smaller arrays, sorting them then joining them with the other arrays
// at each recursion level going up we are creating bigger arrays until we have one large sorted array.
void Sorter::mergeSort(int *a, int first, int last, int *tempArray) {
    if(last - first > 1){
        // Find the middle of the current array
        int middle = (first + last)/2;
        // Recursively branch out splitting the array up, then sorting and merging them
        mergeSort(a, first, middle, tempArray);
        mergeSort(a, middle, last, tempArray);
        merge(a, first, middle, last, tempArray);
    }
}

// Merge the two arrays together to solve the sub problem
void Sorter::merge(int *a, int first, int middle, int last, int *tempArray) {
    int i = first, j = middle, k;
    for(k = 0; i < middle && j < last; k++){
        if(a[i] <= a[j])
            tempArray[k] = a[i++];
        else
            tempArray[k] = a[j++];
    }
    for(; i < middle; k++)
        tempArray[k] = a[i++];
    for(; j <last; k++)
        tempArray[k] = a[j++];

    // Set the actual arrays values
    for(int index = 0; index < last - first; index++){
        a[first + index] = tempArray[index];
    }
}

// This lets us call the quicksort by only giving it an array and a length
void Sorter::quickSort(int *a, int length) {
    quickSort(a, 0, length - 1, length);
}

// Sort the array using by recursively using a pivot point in the array splitting it into two partitions and finding
// the position of the pivot until the entire array is sorted.
void Sorter::quickSort(int *a, int first, int last, int length) {
    if(first < last){
        int pivot = partition(a, first, last);
        // Recursively call the quicksort on the left and right of array of the pivot
        quickSort(a, first, pivot - 1, length);
        quickSort(a, pivot + 1, last, length);
    }
}

// Returns index of a pivot point finding its correct location in the array
int Sorter::partition(int *a, int first, int last) {
    int p = first, pivot = a[first], location;

    // Loop to the end of the partition
    for (location = first + 1; location <= last; location++) {
        // Compare the pivot to the current item, if the pivot is larger swap the items and increment p
        if (pivot > a[location]) {
            a[p] = a[location];
            a[location] = a[p + 1];
            a[p + 1] = pivot;
            p++;
        }
    }
    return p;
}


// Sort the array digit by digit for each item in the array, example: 11, 2, 100 would be sorted by 1's
// then 10's then 100's for each element in the array. Meaning the first loop would be 100, 11, 2. The second:
// 100, 2, 11 and finally the third loop: 2, 11, 100.

// Original code sample obtained via: https://www.geeksforgeeks.org/radix-sort/
void Sorter::radixSort(int *a, int length) {

    // Find the highest value in the array
    int max = a[0];
    for (int i = 1; i < length; i++) {
        if (a[i] > max)
            max = a[i];
    }

    // Here were looping over the array based on the digits in max, for example if max was 1000 we would loop 4 times
    // where exp was 1, 10, 100, and 1000 respectively
    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(a, length, exp); // Calling the countsort on the array using the current digit spot
}

// sort an array of numbers by their value at digit spot exp, for example if  a was [32, 1, 13] and exp was 1,
// the sorted array would be [1, 32, 13]
void Sorter::countSort(int *a, int length, int exp){
    int output[length]; // temp array
    int i, count[10] = {0};

    // Count the occurances of digits 0-9 at the exp, example num occurances of 1 at the 10's spot
    for (i = 0; i < length; i++) {
        count[(a[i] / exp) % 10]++;
    }

    // Here we are modifying the count array to indicate the position of each item in the output
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // loop the length of the array backwards and set the output arrays value
    for (i = length - 1; i >= 0; i--) {
        // Get the index from the count array and assign the value from input array
        output[count[(a[i] / exp) % 10] - 1] = a[i];
        // Decrease index so that duplicates will be placed one index lower
        count[(a[i] / exp) % 10]--;
    }

    // Set the actual array
    for (i = 0; i < length; i++)
        a[i] = output[i];
}
