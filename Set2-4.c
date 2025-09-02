#include <stdio.h>
#include <stdlib.h>

// Merges two sub-arrays of arr[]
// First sub-array is arr[left..mid]
// Second sub-array is arr[mid+1..right]
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr[left..right]
    i = 0; // Initial index of first sub-array
    j = 0; // Initial index of second sub-array
    k = left; // Initial index of merged sub-array

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

// Iterative merge sort function
void iterativeMergeSort(int arr[], int n) {
    int current_size; // For current sub-array size
    int left_start;   // For starting index of left sub-array

    // Start with sub-array size 1. Then 2, 4, 8, ...
    for (current_size = 1; current_size <= n - 1; current_size = 2 * current_size) {
        // Pick starting point of different sub-arrays of current_size
        for (left_start = 0; left_start < n - 1; left_start += 2 * current_size) {
            // Find ending point of left sub-array. mid is (left_start + current_size - 1)
            int mid = left_start + current_size - 1;
            int right_end = (left_start + 2 * current_size - 1 < n - 1) ?
                            (left_start + 2 * current_size - 1) : (n - 1);

            if (mid < n) {
                merge(arr, left_start, mid, right_end);
            }
        }
    }
}

// Function to print the array
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    iterativeMergeSort(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}