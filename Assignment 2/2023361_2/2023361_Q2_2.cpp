#include<iostream>
#include<windows.h>
#include<string>
using namespace std;

class Person {
    string name;
    string address;
    string number;

public:
    Person() {}
    Person(string name, string address, string number) {
        this->name = name;
        this->address = address;
        this->number = number;
    }
    
    void display() {
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Number: " << number << endl;
    }
    
    string getname() {
        return name;
    }
};

struct Node {
    Person P;
    Node *next; // Pointer to the next node
};

class LinkedList {
public:
    Node *head; // Pointer to the start of the list

    LinkedList() {
        head = NULL; // Initialize head
    }

    // Add a person to the list in alphabetical order
    void AddAlphabetically(Person P) {
        Node *newNode = new Node;
        newNode->P = P;
        newNode->next = NULL; // Initialize next to NULL

        // Insert at the head if the list is empty or the new person comes before the head
        if (head == NULL || head->P.getname() >= P.getname()) {
            newNode->next = head;
            head = newNode;
            return;
        }

        // Traverse to find the correct insertion point
        Node *tmp = head;
        Node *prev = NULL;
        while (tmp != NULL && tmp->P.getname() < P.getname()) {
            prev = tmp;
            tmp = tmp->next;
        }

        // Insert the new node in the list
        prev->next = newNode;
        newNode->next = tmp;
    }

    // Display all members in the list
    void display() {
        if (head == NULL) {
            cout << "No persons added yet!" << endl;
            return;
        }
        
        int i = 1;
        Node *tmp = head;
        while (tmp != NULL) {
            cout << i << ": " << endl;
            i++;
            tmp->P.display(); // Display person's details
            tmp = tmp->next;
            cout << endl;
        }
        cout << endl;
    }

    // Find a member by name
    void find(string name) {
        Node *tmp = head;
        while (tmp != NULL && tmp->P.getname() != name) {
            tmp = tmp->next; // Traverse the list
        }
        if (tmp == NULL) {
            cout << "Person Not Found!" << endl;
            return;
        }
        cout << "Person found: " << endl;
        tmp->P.display(); // Display found person's details
    }
};

int main() {
    LinkedList L1;
    int choice;

    do {
        // Menu for user options
        cout << "Choose an option:" << endl;
        cout << "1. Display all members" << endl;
        cout << "2. Add a member" << endl;
        cout << "3. Find a member" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline character left by cin
        system("cls");

        if (choice == 1) {
            // Display all members
            L1.display();
            system("pause");
            system("cls");
        } 
        else if (choice == 2) {
            // Add a member
            string name, address, number;

            cout << "Enter name: ";
            getline(cin, name); // Capture full name

            cout << "Enter address: ";
            getline(cin, address); // Capture full address

            cout << "Enter phone number: ";
            getline(cin, number); // Capture phone number

            Person newPerson(name, address, number);
            L1.AddAlphabetically(newPerson); // Add person to the list
            cout << "Person added successfully!" << endl;
            system("pause");
            system("cls");
        } 
        else if (choice == 3) {
            // Find a member
            string name;
            cout << "Enter the name to find: ";
            getline(cin, name); // Handle names with spaces
            L1.find(name); // Search for the person
            system("pause");
            system("cls");
        } 
        else if (choice == 4) {
            // Exit the program
            system("cls");
            cout << "Exiting program..." << endl;
        } 
        else {
            cout << "Invalid choice! Please choose again." << endl;
            system("pause");
            system("cls");
        }

        cout << endl; // Spacing for readability
    } while (choice != 4);

    return 0;
}


