#include <iostream>
using namespace std;

const int TABLE_SIZE = 10; // Size of the hash table
const int PRIME = 7;       // A prime number smaller than TABLE_SIZE

struct HashNode {
    int key;
    int value;
    bool isDeleted;

    HashNode() : key(-1), value(-1), isDeleted(false) {}
};

class HashTable {
    HashNode table[TABLE_SIZE];

    int hashFunc(int key) {
        return key % TABLE_SIZE;
    }

    int hashFunc2(int key) {
        return PRIME - (key % PRIME); // Second hash function
    }

public:
    void insert(int key, int value) {
        int hash_val = hashFunc(key);
        int step = hashFunc2(key);
        int i = 0;

        while (table[hash_val].key != -1 && !table[hash_val].isDeleted && table[hash_val].key != key) {
            i++;
            hash_val = (hashFunc(key) + i * step) % TABLE_SIZE; // Double hashing
            if (i > TABLE_SIZE) {
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
        int step = hashFunc2(key);
        int i = 0;

        while (table[hash_val].key != -1) {
            if (table[hash_val].key == key && !table[hash_val].isDeleted) {
                table[hash_val].isDeleted = true;
                cout << "Key " << key << " removed from the hash table." << endl;
                return;
            }
            i++;
            hash_val = (hashFunc(key) + i * step) % TABLE_SIZE;
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
