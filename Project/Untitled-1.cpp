#include<iostream>
using namespace std;

struct Node{
    Node * left;
    Node * right;
    int data;
};


class Trees{
    private:

    Node * root;

    Node *IPRE(Node * root){
        Node *tmp = root;
        tmp = tmp->left;
        while(tmp->right != NULL){
            tmp = tmp->right;
        }
        return tmp;
    }

    Node * helpsearch(Node * root, int data){
        if(root == NULL){
            cout<<"Tree is empty!"<<endl;
            return NULL;
        }
        if(root->data == data){
            return root;
        }
        if(data < root->data){
            return helpsearch(root->left, data);
        }
        if(data > root->data){
            return helpsearch(root->right, data);
        }
    }

    Node * deleteNode(Node * root, int data){
        if(root == NULL){
            return NULL;
        }
        if(root->left == NULL && root->right == NULL){
            delete root;
            return NULL;
        }
        if(data < root->data){
            root->left = deleteNode(root->left, data);
        }
        if(data > root->data){
            root->right = deleteNode(root->right, data);
        }
        else{
            Node *IPre = IPRE(root);
            root->data = IPre->data;
            root->left = deleteNode(root->left, IPre->data);
        }
        return root;
    }

    void helpinOrder(Node * root){
        if(root!=NULL){
            helpinOrder(root->left);
            cout<<root->data<<" ";
            helpinOrder(root->right);
        }
    }

    public:
    Trees(){
        root = NULL;
    }

    Node * createNode(int data){
        Node * newNode = new Node;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->data = data;
        return newNode;
    }

    

    void insert(int data){
        Node * prev = NULL;
        Node *tmp = root;
        Node *newNode = createNode(data);
        if(tmp == NULL){
            root = newNode;
            return;
        }
        while(tmp != NULL){
            prev = tmp;
            if(tmp->data > data){
                tmp = tmp->left;
            }
            else{
                tmp = tmp->right;
            }
        }
        if(data < prev->data){
            prev->left = newNode;
        }
        else{
            prev->right = newNode;
        }   
    }


    Node * search(int data){
        Node*tmp = root;
        return helpsearch(tmp, data);
    }

    void del(int data){
        Node *tmp = root;
        root = deleteNode(tmp,data);
    }

    void inOrder(){
        Node *tmp = root;
        helpinOrder(tmp);   
    }

};

int main(){
    Trees T;
    T.insert(50);
    T.insert(9);
    T.insert(200);
    T.insert(50);
    T.inOrder();
    T.del(50);
    T.inOrder();
    Node * s = T.search(50);
    cout<<s->data<<endl;

    return 0;
}