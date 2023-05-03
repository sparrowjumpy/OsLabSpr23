#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 100000

int arr[MAX_SIZE];
int temp[MAX_SIZE];

typedef struct {
    int start_index;
    int end_index;
} MergeSortArgs;

void merge(int start, int mid, int end) {
    int i = start, j = mid+1, k = start;

    while(i <= mid && j <= end) {
        if(arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while(i <= mid) {
        temp[k++] = arr[i++];
    }

    while(j <= end) {
        temp[k++] = arr[j++];
    }

    for(int x=start; x<=end; x++) {
        arr[x] = temp[x];
    }
}

void* merge_sort(void* arg) {
    MergeSortArgs* args = (MergeSortArgs*) arg;

    if(args->start_index >= args->end_index) {
        return NULL;
    }

    int mid = (args->start_index + args->end_index) / 2;

    pthread_t left_thread, right_thread;
    MergeSortArgs left_args = {args->start_index, mid};
    MergeSortArgs right_args = {mid+1, args->end_index};
    pthread_create(&left_thread, NULL, merge_sort, &left_args);
    pthread_create(&right_thread, NULL, merge_sort, &right_args);

    pthread_join(left_thread, NULL);
    pthread_join(right_thread, NULL);

    merge(args->start_index, mid, args->end_index);

    return NULL;
}

int main() {
    int n;

    printf("Enter array size (up to %d): ", MAX_SIZE);
    scanf("%d", &n);
    printf("Enter array elements: ");
    for(int i=0; i<n; i++) {
        scanf("%d", &arr[i]);
    }

    MergeSortArgs args = {0, n-1};

    pthread_t merge_sort_thread;
    pthread_create(&merge_sort_thread, NULL, merge_sort, &args);
    pthread_join(merge_sort_thread, NULL);
    printf("Sorted array: ");
    for(int i=0; i<n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
