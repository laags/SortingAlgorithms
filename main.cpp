#include <iostream>
#include <iterator>
#include <regex>
#include <chrono>
#include "Sorter.h"
#include "FileIO.h"

// Array Variables
int * original;
int * copy;
int size;

// Splits a users command at the space, parses the number and then returns it as an int
int getNumber(std::string userInput){
    return stoi(userInput.substr(0, userInput.find(" ")));
}

// Resets the array we are using for sorting back to the original state
void resetArray(){
    for(int i = 0; i < size; i++)
    {
        copy[i] = original[i];
    }
}

int main() {
    // Regex for validating commands
    std::regex withWriteRegex("^[1-9][0-9]*\\s[W]$");
    std::regex withoutWriteRegex("^[1-9][0-9]*$");

    // Get user input for the size of the array, parse it for the command and the number
    std::string userInput;
    bool writeFlag = false;
    std::cout << "Enter an array size: " << std::endl;
    while(true) {
        std::getline(std::cin, userInput);

        if(regex_match(userInput, withWriteRegex) && userInput != "1 W"){
            writeFlag = true;
            break;
        }

        else if (regex_match(userInput, withoutWriteRegex) && userInput != "1"){
            break;
        }

        std::cout << "Invalid command please try again: " << std::endl;
    }

    // User the number we received from input to create the array
    size = getNumber(userInput);
    original = new int [size];
    copy = new int [size];

    // Populate the array with random numbers
    srand(time(0));
    for (int i = 0; i < size; i++){
        original[i] = rand();
    }

    // BUBBLE SORT
    resetArray();
    auto start = std::chrono::high_resolution_clock::now();
    Sorter::bubbleSort(copy, size);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << std::endl << "Bubble Sort: " << elapsed.count() << std::endl;
    if(writeFlag)
        FileIO::write(copy, size, "bubblesort.txt");

    // SELECTION SORT
    resetArray();
    start = std::chrono::high_resolution_clock::now();
    Sorter::selectionSort(copy, size);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << std::endl << "Selection Sort: " << elapsed.count() << std::endl;
    if(writeFlag)
        FileIO::write(copy, size, "selectionsort.txt");

    // INSERTION SORT
    resetArray();
    start = std::chrono::high_resolution_clock::now();
    Sorter::insertionSort(copy, size);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << std::endl << "Insertion Sort: " << elapsed.count() << std::endl;
    if(writeFlag)
        FileIO::write(copy, size, "insertionsort.txt");

    // SHELL SORT
    resetArray();
    start = std::chrono::high_resolution_clock::now();
    Sorter::shellSort(copy, size);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << std::endl << "Shell Sort: " << elapsed.count() << std::endl;
    if(writeFlag)
        FileIO::write(copy, size, "shellsort.txt");

    // MERGE SORT
    resetArray();
    start = std::chrono::high_resolution_clock::now();
    Sorter::mergeSort(copy, size);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << std::endl << "Merge Sort: " << elapsed.count() << std::endl;
    if(writeFlag)
        FileIO::write(copy, size, "mergesort.txt");

    // QUICK SORT
    resetArray();
    start = std::chrono::high_resolution_clock::now();
    Sorter::quickSort(copy, size);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << std::endl << "Quick Sort: " << elapsed.count() << std::endl;
    if(writeFlag)
        FileIO::write(copy, size, "quicksort.txt");

    // RADIX SORT
    resetArray();
    start = std::chrono::high_resolution_clock::now();
    Sorter::radixSort(copy, size);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << std::endl << "Radix Sort: " << elapsed.count() << std::endl;
    if(writeFlag)
        FileIO::write(copy, size, "radixsort.txt");

    return 0;
}