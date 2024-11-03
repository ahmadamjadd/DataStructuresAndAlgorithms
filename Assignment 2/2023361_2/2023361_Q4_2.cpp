#include <iostream>
using namespace std;

// Node structure for the doubly linked list
struct Node {
    int data;
    Node* next;
    Node* prev;
};

class DoublyLinkedList {
    Node* head; 
    Node* tail; 

public:
    DoublyLinkedList() {
        head = NULL; 
        tail = NULL; 
    }

    // Add a new node at the front
    void AddAtFront(int val) {
        Node* newNode = new Node; 
        newNode->data = val;
        newNode->next = head;

        if (head != NULL) {
            head->prev = newNode; // Link the old head back
        } else {
            tail = newNode; // New node is also the tail
        }
        head = newNode; // Set the new node as head
    }

    // Display the list contents
    void display() {
        Node* tmp = head;
        while (tmp != NULL) {
            cout << tmp->data << " "; 
            tmp = tmp->next;
        }
        cout << endl;
    }

    // Change the head to the specified position
    void ChangeHead(int position) {
        for(int i = 0; i < position; i++) {
            Node* tmp = head;
            head = head->next; // Move head forward
            head->prev = NULL; // Clear previous link for new head
            tail->next = tmp; // Append old head to end
            tmp->prev = tail; // Link back to tail
            tmp->next = NULL; // Clear next link for old head
            tail = tail->next; // Update tail
        }
    }
};

int main() {
    DoublyLinkedList L1;
    L1.AddAtFront(1);
    L1.AddAtFront(2);
    L1.AddAtFront(8);
    L1.AddAtFront(3);
    L1.AddAtFront(11);
    L1.display(); // Display before changing head
    L1.ChangeHead(2); // Change head position
    L1.display(); // Display after changing head
    return 0;
}
