#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

/**
 * @brief swaps the variable values by pointer
 * 
 * @param a 
 * @param b 
 */
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief returns the partition
 * 
 * @param low 
 * @param high 
 * @return int* 
 */
int* partition(int* low, int* high) {
    int piviot = *high;
    int* i = (low - 1), *temp = low;

    while (temp <= high) {
        if (*temp < piviot) {
            i++;
            swap(temp, i);
        }

        temp++;
    }
    swap((i + 1), high);

    return ++i;
}

/**
 * @brief Function implementes sorting using quick sort algorithm
 * 
 * @param low pointer to start
 * @param high pointer to end
 */
void quickSort(int* low, int* high) {
    if (low < high) {
        int* pi =  partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

int main(int argc, char const *argv[])
{

    int n; cin >> n;

    int arr[n];

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    chrono::steady_clock::time_point start = high_resolution_clock::now();

    quickSort(arr, arr + n - 1);

    chrono::steady_clock::time_point stop = high_resolution_clock::now();

    chrono::microseconds duration = duration_cast<microseconds>(stop - start);

    for (int i = 0; i < n; i++){
        cout << arr[i] << "\t";
    }

    cout << "\n";

    cout << "EXEC TIME: " << duration.count() << " MS" << "\n";

    return 0;
}
