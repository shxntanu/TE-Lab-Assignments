#include <iostream>
using namespace std;

void selectionSort(int arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    // Find the index of the minimum element in the unsorted part
    int min_idx = i;
    for (int j = i + 1; j < n; j++) {
      if (arr[j] < arr[min_idx]) {
        min_idx = j;
      }
    }
    // Swap the minimum element with the first element of the unsorted part
    if (min_idx != i) {
      swap(arr[i], arr[min_idx]);
    }
  }
}

int main() {
  int arr[] = {64, 25, 12, 22, 11};
  int n = sizeof(arr) / sizeof(arr[0]);

  selectionSort(arr, n);

  cout << "Sorted array: ";
  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;

  return 0;
}
