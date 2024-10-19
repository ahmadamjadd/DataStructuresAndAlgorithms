#include<iostream>
using namespace std;

class CircularQueue{
    struct Node{
        int data;
        Node *next;
    };
    int size;
    Node *head;
    Node *tail;
    public:
    CircularQueue(int size){
        head = NULL;
        tail = NULL;
        this->size = size;

    }
    void enqueue(int data){
        if(size>0){
            Node *newptr = new Node;
            newptr->data = data;
            if(head == NULL){
                head = newptr;
                tail = newptr;
                newptr->next = newptr;
                size--;
                return;
            }
            tail->next = newptr;
            newptr->next = head;
            tail = newptr;
            size--;
        }
        else{
            cout<<"Queue is FULL"<<endl;
        }
        
    }

    void deque(){
        if(isEmpty()){
            cout<<"Queue is Empty"<<endl;
            return;
        }
        Node *tmpPtr = head;
        if(head == tail){
            head = NULL;
            tail = NULL;
            delete tmpPtr;
            return;
        }
        tail->next = head->next;
        head = head->next;
        size++;
        delete tmpPtr;
    }
    
    bool isEmpty(){
        if(head == NULL){
            return true;
        }
        return false;
    }

    int peek(){
        return head->data;
    }

    void display(){
        Node *tmp = head;
        do{
            cout<<tmp->data<<" ";
            tmp=tmp->next;

        }while(tmp!=head);
    }
};
int main(){
    CircularQueue Q1(2);
    Q1.enqueue(1);
    Q1.enqueue(1);
    Q1.enqueue(1);
    Q1.display();
    Q1.deque();
    Q1.deque();
    Q1.deque();
    return 0;
}