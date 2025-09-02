#include <stdio.h>

// Merges two sub-arrays
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temp arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr
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
}

// Iterative merge sort
void mergeSort(int arr[], int n) {
    int current_size; // For current sub-array size
    int left_start;   // For starting index of left sub-array

    // Outer loop: Iterate through different sub-array sizes
    for (current_size = 1; current_size <= n - 1; current_size = 2 * current_size) {
        // Inner loop: Pick starting points of sub-arrays to be merged
        for (left_start = 0; left_start < n - 1; left_start += 2 * current_size) {
            int mid = left_start + current_size - 1;
            int right_end = (left_start + 2 * current_size - 1 < n - 1) ?
                            (left_start + 2 * current_size - 1) : (n - 1);
            
            // Only merge if mid is a valid index within the array
            if (mid < n -1) {
                merge(arr, left_start, mid, right_end);
            }
        }
    }
}

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 15, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    mergeSort(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}