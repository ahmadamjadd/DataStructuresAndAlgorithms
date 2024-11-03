#include <iostream>
using namespace std;

// Node structure for the linked list
struct Node {
    int data;      
    Node *next;     
};

class LinkedList {
public:
    Node *head;     

    LinkedList() {
        head = NULL; 
    }

    // Add a node at the head of the list
    void AddAtHead(int val) {
        Node *newNode = new Node;
        newNode->data = val;
        newNode->next = head; 
        head = newNode; 
    }

    // Display all node values in the list
    void display() {
        Node *tmp = head;
        while (tmp != NULL) {
            cout << tmp->data << " ";
            tmp = tmp->next; 
        }
        cout << endl;
    }

    // Create a loop in the list
    void AddLoop(int st, int en) {
        Node *start = head;
        Node *end = head;

        for (int i = 0; i < st - 1; i++) {
            start = start->next;
        }
        for (int i = 0; i < en - 1; i++) {
            end = end->next;
        }
        end->next = start; // Create loop
    }
};

// Detect if a loop exists and return the starting node's data
int DetectLoop(LinkedList &L1) {
    Node *slow = L1.head;
    Node *fast = L1.head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next; // Move slow by one
        fast = fast->next->next; // Move fast by two

        if (slow == fast) { // Loop detected
            cout << "Cycle detected!" << endl;
            Node *start = L1.head;
            int position = 1;

            while (start != slow) { // Find start of the cycle
                start = start->next;
                slow = slow->next;
                position++;
            }
            cout << "Cycle starts at position " << position << "!" << endl;
            int tmp = slow->data;

            // Break the loop
            int j = 0;
            while (slow->next != start) {
                slow = slow->next;
                j++;
            }
            slow->next = NULL; // Remove loop
            cout << "Loop removed from Node " << position + j << " to Node " << position << endl;

            return tmp; // Return the data at the start of the cycle
        }
    }

    cout << "No cycle detected!" << endl;
    return -1; // No cycle
}

int main() {
    LinkedList L1;
    L1.AddAtHead(1);
    L1.AddAtHead(2);
    L1.AddAtHead(8);
    L1.AddAtHead(3);
    L1.AddAtHead(11);
    L1.display();
    L1.AddLoop(5, 5); // Create loop
    int ans = DetectLoop(L1); // Detect loop
    L1.display();
    cout << "Value returned: " << ans << endl;
    return 0;
}


