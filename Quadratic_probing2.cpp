#include<iostream>
#include<string>
using namespace std;

struct Node{
    string key;
    int value;
    bool isDeleted;

    Node(): key(""), value(-1), isDeleted(false) {}
};

class Hashmap{
    int size;
    Node* array;

    public:
    Hashmap(int size){
        this->size = size;
        array = new Node[size];
    }

    int hashfunc(string key){
        int hash = 0;
        for(char ch : key){
            hash = (hash + ch) % size;
        }
        return hash;
    }

    void insert(string key, int value){
        int index = hashfunc(key);
        int i = 0;
        while(array[index].key != "" && array[index].key != key && !array[index].isDeleted){
            i++;
            index = (index + i*i)%size;
            if(i>size){
                cout<<"Not enough space"<<endl;
                return;
            }
        }
        array[index].key = key;
        array[index].value = value;
        array[index].isDeleted = false;
    }

    void del(string key){
        int index = hashfunc(key);
        int i = 0;
        while(array[index].key != ""){
            if(array[index].key == key && !array[index].isDeleted){
                array[index].isDeleted = true;
                cout<<"Removed!"<<endl;
                return;
            }
            i++;
            index = (index + (i*i)) %size;
            if(i>size){
                break;
            }
        }
        cout<<"value not found!"<<endl;
    }

    void display(){
        for(int i = 0; i<size; i++){
            cout<<i<<"==> ";
            if(array[i].key != "" && !array[i].isDeleted){
                cout<<"["<< array[i].key <<", "<<array[i].value<<"]";
                cout<<endl;
            }
            else if(array[i].isDeleted){
                cout<<"Deleted"<<endl;
            }
            else{
                cout << "empty"<<endl;
            }
        }
    }
};

int main(){
    Hashmap H(10);
    H.insert("apple", 90);
    H.insert("banana", 40);
    H.del("banana");
    H.display();
    return 0;
}
