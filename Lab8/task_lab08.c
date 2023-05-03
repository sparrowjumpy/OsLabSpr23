#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 100000

int arr[MAX_SIZE]; // the array to be sorted
int temp[MAX_SIZE]; // temporary array to store sorted elements during merge step

// Struct to hold start and end indices for merge sort
typedef struct {
    int start_index;
    int end_index;
} MergeSortArgs;

// Merge two sorted arrays into one
void merge(int start, int mid, int end) {
    int i = start, j = mid+1, k = start;

    // Compare elements from both arrays and add them to the temporary array in order
    while(i <= mid && j <= end) {
        if(arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // Add any remaining elements from the left array to the temporary array
    while(i <= mid) {
        temp[k++] = arr[i++];
    }

    // Add any remaining elements from the right array to the temporary array
    while(j <= end) {
        temp[k++] = arr[j++];
    }

    // Copy the sorted elements back to the original array
    for(int x=start; x<=end; x++) {
        arr[x] = temp[x];
    }
}

// Merge sort function
void* merge_sort(void* arg) {
    MergeSortArgs* args = (MergeSortArgs*) arg;

    // If there is only one element or less, the array is already sorted
    if(args->start_index >= args->end_index) {
        return NULL;
    }

    int mid = (args->start_index + args->end_index) / 2;

    // Sort the left and right halves of the array in separate threads
    pthread_t left_thread, right_thread;
    MergeSortArgs left_args = {args->start_index, mid};
    MergeSortArgs right_args = {mid+1, args->end_index};
    pthread_create(&left_thread, NULL, merge_sort, &left_args);
    pthread_create(&right_thread, NULL, merge_sort, &right_args);

    // Wait for the left and right halves to be sorted before merging them
    pthread_join(left_thread, NULL);
    pthread_join(right_thread, NULL);

    merge(args->start_index, mid, args->end_index);

    return NULL;
}

int main() {
    int n;

    // Read in the size of the array and the array elements from the user
    printf("Enter array size (up to %d): ", MAX_SIZE);
    scanf("%d", &n);
    printf("Enter array elements: ");
    for(int i=0; i<n; i++) {
        scanf("%d", &arr[i]);
    }

    MergeSortArgs args = {0, n-1}; // create arguments for the initial merge sort call

    pthread_t merge_sort_thread;
    pthread_create(&merge_sort_thread, NULL, merge_sort, &args); // sort the array in a separate thread
    pthread_join(merge_sort_thread, NULL); // wait for the sorting to finish
    printf("Sorted array: ");
    for(int i=0; i<n; i++) {
        printf("%d ", arr[i]); // print out the sorted array
    }
    printf("\n");

    return 0;
}
