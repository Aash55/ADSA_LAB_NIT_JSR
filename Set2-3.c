#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1] that are greater than key,
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap the elements
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // Swap the found minimum element with the first element
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}
///
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
// 
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++) L[i] = arr[left + i];
    for (j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    i = 0; j = 0; k = left;
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
    while (i < n1) {
        arr[k] = L[i];
        i++; k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++; k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
//
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}
// 
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void countSort(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0};
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int n) {
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}
//
void countingSort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    int count[max + 1];
    memset(count, 0, sizeof(count));
    int output[n];
    for (int i = 0; i < n; i++)
        count[arr[i]]++;
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}
//
struct Node {
    int data;
    struct Node *next;
};

void insertSorted(struct Node **head, int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    if (*head == NULL || (*head)->data >= newNode->data) {
        newNode->next = *head;
        *head = newNode;
    } else {
        struct Node *current = *head;
        while (current->next != NULL && current->next->data < newNode->data) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

#define MAX_BUCKETS 10

void bucketSort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    struct Node **buckets = (struct Node **)calloc(max + 1, sizeof(struct Node *));
    for (int i = 0; i < n; i++) {
        insertSorted(&buckets[arr[i]], arr[i]);
    }
    int k = 0;
    for (int i = 0; i <= max; i++) {
        struct Node *current = buckets[i];
        while (current != NULL) {
            arr[k++] = current->data;
            current = current->next;
        }
    }
    // Clean up memory
    for (int i = 0; i <= max; i++) {
        struct Node *current = buckets[i];
        while (current != NULL) {
            struct Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(buckets);
}
//

void radixExchangeSort(int arr[], int left, int right, int bit) {
    if (left >= right || bit < 0) return;
    int i = left, j = right;
    while (i <= j) {
        // Check if the bit is set in the number
        while (i <= right && !((arr[i] >> bit) & 1)) {
            i++;
        }
        while (j >= left && ((arr[j] >> bit) & 1)) {
            j--;
        }
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }
    radixExchangeSort(arr, left, i - 1, bit - 1);
    radixExchangeSort(arr, i, right, bit - 1);
}
//
void addressCalculationSort(int arr[], int n) {
    int buckets[MAX_BUCKETS][n];
    int bucket_counts[MAX_BUCKETS];
    memset(bucket_counts, 0, sizeof(bucket_counts));

    int max_val = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    if (max_val == 0) return;

    for (int i = 0; i < n; i++) {
        int bucket_index = (int)((double)arr[i] / max_val * (MAX_BUCKETS - 1));
        buckets[bucket_index][bucket_counts[bucket_index]++] = arr[i];
    }

    int k = 0;
    for (int i = 0; i < MAX_BUCKETS; i++) {
        insertionSort(buckets[i], bucket_counts[i]);
        for (int j = 0; j < bucket_counts[i]; j++) {
            arr[k++] = buckets[i][j];
        }
    }
}

void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Original array: ");
    printArray(arr, n);
    insertionSort(arr, n);
    printf("Inserted Sorted array: ");
    printArray(arr, n);
    printf("\n");

    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("Original array: ");
    printArray(arr1, n1);
    bubbleSort(arr1, n1);
    printf("Bubble Sorted array: ");
    printArray(arr1, n1);
    printf("\n");

    int arr2[] = {64, 25, 12, 22, 11};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("Original array: ");
    printArray(arr2, n2);
    selectionSort(arr2, n2);
    printf("Seletion Sorted array: ");
    printArray(arr2, n2);
    printf("\n");

    int arr3[] = {12, 34, 54, 2, 3};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("Original array: ");
    printArray(arr3, n3);
    shellSort(arr3, n3);
    printf("Shell Sorted array: ");
    printArray(arr3, n3);
    printf("\n");

    int arr4[] = {10, 7, 8, 9, 1, 5};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("Original array: ");
    printArray(arr4, n4);
    quickSort(arr4, 0, n4 - 1);
    printf("Quick Sorted array: ");
    printArray(arr4, n4);
    printf("\n");

    int arr5[] = {12, 11, 13, 5, 6, 7};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    printf("Original array: ");
    printArray(arr5, n5);
    mergeSort(arr5, 0, n5 - 1);
    printf("Merge Sorted array: ");
    printArray(arr5, n5);
    printf("\n");

    int arr6[] = {12, 11, 13, 5, 6, 7};
    int n6 = sizeof(arr6) / sizeof(arr6[0]);
    printf("Original array: ");
    printArray(arr6, n6);
    heapSort(arr6, n6);
    printf("Heap Sorted array: ");
    printArray(arr6, n6);
    printf("\n");

    int arr7[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n7 = sizeof(arr7) / sizeof(arr7[0]);
    printf("Original array: ");
    printArray(arr7, n7);
    radixSort(arr7, n7);
    printf("Radix Sorted array: ");
    printArray(arr7, n7);
    printf("\n");
    
    int arr8[] = {4, 2, 2, 8, 3, 3, 1};
    int n8 = sizeof(arr8) / sizeof(arr8[0]);
    printf("Original array: ");
    printArray(arr8, n8);
    countingSort(arr8, n8);
    printf("Counting Sorted array: ");
    printArray(arr8, n8);
    printf("\n");

    int arr9[] = {29, 25, 3, 49, 9, 37, 21, 43};
    int n9 = sizeof(arr9) / sizeof(arr9[0]);
    printf("Original array: ");
    printArray(arr9, n9);
    bucketSort(arr9, n9);
    printf("Bucket Sorted array: ");
    printArray(arr9, n9);
    printf("\n");
    
    int arr10[] = {12, 11, 13, 5, 6};
    int n10 = sizeof(arr10) / sizeof(arr10[0]);
    // Assuming max number of bits is around 31 for 32-bit integers
    int max_bits = 31;
    printf("Original array: ");
    printArray(arr10, n10);
    radixExchangeSort(arr10, 0, n10 - 1, max_bits);
    printf("Radix Exchange Sorted array: ");
    printArray(arr10, n10);
    printf("\n");

    int arr11[] = {45, 29, 3, 19, 92, 11, 80};
    int n11 = sizeof(arr11) / sizeof(arr11[0]);
    printf("Original array: ");
    printArray(arr11, n11);
    addressCalculationSort(arr11, n11);
    printf("Address Calculation Sorted array: ");
    printArray(arr11, n11);


    return 0;
}