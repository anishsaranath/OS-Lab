#include <stdio.h>
int main() {
    int arr[100], n, i;
    int smallest, second_smallest;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    printf("Enter %d elements: ", n);
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    if(arr[0] < arr[1]) {
        smallest = arr[0];
        second_smallest = arr[1];
    } else {
        smallest = arr[1];
        second_smallest = arr[0];
    }
    for(i = 2; i < n; i++) {
        if(arr[i] < smallest) {
            second_smallest = smallest;
            smallest = arr[i];
        } else if(arr[i] < second_smallest && arr[i] != smallest) {
            second_smallest = arr[i];
        }
    }
    printf("Second smallest element: %d\n", second_smallest);
    return 0;
}
