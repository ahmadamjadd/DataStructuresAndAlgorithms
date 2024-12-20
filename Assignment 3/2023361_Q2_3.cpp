#include<iostream>
#include<string>
#include<algorithm>
#include<windows.h>

using namespace std;

//structure of Node for LinkedList
struct Node_Linked {
public:
    string dataString;//will contain incidents
    int dataInt;//will contain id of incidents
    Node_Linked *next;

    Node_Linked(string s, int i) {
        dataString = s;
        dataInt = i;
        next = nullptr;
    }
};

//LinkedList Implementation
class LinkedList {
public:
    Node_Linked *head;

    LinkedList() {
        head = nullptr;
    }

    //copy contructor so that when im assigning Linked List object with its own object in Location Class, it does not cause issue and copies successfully
    LinkedList(const LinkedList &other) {
        if (other.head == nullptr) {
            head = nullptr;
        } else {
            head = new Node_Linked(other.head->dataString, other.head->dataInt);
            Node_Linked *currentOther = other.head->next;
            Node_Linked *currentNew = head;

            while (currentOther != nullptr) {
                currentNew->next = new Node_Linked(currentOther->dataString, currentOther->dataInt);
                currentNew = currentNew->next;
                currentOther = currentOther->next;
            }
        }
    }

    void insert(string s, int i) {
        Node_Linked *newNode = new Node_Linked(s, i);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node_Linked *temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void display() const {
        Node_Linked *temp = head;
        while (temp != nullptr) {
            cout << "Id: " << temp->dataInt << endl;
            cout << "Description: " << temp->dataString << endl;
            temp = temp->next;
        }
    }

    //deleting a specific node
    void deleteById(int id) {
        if (head == nullptr) return;

        if (head->dataInt == id) {
            Node_Linked* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node_Linked* current = head;
        while (current->next != nullptr && current->next->dataInt != id) {
            current = current->next;
        }

        if (current->next != nullptr) {
            Node_Linked* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }


    //del function so when i will be deleting whole tree node, i will call it as well so linkedlist gets deleted from memory as well
    void del_whole_LinkedList() {
        Node_Linked *temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

//location class
class Location {
private:
    int loc_id;
    string area;
    string city;
public:
    LinkedList incident;

    Location() {
        loc_id = 0;
        area = "";
        city = "";
    }

    Location(int loc_id, string area, string city, const LinkedList L) {
        this->loc_id = loc_id;
        this->area = area;
        this->city = city;
        this->incident = L;//using copy constructor here
    }

    int get_loc_id() const {
        return loc_id;
    }

    void print_details() const {
        cout << "LocationID: " << loc_id << endl;
        cout << "Area: " << area << endl;
        cout << "City: " << city << endl;
        incident.display();
    }
};

//strcuture of Node for tree
struct Node_tree {
    Location L;//will contain locations as nodes
    Node_tree *left;
    Node_tree *right;
    int height;

    Node_tree(Location location) {
        L = location;
        left = nullptr;
        right = nullptr;
        height = 0;
    }
};

//AVL Tree Implementation
class AVL {
private:
    Node_tree *root;

    int getHeight(Node_tree *node) {
        if (node == nullptr) {
            return 0;
        } else {
            return node->height;
        }
    }

    int getBalanceFactor(Node_tree *node) {
        if (node == nullptr) {
            return 0;
        } else {
            return getHeight(node->left) - getHeight(node->right);
        }
    }

    Node_tree *rightRotate(Node_tree *y) {
        Node_tree *x = y->left;
        Node_tree *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    Node_tree *leftRotate(Node_tree *x) {
        Node_tree *y = x->right;
        Node_tree *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    //adding nodes on the basis of location ID
    Node_tree* add(Node_tree* node, Location val) {
        if (node == nullptr) {
            return new Node_tree(val);
        }

        if (val.get_loc_id() < node->L.get_loc_id()) {
            node->left = add(node->left, val);
        } else if (val.get_loc_id() > node->L.get_loc_id()) {
            node->right = add(node->right, val);
        } else {
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalanceFactor(node);
        //applying conditions
        if (balance > 1 && val.get_loc_id() < node->left->L.get_loc_id()) {
            return rightRotate(node);
        }

        if (balance < -1 && val.get_loc_id() > node->right->L.get_loc_id()) {
            return leftRotate(node);
        }

        if (balance > 1 && val.get_loc_id() > node->left->L.get_loc_id()) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && val.get_loc_id() < node->right->L.get_loc_id()) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    //inorder Traversel
    void inOrder(Node_tree *node) const {
        if (node == nullptr) {
            return;
        }

        inOrder(node->left);
        node->L.print_details();
        cout << "Height=" << node->height << endl << endl;
        inOrder(node->right);
    }

    Node_tree* inOrderPredecessor(Node_tree* node) {
        node = node->left;
        while (node != nullptr && node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    //deleting Nodes on the basis of location ID
    Node_tree* deleteNode(Node_tree* node, Location val) {
        if (node == nullptr) {
            return node;
        }

        if (val.get_loc_id() < node->L.get_loc_id()) {
            node->left = deleteNode(node->left, val);
        } else if (val.get_loc_id() > node->L.get_loc_id()) {
            node->right = deleteNode(node->right, val);
        } else {
            if (node->left == nullptr || node->right == nullptr) {
                Node_tree* temp = nullptr;
                if (node->left != nullptr) {
                    temp = node->left;
                } else {
                    temp = node->right;
                }

                node->L.incident.del_whole_LinkedList();//deleting whole linked list associated with node so it does not remain in memory
                delete node;
                return temp;
            }

            Node_tree* temp = inOrderPredecessor(node);
            node->L = temp->L;
            node->left = deleteNode(node->left, temp->L);
        }

        if (node != nullptr) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));

            int balance = getBalanceFactor(node);

            //applying conditions
            if (balance > 1 && getBalanceFactor(node->left) >= 0) {
                return rightRotate(node);
            }

            if (balance > 1 && getBalanceFactor(node->left) < 0) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }

            if (balance < -1 && getBalanceFactor(node->right) <= 0) {
                return leftRotate(node);
            }

            if (balance < -1 && getBalanceFactor(node->right) > 0) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }

        return node;
    }

    //finding node based on ID
    Node_tree* helpsearch(Node_tree* node, int value) {
        if (node == nullptr) {
            return NULL;
        }
        if (node->L.get_loc_id() == value) {
            return node;
        } else if (value < node->L.get_loc_id()) {
            return helpsearch(node->left, value);
        } else {
            return helpsearch(node->right, value);
        }
    }

public:
    AVL() {
        root = nullptr;
    }

    void insert(Location val) {
        root = add(root, val);
    }

    void traverseTree() const {
        inOrder(root);
    }

    void deletion(Location L) {
        root = deleteNode(root, L);
    }

    Node_tree * search(int val){
        return helpsearch(root, val);
    }

    
};

int main() {
    AVL avlTree;
    //first location
    LinkedList incidents120;
    incidents120.insert("Fire near bank", 1);
    incidents120.insert("Traffic Accident", 2);
    incidents120.insert("people fight at street 3", 3);
    Location loc1(120, "Zro-pt", "Isb", incidents120);
    avlTree.insert(loc1);

    //second location
    LinkedList incidents115;
    incidents115.insert("Main Road Sucide Attack", 1);
    incidents115.insert("Gun Fires", 2);
    avlTree.insert(Location(115, "F-7", "Isb", incidents115));

    //third location
    LinkedList incidents125;
    incidents125.insert("Car blast near centaurus", 1);
    avlTree.insert(Location(125, "F-8", "Isb", incidents125));

    //inorder traversel of tree
    cout << "InOrder Traversel before deletion and before adding a new location at node 120: " << endl << endl;
    avlTree.traverseTree();

    //adding a new incident
    cout << endl << endl << "Adding a new incident at node 120: " << endl << endl;
    Node_tree * node = avlTree.search(120);
    node->L.incident.insert("Robery in Market", 4);
    avlTree.traverseTree();

    //deleting an incident
    cout << endl << endl << "Deleting incident at node 120 with ID 3: " << endl << endl;
    Node_tree * node2 = avlTree.search(120);
    node->L.incident.deleteById(3);
    avlTree.traverseTree();

    //deleting whole node
    cout << endl << endl << "InOrder Traversel After Deletion of Node 120: " << endl << endl;
    avlTree.deletion(loc1);
    avlTree.traverseTree();//inorder

    return 0;
}

