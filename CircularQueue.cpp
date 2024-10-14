class MyCircularQueue {
    int *array;
    int size;
    int front;
    int rear;
public:
    MyCircularQueue(int k) {
        this->size = k+1;
        array = new int[size];
        front = 0;
        rear = 0;   
    }
    
    bool enQueue(int value) {
        if(isFull()){
            return false;
        } 
        rear = (rear + 1)%size;
        array[rear] = value;
        return true;   
    }
    
    bool deQueue() {
        if(isEmpty()){
            return false;
        }
        front = (front+1)%size;
        return true;    
    }
    
    int Front() {
        if(!isEmpty()){
            int index = (front +1)%size;
            return array[index];
        }
        return -1;
          
    }
    
    int Rear() {
        if(!isEmpty()){
           return array[rear];
        }
        return -1;
        
        
    }
    
    bool isEmpty() {
        if(front == rear){
            return true;
        }
        return false;
        
    }
    
    bool isFull() {
        if(((rear+1)%size) == front){
            return true;
        }
        return false;
    
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */