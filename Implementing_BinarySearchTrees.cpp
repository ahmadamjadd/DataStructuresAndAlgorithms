#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;
};

class BST {
private:
    Node *root;

    Node *createNode(int data) {
        Node *newNode = new Node;
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    Node *deleteNode(Node *root, int data) {
        if (root == NULL) {
            return NULL;
        }

        // Searching for the node to be deleted
        if (data < root->data) {
            root->left = deleteNode(root->left, data);
        } else if (data > root->data) {
            root->right = deleteNode(root->right, data);
        } else {
            // Node with one child or no child
            if (root->left == NULL) {
                Node *temp = root->right;
                delete root;
                return temp;
            } else if (root->right == NULL) {
                Node *temp = root->left;
                delete root;
                return temp;
            }

            // Node with two children
            Node *inOrderSuccessor = findMin(root->right);
            root->data = inOrderSuccessor->data;
            root->right = deleteNode(root->right, inOrderSuccessor->data);
        }
        return root;
    }

    Node *findMin(Node *root) {
        while (root->left != NULL) {
            root = root->left;
        }
        return root;
    }

    void inOrderTraversal(Node *root) {
        if (root == NULL) {
            return;
        }
        inOrderTraversal(root->left);
        cout << root->data << " ";
        inOrderTraversal(root->right);
    }

public:
    BST() {
        root = NULL;
    }

    void insert(int data) {
        Node *newNode = createNode(data);
        if (root == NULL) {
            root = newNode;
            return;
        }

        Node *curr = root;
        Node *prev = NULL;

        while (curr != NULL) {
            prev = curr;
            if (data == curr->data) {
                cout << "Cannot add duplicate value: " << data << endl;
                return;
            } else if (data < curr->data) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }

        if (data < prev->data) {
            prev->left = newNode;
        } else {
            prev->right = newNode;
        }
    }

    void del(int data) {
        root = deleteNode(root, data);
    }

    void display() {
        if (root == NULL) {
            cout << "Tree is empty" << endl;
        } else {
            inOrderTraversal(root);
            cout << endl;
        }
    }
    void tmpsearch(Node * root, int val){
        if(root == NULL){
            cout<<"Element not found"<<endl;
            return;
        }
        if(val == root->data){
            cout<<"Element found"<<endl;
            return;
        }
        if(val>root->data){
            tmpsearch(root->right, val);
        }
        else{
            tmpsearch(root->left, val);
        }

    }
    void search(int val){
        tmpsearch(root, val);
    }
};

int main() {
    BST tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    cout << "Tree in-order before deletion:" << endl;
    tree.display();

    tree.del(7);
    cout << "Tree in-order after deleting 7:" << endl;
    tree.display();

    tree.del(5);
    cout << "Tree in-order after deleting 5:" << endl;
    tree.display();
    tree.search(5);
    tree.search(6);

    return 0;
}
