#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;


void merge(vector<int>& v, int low, int mid, int high) {
    // if (low >= high) return;

    vector<int> temp(high - low + 1);

    int i = low, j = mid + 1, trg = 0;

    while (i <= mid && j <= high) {
        if (v[i] < v[j]) {
            temp[trg] = v[i];
            i++;
        } else {
            temp[trg] = v[j];
            j++;
        }
        trg++;
    }

    while (i <= mid) {
        temp[trg] = v[i];
        i++; trg++;
    }

    while (j <= high) {
        temp[trg] = v[j];
        j++; trg++;
    }

    for (int i = 0; i < temp.size(); i++) {
        v[low + i] = temp[i];
    }
}

void mergeSort(vector<int>& v, int low, int high) {
    if (low >= high) return;
    int mid = low + (high - low) / 2;

    mergeSort(v, low, mid);
    mergeSort(v, mid + 1, high);

    merge(v, low, mid, high);
}

void mergeSort(vector<int>& v) {
    mergeSort(v, 0, v.size() - 1);
}

int main(int argc, char const *argv[])
{
    int n; cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    chrono::steady_clock::time_point start = high_resolution_clock::now();
    mergeSort(v);
    chrono::steady_clock::time_point stop = high_resolution_clock::now();

    // for (int i = 0; i < n; i++) cout << v[i] << "\t";

    chrono::microseconds duration = duration_cast<microseconds>(stop - start);
    cout << "\nEXEC TIME: " << duration.count() << " MS" << "\n";
    return 0;
}
