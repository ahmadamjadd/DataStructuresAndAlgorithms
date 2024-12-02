#include <iostream>
#include<vector>
using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;
};

class BST {
private:
    Node *root;
    vector<int> array;

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
    void inOrder(Node * root){
        if(root!=NULL){
            inOrder(root->left);
            array.push_back(root->data);
            inOrder(root->right);
        }
    }
    void merge(BST &tree) {
    inOrder(tree.root); // Traverse the second tree and populate the array
    for (int i = 0; i < array.size(); i++) {
        this->insert(array[i]); // Insert elements into the current tree
    }
    array.clear(); // Clear the temporary storage
}

};

int main() {
    BST tree1;
    BST tree2;

    // Populate tree1
    tree1.insert(5);
    tree1.insert(3);
    tree1.insert(7);

    // Populate tree2
    tree2.insert(2);
    tree2.insert(4);
n
    // Merge tree2 into tree1
    tree1.merge(tree2);

    // Display the result
    cout << "Merged tree1 (in-order): ";
    tree1.display(); // Should display 2 3 4 5 7

    cout << "Tree2 remains unchanged: ";
    tree2.display(); // Should display 2 4

    return 0;
}
