/**
 * @Description This program follows the KSmall algorithm using Recursive thinking
 *   This program finds the Kth smallest element in an array without
 *   needing to sort it This is done by partitioning the array around a pivot and
 *   then recursively searching through the relevant partition (or partitions) of the array
 *
 * @author Isaiah G. (StarID: 16437856)
 * @date Week 2 sunday 23:59
 * @instructor Jie Meichsner Ph.D
 *
 * @Comments 
 *   The partitions function takes an array and a pivot as input
 *   S1 is defined as elements in array <= pivot
 *   S2 is defined as elements in array > pivot
 *   Special actions are taken if S1 is empty (i.e. pivot is smallest)
 */

#include <iostream>
using namespace std;

/**
 * Partitioning of array segment(s) defined by arr[low..high] on pivot element (arr[low])
*  Elements less than or equal to pivot point will be there in S1
 * Elements greater than pivot will be there in S2
 *
 * @param arr   Pointer to array to be partitioned
 * @param low   Start index of segment to be partitioned
 * @param high  End index of pivot after partitioning
 * @return      The final index of the pivot after partitioning
 *
 * @pre  arr != nullptr, 0 <= low <= high
 * @post arr[low..pivotIndex-1] <= arr[pivotIndex] < arr[pivotIndex+1..high]
 */

int partition(int* arr, int low, int high) {
    int pivot = arr[low];
    int left  = low + 1;   // Scans from after the pivot
    int right = high;

    while (left <= right) {
        // Moves the left pointer to the right while the elements are <= pivot
        while (left <= right && arr[left] <= pivot) {
            left++;
        }
        // Moves the right pointer to the left while the elements are > pivot
        while (left <= right && arr[right] > pivot) {
            right--;
        }
        // Swaps the out of place elements
        if (left < right) {
            swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }

    // Points to the last element in S1 and only swaps if S1 is not empty
    if (right > low) {
        swap(arr[low], arr[right]);
    }
    // If the right == low and S1 is empty the pivot stays at arr[low] and no swap is needed

    return right;   // Final position of the pivot
}

/**
 * Finds the Kth smallest element in arr[low..high] by recursively partitioning the array
 * The first elements of the sub-arrays are used as the pivot elements
 *
 * @param arr   Pointer for the array thats being partitioned
 * @param low   The starting index of the segment that's to be partitioned
 * @param high  The ending index of the pivot after being partitioning
 * @param k     The rank of the desired smallest element
 * @return      The Kth smallest value in arr[low..high]
 *
 * @pre  arr != nullptr, 0 <= low <= high, 1 <= k <=
 * @post The array might be rearranged but the Kth smallest element is only printed
 */

int kSmall(int* arr, int low, int high, int k) {
    int pivotIndex = partition(arr, low, high); // Partitions and then grabs the pivots final value

    int s1Size = pivotIndex - low;              // The current size of S1

    if (k <= s1Size) {                          // Checks if k is in S1
        return kSmall(arr, low, pivotIndex - 1, k);
    } else if (k == s1Size + 1) {               // Checks if k is the pivot point
        return arr[pivotIndex];
    } else {                                    // Otherwise k is in S2
        return kSmall(arr, pivotIndex + 1, high, k - s1Size - 1);
    }
}

/**
 * Prints all the elements of the array
 *
 * @param arr  The pointer for the array
 * @param size Number of elements in the array
 */
void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << " ";
    }
    cout << endl;
}

/**
 *    This tests kSmall for 3 cases 
 *    1 - is k in S1 
 *    2 - is k the pivot 
 *    3 - is k in S2 
 */
int main() {
    cout << "=== kSmall Algorithm ===" << endl << endl;

    //  if k is in the S1 array
    cout << "--- kth smallest is in the S1 array ---" << endl;
    int size1 = 6;
    int* arr1 = new int[size1]{6, 3, 1, 10, 8, 4};
    int k1 = 2;
    cout << "Array: "; printArray(arr1, size1);
    cout << "k = " << k1 << endl;
    int result1 = kSmall(arr1, 0, size1 - 1, k1);
    cout << "The " << k1 << "nd smallest element is: " << result1 << endl;
    cout << "Expected: 3" << endl << endl;
    delete[] arr1;

    //  if k is the pivot
    cout << "--- kth smallest is the pivot point ---" << endl;
    int size2 = 6;
    int* arr2 = new int[size2]{6, 3, 1, 10, 8, 4};
    int k2 = 4;
    cout << "Array: "; printArray(arr2, size2);
    cout << "k = " << k2 << endl;
    int result2 = kSmall(arr2, 0, size2 - 1, k2);
    cout << "The " << k2 << "th smallest element is: " << result2 << endl;
    cout << "Expected: 6" << endl << endl;
    delete[] arr2;

    //  if k is in the S2 array
    cout << "--- kth smallest is in the S2 array ---" << endl;
    int size3 = 6;
    int* arr3 = new int[size3]{6, 3, 1, 10, 8, 4};
    int k3 = 6;
    cout << "Array: "; printArray(arr3, size3);
    cout << "k = " << k3 << endl;
    int result3 = kSmall(arr3, 0, size3 - 1, k3);
    cout << "The " << k3 << "th smallest element is: " << result3 << endl;
    cout << "Expected: 10" << endl << endl;
    delete[] arr3;

    //  if s1 is an empty array 
    cout << "--- S1 is empty ---" << endl;
    int size4 = 7;
    int* arr4 = new int[size4]{1, 3, 5, 2, 19, 3, 4};
    int k4 = 1;
    cout << "Array: "; printArray(arr4, size4);
    cout << "k = " << k4 << endl;
    int result4 = kSmall(arr4, 0, size4 - 1, k4);
    cout << "The " << k4 << "st smallest element is: " << result4 << endl;
    cout << "Expected: 1" << endl << endl;
    delete[] arr4;

    return 0;
}