#include <iostream>
using namespace std;

const int TABLE_SIZE = 10; // Size of the hash table

struct HashNode {
    int key;
    int value;
    bool isDeleted;

    HashNode() : key(-1), value(-1), isDeleted(false) {}
};

class HashTable {
    HashNode table[TABLE_SIZE];
    int c1 = 1, c2 = 3; // Constants for quadratic probing

    int hashFunc(int key) {
        return key % TABLE_SIZE;
    }

public:
    void insert(int key, int value) {
        int hash_val = hashFunc(key);
        int i = 0;

        while (table[hash_val].key != -1 && !table[hash_val].isDeleted && table[hash_val].key != key) {
            i++;
            hash_val = (hashFunc(key) + c1 * i + c2 * i * i) % TABLE_SIZE; // Quadratic probing
            if (i > TABLE_SIZE) { // Stop after TABLE_SIZE attempts
                cout << "Hash Table is full. Cannot insert key " << key << endl;
                return;
            }
        }

        table[hash_val].key = key;
        table[hash_val].value = value;
        table[hash_val].isDeleted = false;
    }

    void remove(int key) {
        int hash_val = hashFunc(key);
        int i = 0;

        while (table[hash_val].key != -1) {
            if (table[hash_val].key == key && !table[hash_val].isDeleted) {
                table[hash_val].isDeleted = true;
                cout << "Key " << key << " removed from the hash table." << endl;
                return;
            }
            i++;
            hash_val = (hashFunc(key) + c1 * i + c2 * i * i) % TABLE_SIZE;
            if (i > TABLE_SIZE) break;
        }
        cout << "Key " << key << " not found in the hash table." << endl;
    }

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

    ht.insert(10, 100);
    ht.insert(20, 200);
    ht.insert(30, 300);
    ht.insert(40, 400);
    ht.insert(25, 250);

    cout << "Hash Table after insertion:" << endl;
    ht.display();

    ht.remove(20);
    cout << "Hash Table after deletion:" << endl;
    ht.display();

    return 0;
}
