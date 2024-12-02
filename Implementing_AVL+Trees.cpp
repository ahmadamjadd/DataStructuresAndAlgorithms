#include <iostream>
using namespace std;

// Node structure
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

// Function to get the height of the tree
int getHeight(Node* node) {
    return (node == nullptr) ? 0 : node->height;
}

// Helper function to create a new node
Node* createNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1; // Initial height is 1
    return node;
}

// Function to get the balance factor of a node
int getBalanceFactor(Node* node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Right rotation
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x; // New root
}

// Left rotation
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y; // New root
}

// Insert function
Node* insert(Node* node, int key) {
    // Perform the normal BST insertion
    if (node == nullptr) return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // No duplicates allowed

    // Update height
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Get the balance factor
    int balance = getBalanceFactor(node);

    // Perform rotations to balance the tree
    // Left-Left (LL) case
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    // Right-Right (RR) case
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    // Left-Right (LR) case
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right-Left (RL) case
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node; // Return the unchanged node
}

// Function to find the node with the minimum key
Node* findMinNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Delete function
Node* deleteNode(Node* root, int key) {
    if (root == nullptr) return root;

    // Perform standard BST delete
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node with only one child or no child
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == nullptr) { // No child
                temp = root;
                root = nullptr;
            } else // One child
                *root = *temp;

            delete temp;
        } else {
            // Node with two children
            Node* temp = findMinNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node
    if (root == nullptr) return root;

    // Update height
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Get the balance factor
    int balance = getBalanceFactor(root);

    // Perform rotations to balance the tree
    // Left-Left (LL) case
    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rotateRight(root);

    // Left-Right (LR) case
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right-Right (RR) case
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return rotateLeft(root);

    // Right-Left (RL) case
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// In-order traversal
void inOrderTraversal(Node* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);
        cout << root->key << " ";
        inOrderTraversal(root->right);
    }
}

// Main function
int main() {
    Node* root = nullptr;

    // Insert elements
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    cout << "In-order traversal of AVL tree: ";
    inOrderTraversal(root);
    cout << endl;

    // Delete a node
    root = deleteNode(root, 40);
    cout << "In-order traversal after deletion of 40: ";
    inOrderTraversal(root);
    cout << endl;

    return 0;
}
