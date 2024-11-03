#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
    Node *prev;
};

class DoublyLinkedList
{
    Node *head;
    Node *tail;

public:
    DoublyLinkedList()
    {
        head = NULL;
        tail = NULL;
    }

    void AddAtFront(int val)
    {
        Node *newNode = new Node;
        newNode->data = val;
        newNode->next = head;
        newNode->prev = NULL;

        if (head != NULL)
        {
            head->prev = newNode;
        }
        else
        {
            tail = newNode;
        }
        head = newNode;
    }

    void display()
    {
        Node *tmp = head;
        while (tmp != NULL)
        {
            cout << tmp->data << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }

    void swapNodes(int a, int b)
    {
        if (a == b)
            return; // No need to swap same values

        Node *nodeA = head;
        Node *nodeB = head;

        // Locate nodes to swap
        while (nodeA != NULL && nodeA->data != a)
            nodeA = nodeA->next;
        while (nodeB != NULL && nodeB->data != b)
            nodeB = nodeB->next;

        // Check if both nodes exist
        if (nodeA == NULL || nodeB == NULL)
        {
            cout << "Cannot swap as one or both of Nodes do not exist!" << endl;
            return;
        }

        // If nodes are adjacent
        if (nodeA->next == nodeB || nodeB->next == nodeA)
        {
            Node *firstNode;
            Node *secondNode;

            if (nodeA->next == nodeB)
            { // A is before B
                firstNode = nodeA;
                secondNode = nodeB;
            }
            else
            { // B is before A
                firstNode = nodeB;
                secondNode = nodeA;
            }

            // Adjust links for adjacent nodes
            if (firstNode->prev)
            {
                firstNode->prev->next = secondNode;
            }
            else
            {
                head = secondNode; // Update head if firstNode was head
            }

            if (secondNode->next)
            {
                secondNode->next->prev = firstNode;
            }
            else
            {
                tail = firstNode; // Update tail if secondNode was tail
            }

            // Swap pointers
            firstNode->next = secondNode->next;
            secondNode->next = firstNode;

            // Update previous pointers
            secondNode->prev = firstNode->prev;
            firstNode->prev = secondNode;

            // Ensure previous links are correct
            if (firstNode->next)
            {
                firstNode->next->prev = firstNode;
            }
            if (secondNode->prev)
            {
                secondNode->prev->next = secondNode;
            }
        }
        else
        { // Handle non-adjacent nodes
            Node *temp1Prev = nodeA->prev;
            Node *temp1Next = nodeA->next;
            Node *temp2Prev = nodeB->prev;
            Node *temp2Next = nodeB->next;

            if (temp1Prev)
            {
                temp1Prev->next = nodeB; // Link A's previous to B
            }
            else
            {
                head = nodeB; // Update head if A was head
            }

            if (temp2Prev)
            {
                temp2Prev->next = nodeA; // Link B's previous to A
            }
            else
            {
                head = nodeA; // Update head if B was head
            }
            if (temp1Next)
            {
                temp1Next->prev = nodeB; // Link A's next to B
            }
            else
            {
                tail = nodeB; // Update tail if A was tail
            }

            if (temp2Next)
            {
                temp2Next->prev = nodeA; // Link B's next to A
            }
            else
            {
                tail = nodeA; // Update tail if B was tail
            }

            // Finalize the swap for non-adjacent nodes
            nodeB->prev = temp1Prev;
            nodeB->next = temp1Next;

            nodeA->prev = temp2Prev;
            nodeA->next = temp2Next;
        }
    }
};

int main()
{
    DoublyLinkedList L1;
    L1.AddAtFront(0);
    L1.AddAtFront(7);
    L1.AddAtFront(6);
    L1.AddAtFront(9);
    L1.AddAtFront(2);
    L1.AddAtFront(4);
    L1.AddAtFront(5);
    L1.AddAtFront(8);
    L1.AddAtFront(1);
    L1.AddAtFront(3);

    cout << "Original List: ";
    L1.display();

    L1.swapNodes(3, 0); // Example swap
    cout << "After swapping: ";
    L1.display();

    return 0;
}
