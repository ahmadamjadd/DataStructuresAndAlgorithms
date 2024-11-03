#include<iostream>
using namespace std;
#include<queue>

void reverse(queue<int> &q){
    if(q.empty()){
        return;
    }
    int tmp = q.front();
    q.pop();

    reverse(q);

    q.push(tmp);
}

int main(){
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    reverse(q);
    while (!q.empty()) {  // Corrected loop to avoid issues with size changing
        cout << q.front() << " ";
        q.pop();
    }
    return 0;
}
