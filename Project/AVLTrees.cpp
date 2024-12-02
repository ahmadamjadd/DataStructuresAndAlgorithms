#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
    Node *left;
    Node *right;
    int data;
    int height;
};

class AVLTrees
{
private:
    Node *root;

    Node *RightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    Node *LeftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        x->right = T2;
        y->left = x;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Node *helpinsert(Node *root, int data)
    {
        if (root == NULL)
        {
            return createNode(data);
        }

        if (data < root->data)
        {
            root->left = helpinsert(root->left, data);
        }
        else
        {
            root->right = helpinsert(root->right, data);
        }

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int bf = BalanceFactor(root);

        if (bf > 1 && data < root->left->data)
        {
            return LeftRotate(root);
        }

        if (bf < -1 && data > root->right->data)
        {
            return RightRotate(root);
        }

        if (bf > 1 && data > root->left->data)
        {
            root->left = LeftRotate(root->left);
            return RightRotate(root);
        }
        if (bf < -1 && data < root->right->data)
        {
            root->right = RightRotate(root->right);
            return LeftRotate(root);
        }

        return root;
    }

    Node *createNode(int data)
    {
        Node *newNode = new Node;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->data = data;
        newNode->height = 1;
        return newNode;
    }

    int getHeight(Node *node)
    {
        if (node == NULL)
            return 0;
        return node->height;
    }

    int BalanceFactor(Node *node)
    {
        if (node == NULL)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    void helpinOrder(Node *root)
    {
        if (root != NULL)
        {
            helpinOrder(root->left);
            cout << root->data << " ";
            helpinOrder(root->right);
        }
    }

    Node *helpsearch(Node *root, int data)
    {
        if (root == NULL)
        {
            cout << "Tree is empty!" << endl;
            return NULL;
        }
        if (root->data == data)
        {
            return root;
        }
        if (data < root->data)
        {
            return helpsearch(root->left, data);
        }
        if (data > root->data)
        {
            return helpsearch(root->right, data);
        }
    }

    Node *IPRE(Node *root)
    {
        Node *tmp = root;
        tmp = tmp->left;
        while (tmp->right != NULL)
        {
            tmp = tmp->right;
        }
        return tmp;
    }

    Node *deleteNode(Node *root, int data)
    {
        if (root == NULL)
        {
            return NULL;
        }
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            return NULL;
        }
        if (data < root->data)
        {
            root->left = deleteNode(root->left, data);
        }
        if (data > root->data)
        {
            root->right = deleteNode(root->right, data);
        }
        else
        {
            Node *IPre = IPRE(root);
            root->data = IPre->data;
            root->left = deleteNode(root->left, IPre->data);
        }
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int bf = BalanceFactor(root);

        if (bf > 1 && BalanceFactor(root->left) >= 0)
        {
            return LeftRotate(root);
        }

        if (bf > 1 && BalanceFactor(root->left) < 0)
        {
            root->left = RightRotate(root->left);
            return LeftRotate(root);
        }

        if (bf < -1 && BalanceFactor(root->right) <= 0)
        {
            return RightRotate(root);
        }

        if (bf < -1 && BalanceFactor(root->right) > 0)
        {
            root->right = LeftRotate(root->right);
            return RightRotate(root);
        }

        return root;
    }

public:
    AVLTrees()
    {
        root = NULL;
    }

    void insert(int data)
    {
        root = helpinsert(root, data);
    }

    void inOrder()
    {
        helpinOrder(root);
        cout << endl;
    }

    Node *search(int data)
    {
        Node *tmp = root;
        return helpsearch(tmp, data);
    }

    void del(int data)
    {
        Node *tmp = root;
        root = deleteNode(tmp, data);
    }
};

int main() {
    AVLTrees T;
    
    // Insert values
    T.insert(50);
    T.insert(50);
    T.insert(9);
    T.insert(200);

    // Print in-order traversal of the tree
    T.inOrder();
    cout << endl;

    // Delete a node and print the tree again
    T.del(50);
    T.inOrder();
    cout << endl;

    // Search for a value after deletion
    Node *s = T.search(50);
    if (s != NULL) {
        cout << s->data << endl;
    } else {
        cout << "Node not found!" << endl;  // This will now correctly handle the case where the node is not found
    }

    return 0;
}
