#ifndef ASSIGNMENT3_SORTER_H
#define ASSIGNMENT3_SORTER_H


class Sorter {
public:
    static void bubbleSort(int[], int length);
    static void selectionSort(int[], int length);
    static void insertionSort(int a[], int length);
    static void shellSort(int a[], int length);
    static void mergeSort(int[], int length);
    static void mergeSort(int[], int first, int last, int[]);
    static void merge(int[], int first, int mid, int last, int[]);
    static void quickSort(int[], int first, int last, int length);
    static void quickSort(int[], int length);
    static int partition(int[], int first, int last);
    static void radixSort(int[], int length);
    static void countSort(int[], int length, int exp);
};


#endif //ASSIGNMENT3_SORTER_H
