#include<iostream>
using namespace std;

struct Node {
    int data;
    Node *prev;
    Node *next;
};

class DoubleCircularLinkedList {
public:
    Node *head;
    Node *tail;

public:
    DoubleCircularLinkedList() {
        head = NULL;
        tail = NULL;
    }

    void insertAtend(int val) {
        Node *newNode = new Node;
        newNode->data = val;
        if (head == NULL) {
            head = newNode;
            tail = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        } else {
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
            tail = newNode;
        }
    }

    void Display() {
        if (head == NULL) return; // Handle empty list case
        Node *tmp = head;
        do {
            cout << tmp->data << " ";
            tmp = tmp->next;
        } while (tmp != head);
        cout << endl;
    }
};

bool CheckPalindrome(Node *head, Node *tail) {
    // Base case 1: List is empty
    if (head == NULL || tail == NULL) {
        cout << "It is a palindrome!" << endl;
        return true;
    }
    
    // Base case 2: If both pointers meet or cross (odd or even length cases)
    if (head == tail || head->prev == tail) {
        cout << "It is a palindrome!" << endl;
        return true;
    }

    // Recursive case: Check if data matches and move pointers inward
    if (head->data == tail->data) {
        return CheckPalindrome(head->next, tail->prev);
    } else {
        cout << "It is not a palindrome!" << endl;
        return false;
    }
}

int main() {
    DoubleCircularLinkedList List;
    List.insertAtend(4);
    List.insertAtend(8);
    List.insertAtend(8);
    List.insertAtend(8);
    List.insertAtend(4);
    
    if (CheckPalindrome(List.head, List.tail)) {
        cout << "The list is a palindrome." << endl;
    } else {
        cout << "The list is not a palindrome." << endl;
    }
    
    List.Display();
    return 0;
}

