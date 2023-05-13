#include <iostream>
#include <vector>
#include <chrono>
#include <functional>
#include "sort/quicksort.h"
#include "sort/mergesort.h"

using namespace std;
using namespace std::chrono;

bool compare(int a, int b) {
    return a < b;
}

vector<int> getArrayFromUser(int n) {
    vector<int> res(n);
    for (int i = 0; i < n; i++) cin >> res[i];
    return res;
}

int main(int argc, char const *argv[])
{
    int n; cin >> n;
    vector<int> arr = getArrayFromUser(n);


    auto startTime = std::chrono::high_resolution_clock::now();

    // TODO: Quicksort Execute
    quickSort(arr, compare);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

    std::cout << "Code execution time: " << duration << " microseconds" << std::endl;

    for (int i = 0; i < n; i++) {
        cout << arr[i] << "\t";
    }
    return 0;
}



