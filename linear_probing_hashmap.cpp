#include <iostream>
using namespace std;

const int TABLE_SIZE = 10; // Size of the hash table

struct HashNode {
    int key;
    int value;
    bool isDeleted; // To handle deletion

    HashNode() : key(-1), value(-1), isDeleted(false) {} // Default constructor
};

class HashTable {
    HashNode table[TABLE_SIZE];

    // Hash function
    int hashFunc(int key) {
        return key % TABLE_SIZE;
    }

public:
    // Insert function
    void insert(int key, int value) {
        int hash_val = hashFunc(key);
        int originalHash = hash_val;

        while (table[hash_val].key != -1 && !table[hash_val].isDeleted && table[hash_val].key != key) {
            hash_val = (hash_val + 1) % TABLE_SIZE; // Linear probing
            if (hash_val == originalHash) {
                cout << "Hash Table is full. Cannot insert key " << key << endl;
                return;
            }
        }

        table[hash_val].key = key;
        table[hash_val].value = value;
        table[hash_val].isDeleted = false;
    }

    // Remove function
    void remove(int key) {
        int hash_val = hashFunc(key);
        int originalHash = hash_val;

        while (table[hash_val].key != -1) {
            if (table[hash_val].key == key && !table[hash_val].isDeleted) {
                table[hash_val].isDeleted = true;
                cout << "Key " << key << " removed from the hash table." << endl;
                return;
            }

            hash_val = (hash_val + 1) % TABLE_SIZE; // Linear probing
            if (hash_val == originalHash) break; // Prevent infinite loop
        }
        cout << "Key " << key << " not found in the hash table." << endl;
    }

    // Display function
    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i].key != -1 && !table[i].isDeleted) {
                cout << i << ": [" << table[i].key << ", " << table[i].value << "]" << endl;
            } else if (table[i].isDeleted) {
                cout << i << ": Deleted" << endl;
            } else {
                cout << i << ": Empty" << endl;
            }
        }
    }
};

int main() {
    HashTable ht;

    // Insert key-value pairs
    ht.insert(10, 100);
    ht.insert(20, 200);
    ht.insert(30, 300);
    ht.insert(40, 400);
    ht.insert(25, 250);

    // Display the hash table
    cout << "Hash Table after insertion:" << endl;
    ht.display();

    // Remove a key
    ht.remove(20);

    // Display the hash table after deletion
    cout << "Hash Table after deletion:" << endl;
    ht.display();

    // Attempt to remove a non-existing key
    ht.remove(50);

    return 0;
}
