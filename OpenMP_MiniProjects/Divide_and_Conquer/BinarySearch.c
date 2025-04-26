#include <stdio.h>

int binary_search(int arr[], int start, int end, int target) {
    if (start > end) return -1;

    int mid = (start + end) / 2;
    if (arr[mid] == target) return mid;
    else if (arr[mid] > target) return binary_search(arr, start, mid - 1, target);
    else return binary_search(arr, mid + 1, end, target);
}

int main() {
    int arr[] = {2, 4, 6, 8, 10, 12, 14};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 10;
    int result = binary_search(arr, 0, n - 1, target);


    if (result != -1)
        printf("Element found at index %d\n", result);
    else
        printf("Element not found\n");

    return 0;
}
