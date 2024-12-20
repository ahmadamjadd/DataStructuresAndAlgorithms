#include <iostream>
#include <list>
using namespace std;

class HashMapTable {
    int table_size; // Size of the hash table
    list<int>* table; // Pointer to an array containing the keys

public:
    // Constructor
    HashMapTable(int size);

    // Hash function to compute the index using the key
    int hashFunction(int key) {
        return (key % table_size);
    }

    // Insert key into the hash table
    void insertElement(int key);

    // Delete key from the hash table
    void deleteElement(int key);

    // Display the hash table
    void displayHashTable();
};

// Constructor to initialize the hash table
HashMapTable::HashMapTable(int ts) {
    this->table_size = ts;
    table = new list<int>[table_size];
}

// Insert function to add a key to the hash table
void HashMapTable::insertElement(int key) {
    int index = hashFunction(key);
    table[index].push_back(key);
}

// Delete function to remove a key from the hash table
void HashMapTable::deleteElement(int key) {
    int index = hashFunction(key);

    // Find the key in the list at the computed index
    list<int>::iterator it;
    for (it = table[index].begin(); it != table[index].end(); it++) {
        if (*it == key)
            break;
    }

    // Remove the key if found
    if (it != table[index].end())
        table[index].erase(it);
}

// Display function to showcase the hash table
void HashMapTable::displayHashTable() {
    for (int i = 0; i < table_size; i++) {
        cout << i;
        for (auto x : table[i])
            cout << " ==> " << x;
        cout << endl;
    }
}

// Main function
int main() {
    // Array of all the keys to be inserted in the hash table
    int arr[] = {20, 34, 56, 54, 76, 87};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Create a hash table with size 6
    HashMapTable ht(6);

    // Insert keys into the hash table
    for (int i = 0; i < n; i++)
        ht.insertElement(arr[i]);

    // Delete element 34 from the hash table
    ht.deleteElement(34);

    // Display the final data in the hash table
    ht.displayHashTable();

    return 0;
}
