#pragma once
#include <vector>

namespace QuickSortHelper
{
    /**
     * @brief Partitions the array around a pivot element.
     *
     * @tparam T The type of elements in the array.
     * @tparam Comparator The type of the comparison function.
     * @param arr The array to be partitioned.
     * @param low The starting index of the partition.
     * @param high The ending index of the partition.
     * @param comp The comparison function for sorting.
     * @return The index of the pivot element after partitioning.
     */
    template <typename T, typename Comparator>
    int partition(std::vector<T> &arr, int low, int high, Comparator comp)
    {
        T pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            if (comp(arr[j], pivot))
            {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }

        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    /**
     * @brief Sorts the array using the QuickSort algorithm.
     *
     * @tparam T The type of elements in the array.
     * @tparam Comparator The type of the comparison function.
     * @param arr The array to be sorted.
     * @param low The starting index of the sorting range.
     * @param high The ending index of the sorting range.
     * @param comp The comparison function for sorting.
     */
    template <typename T, typename Comparator>
    void quickSort(std::vector<T> &arr, int low, int high, Comparator comp)
    {
        if (low < high)
        {
            int pivotIndex = partition(arr, low, high, comp);

            quickSort(arr, low, pivotIndex - 1, comp);
            quickSort(arr, pivotIndex + 1, high, comp);
        }
    }

}

/**
 * @brief Sorts the array using the QuickSort algorithm.
 *
 * @code
 * bool comp(int a, int b) {
    return a < b;
 * }
 * vector<int> arr = {8, 7, 1, 5, 9};
 * quickSort(arr, comp);
 * @endcode
 * 
 * @tparam T The type of elements in the array.
 * @tparam Comparator The type of the comparison function.
 * @param arr The array to be sorted.
 * @param comp The comparison function for sorting.
 * 
 */
template<typename T, class _Comparator>
void quickSort(std::vector<T>& arr, _Comparator comp) {
    int size = arr.size();
    QuickSortHelper::quickSort(arr, 0, size - 1, comp);
}