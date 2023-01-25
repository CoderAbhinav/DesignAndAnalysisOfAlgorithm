#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++) {

        if (arr[j] < pivot) {
            i++; 
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high) {

        int pi = partition(arr, low, high);
 
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

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
