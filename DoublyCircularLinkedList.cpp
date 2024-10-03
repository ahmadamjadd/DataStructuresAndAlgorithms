#include<iostream>
using namespace std;

class DoublyCircularLinkedList{

    struct Node{
        int data;
        Node* next;
        Node* prev;
    };
    Node *head;

public:
    DoublyCircularLinkedList();
    void AddAtHead(int val);
    void AddAtTail(int val);
    void Delete(int val);
    void Display();
};

int main(){
    DoublyCircularLinkedList list;
    list.AddAtHead(10);
    list.AddAtTail(20);
    list.AddAtTail(30);
    list.Display();
    list.Delete(20);
    list.Display();
    return 0;
}

DoublyCircularLinkedList :: DoublyCircularLinkedList(){
    head = NULL;  // Initialize head as NULL for an empty list
}

void DoublyCircularLinkedList :: AddAtHead(int val){
    Node* newNode = new Node;
    newNode->data = val;
    if (head == NULL) {
        // First node in the circular list
        head = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } else {
        // Adding to the head of a non-empty list
        Node* tail = head->prev;  // Get the tail (last) node
        newNode->next = head;
        newNode->prev = tail;
        head->prev = newNode;
        tail->next = newNode;
        head = newNode;  // Move head to the new node
    }
}

void DoublyCircularLinkedList :: AddAtTail(int val){
    Node* newNode = new Node;
    newNode->data = val;
    if (head == NULL) {
        // Same as AddAtHead if the list is empty
        head = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } else {
        // Adding to the tail of a non-empty list
        Node* tail = head->prev;  // Get the current tail node
        newNode->next = head;
        newNode->prev = tail;
        tail->next = newNode;
        head->prev = newNode;
    }
}

void DoublyCircularLinkedList :: Delete(int val){
    if (head == NULL) {
        cout << "List is empty." << endl;
        return;
    }

    Node* currPtr = head;
    Node* prevPtr = nullptr;
    
    // Search for the node to delete
    do {
        if (currPtr->data == val) {
            // Found the node
            if (currPtr == head && head->next == head) {
                // Single node in the list
                delete head;
                head = NULL;
            } else {
                // More than one node
                Node* nextNode = currPtr->next;
                Node* prevNode = currPtr->prev;
                prevNode->next = nextNode;
                nextNode->prev = prevNode;
                if (currPtr == head) {
                    head = nextNode;  // Update head if needed
                }
                delete currPtr;
            }
            cout << "Element " << val << " deleted." << endl;
            return;
        }
        prevPtr = currPtr;
        currPtr = currPtr->next;
    } while (currPtr != head);

    // Element not found
    cout << "Element not found." << endl;
}

void DoublyCircularLinkedList :: Display(){
    if (head == NULL) {
        cout << "List is empty." << endl;
        return;
    }

    Node* temp = head;
    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);
    cout << endl;
}






/*#include<iostream>
using namespace std;


class DoublyCircularLinkedList{

    struct Node{
        int data;
        Node* next;
        Node* prev;
    };
    Node *head;

    public:
    DoublyCircularLinkedList();
    void AddAtHead(int val);
    void AddAtTail(int val);
    void Delete(int val);
};

int main(){
    return 0;
}

DoublyCircularLinkedList :: DoublyCircularLinkedList(){
    head = NULL;
}

void DoublyCircularLinkedList :: AddAtHead(int val){
    Node * newNode = new Node;
    newNode->data = val;
    if(head!=NULL){
        Node *tempPtr = head->next;
        tempPtr->prev = newNode;
        newNode->next = tempPtr;
        newNode->prev = head;
        head->next = newNode;
    }
    else{
        head->next = newNode;
        newNode->prev = head;
        newNode->next = head;
        head->prev = newNode;
    }
    
}

void DoublyCircularLinkedList :: AddAtTail(int val){
    Node * newNode = new Node;
    newNode->data = val;
    Node * tempPtr = head->next;
    do
    {
        tempPtr = tempPtr->next;
    }while(tempPtr->next != head);
    tempPtr->next = newNode;
    newNode->next = head;
    head->prev = newNode;
    newNode->prev = tempPtr;   
}

void DoublyCircularLinkedList :: Delete(int val){
    Node* currPtr = head;
    Node * prevPtr;
    do{
        prevPtr = currPtr;
        currPtr = currPtr->next;
    }while(currPtr != head && currPtr->data = val);
    if(currPtr == head){
        cout<<"Element not found"<<endl;
    }
    else{
        prevPtr->next = currPtr->next;
        currPtr->next->prev = prevPtr;
        delete currPtr;
    }
}*/
