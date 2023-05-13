#pragma once
#include <iostream>
#include <vector>
namespace MergeSortHelper
{

    /**
     * @brief Merge two sorted subarrays into a single sorted array.
     *
     * @tparam T The type of the elements in the array.
     * @param arr The array to be sorted.
     * @param low The starting index of the first subarray.
     * @param mid The ending index of the first subarray.
     * @param high The ending index of the second subarray.
     * @param comp The comparator function to compare elements.
     */
    template <typename T, typename Compare>
    void merge(std::vector<T> &arr, int low, int mid, int high, Compare comp)
    {
        int leftSize = mid - low + 1;
        int rightSize = high - mid;

        // Create temporary arrays to store the subarrays
        std::vector<T> leftArray(leftSize);
        std::vector<T> rightArray(rightSize);

        // Copy data to the temporary arrays
        for (int i = 0; i < leftSize; i++)
            leftArray[i] = arr[low + i];
        for (int j = 0; j < rightSize; j++)
            rightArray[j] = arr[mid + 1 + j];

        // Merge the two subarrays back into the original array
        int i = 0, j = 0, k = low;
        while (i < leftSize && j < rightSize)
        {
            if (comp(leftArray[i], rightArray[j]))
            {
                arr[k] = leftArray[i];
                i++;
            }
            else
            {
                arr[k] = rightArray[j];
                j++;
            }
            k++;
        }

        // Copy the remaining elements of the left subarray
        while (i < leftSize)
        {
            arr[k] = leftArray[i];
            i++;
            k++;
        }

        // Copy the remaining elements of the right subarray
        while (j < rightSize)
        {
            arr[k] = rightArray[j];
            j++;
            k++;
        }
    }

    /**
     * @brief MergeSort algorithm to sort an array.
     *
     * @tparam T The type of the elements in the array.
     * @param arr The array to be sorted.
     * @param low The starting index of the array.
     * @param high The ending index of the array.
     * @param comp The comparator function to compare elements.
     */
    template <typename T, typename Compare>
    void mergeSort(std::vector<T> &arr, int low, int high, Compare comp)
    {
        if (low < high)
        {
            int mid = low + (high - low) / 2;

            // Sort the first and second halves recursively
            mergeSort(arr, low, mid, comp);
            mergeSort(arr, mid + 1, high, comp);

            // Merge the sorted halves
            merge(arr, low, mid, high, comp);
        }
    }
} // namespace helper

/**
 * @brief MergeSort algorithm to sort an array using a comparator function.
 *
 * @tparam T The type of the elements in the array.
 * @tparam Compare The type of the comparator function.
 * @param arr The array to be sorted.
 * @param comp The comparator function to compare elements.
 */
template <typename T, typename Compare>
void mergeSort(std::vector<T> &arr, Compare comp)
{
    int n = arr.size();
    MergeSortHelper::mergeSort(arr, 0, n - 1, comp);
}