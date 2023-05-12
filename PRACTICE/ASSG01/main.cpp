#include <iostream>
#include <vector>
#include "sort/quicksort.h"

using namespace std;


bool comp(int a, int b) {
    return a < b;
}


/**
 * @brief main function is the entry point of C++ code
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    vector<int> arr = {8, 7, 1, 5, 9};

    quickSort(arr, comp);

    return 0;
}



