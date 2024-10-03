#include <iostream>
using namespace std;

class Array {
private:
    int fullsize;
    int usedsize;
    int *array;

public:
    Array(int fullsize) {
        this->fullsize = fullsize;
        array = new int[fullsize];
        usedsize = 0;
    }

    ~Array() {
        delete[] array; // Destructor to free allocated memory
    }

    bool isEmpty() {
        return usedsize == 0;
    }

    bool isFull() {
        return usedsize == fullsize;
    }

    bool InsertAtBeg(int val) {
        if (isFull()) {
            cout << "Array is full. Cannot insert at beginning." << endl;
            return false;
        }
        for (int i = usedsize - 1; i >= 0; i--) {
            array[i + 1] = array[i];
        }
        array[0] = val;
        usedsize++; // Increment used size
        return true;
    }

    bool InsertAtEnd(int val) {
        if (isFull()) {
            cout << "Array is full. Cannot insert at end." << endl;
            return false;
        }
        array[usedsize] = val;
        usedsize++; // Increment used size
        return true;
    }

    int find(int element) {
        for (int i = 0; i < usedsize; i++) {
            if (array[i] == element) {
                return i;
            }
        }
        return -1; // Not found
    }

    void showBeg() {
        for (int i = 0; i < usedsize; i++) {
            cout << "Element " << i << ": " << array[i] << endl;
        }
    }

    void showEnd() {
        for (int i = (usedsize - 1); i >= 0; i--) {
            cout << "Element " << i << ": " << array[i] << endl;
        }
    }

    bool del(int element) {
        if (isEmpty()) {
            cout << "Array is empty" << endl;
            return false;
        }
        
        int i;
        for (i = 0; i < usedsize; i++) {
            if (array[i] == element) {
                break; // Found the element to delete
            }
        }

        if (i == usedsize) { // Element not found
            cout << "Element not found" << endl;
            return false;
        }

        for (int j = i; j < usedsize - 1; j++) { // Shift elements left
            array[j] = array[j + 1];
        }
        
        usedsize--; // Decrement used size
        return true; 
    }
};

int main() {
    Array arr(5);
    
    arr.InsertAtEnd(10);
    arr.InsertAtEnd(20);
    arr.InsertAtBeg(5);
    
    cout << "Array contents from beginning:" << endl;
    arr.showBeg();
    
    cout << "Array contents from end:" << endl;
    arr.showEnd();
    
    arr.del(20);
    
    cout << "After deletion:" << endl;
    arr.showBeg();
    
    return 0;
}