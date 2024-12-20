/*
Explanation:
1. Count Sort: This sorts the array when the range of numbers is small. It uses a `count` array to record the frequency of each number, then rewrites the input array in sorted order by counting down from the frequencies.
2. Radix Sort: This handles larger numbers by sorting the array digit by digit, starting from the least significant digit (1's place) to the most significant digit (10's, 100's, etc.).
3. CountSortForRadix: Used within Radix Sort, it sorts the array based on the current digit (at position `exp`). It calculates positions using the count array, ensuring stability (maintains relative order of equal elements).
4. Radix Sort repeatedly applies `CountSortForRadix` for each digit until all are processed. This makes it efficient for numbers with small digit ranges and guarantees a stable sort.
*/




#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

//maximum value in array
void findMax(int* arr, int size, int &maxVal) {
    maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
}

//count sort
void countSort(int* arr, int size) {
    int maxVal;
    findMax(arr, size, maxVal);
    int* count = new int[maxVal + 1]();

    for (int i = 0; i < size; i++) {
        count[arr[i]]++;
    }

    int index = 0;
    for (int i = 0; i <= maxVal; i++) {
        while (count[i] > 0) {
            arr[index] = i;
            index++;
            count[i]--;
        }
    }

    delete[] count;
}

//helper count sort for radix
void countSortForRadix(int* arr, int size, int exp) {
    int* output = new int[size];
    int count[10] = {0};

    for (int i = 0; i < size; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }

    delete[] output;
}

//radix sort, sorting at each nth place
void radixSort(int* arr, int size) {
    int maxVal;
    findMax(arr, size, maxVal);

    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countSortForRadix(arr, size, exp);
    }
}

int main() {
    int arr[7] = {4, 2, 2, 8, 3, 3, 1};

    cout << "Before Count Sort: ";
    for (int i = 0; i < 7; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    countSort(arr, 7);

    cout << "After Count Sort: ";
    for (int i = 0; i < 7; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    int arr2[] = {4,2,2,6,3,3,1};

    cout << "Before Radix Sort: ";
    for (int i = 0; i < 7; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;

    radixSort(arr2, 7);

    cout << "After Radix Sort: ";
    for (int i = 0; i < 7; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;

    return 0;
}
