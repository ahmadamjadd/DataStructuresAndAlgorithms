//Interleave the First Half and Second Half of a Queue Using Recursion

#include<iostream>
#include<queue>
using namespace std;

void reverse(queue<int> &q){
    if(q.empty()){
        return;
    }
    int tmp = q.front();
    q.pop();

    reverse(q);

    q.push(tmp);
}

void interleave(queue<int> &q, int half_size){
    if(half_size == 0){
        return;
    }
    int tmp = q.front();
    q.pop();

    interleave(q, half_size-1);
    if(half_size == 1){
        reverse(q);
    }
    q.push(q.front());
    q.pop();
    q.push(tmp);
}

void interleaveQueue(queue<int> &q){
    if(q.size() %2 == 0){
        interleave(q, q.size()/2);
        reverse(q);
        return;
    }
    for(int i = 0; i< q.size()-1; i++){
        q.push(q.front());
        q.pop();
    }
    int tmp = q.front();
    q.pop();
    interleave(q, q.size()/2);
    reverse(q);
    q.push(tmp);
}

int main(){
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);
    interleaveQueue(q);
    while (!q.empty()) {  // Corrected loop to avoid issues with size changing
        cout << q.front() << " ";
        q.pop();
    }
    return 0;
    return 0;
}



