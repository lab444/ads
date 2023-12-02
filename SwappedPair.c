#include <stdio.h>

void findSwappedPair(int arr[], int n) {
    int first = -1, second = -1;

    // Traverse the array to find the swapped pair
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            if (first == -1) {
                first = i;
            } else {
                second = i + 1;
                break; // Found the second element, break the loop
            }
        }
    }

    // Swap the elements to restore the sorted order temporarily
    int temp = arr[first];
    arr[first] = arr[second];
    arr[second] = temp;

    // Check if the array is sorted after swapping
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            printf("Swapped elements: (%d, %d)\n", arr[first], arr[second]);
            printf("Positions: %d and %d\n", first + 1, second + 1);
            return;
        }
    }

    printf("No swapped pair found.\n");
}

int main() {
    int n;

    // Input: Number of elements in the array
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];

    // Input: Elements of the array
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Call the function to find the swapped pair
    findSwappedPair(arr, n);

    return 0;
}