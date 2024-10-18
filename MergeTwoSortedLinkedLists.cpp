#include <iostream>

struct Node {
    int data;
    Node* next;
};

class LinkedList {
public:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void append(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void display() const {
        Node* temp = head;
        while (temp) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

LinkedList* MergeSortedLists(LinkedList* list1, LinkedList* list2) {
    LinkedList* mergedList = new LinkedList();
    Node* tmp1 = list1->head;
    Node* tmp2 = list2->head;

    while (tmp1 != nullptr && tmp2 != nullptr) {
        if (tmp1->data <= tmp2->data) {
            mergedList->append(tmp1->data);
            tmp1 = tmp1->next;
        } else {
            mergedList->append(tmp2->data);
            tmp2 = tmp2->next;
        }
    }

    while (tmp1 != nullptr) {
        mergedList->append(tmp1->data);
        tmp1 = tmp1->next;
    }

    while (tmp2 != nullptr) {
        mergedList->append(tmp2->data);
        tmp2 = tmp2->next;
    }

    return mergedList;
}

int main() {
    LinkedList* L1 = new LinkedList();
    LinkedList* L2 = new LinkedList();
    L1->append(1);
    L1->append(2);
    L1->append(3);
    L2->append(2);
    L2->append(4);
    L2->append(7);

    LinkedList* L3 = MergeSortedLists(L1, L2);
    L3->display();

    delete L1; // Cleanup
    delete L2; // Cleanup
    delete L3; // Cleanup
    return 0;
}
