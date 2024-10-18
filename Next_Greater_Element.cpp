/*Given an array of integers, for each element, find the next greater element (NGE) to its right.
 If there is no greater element to the right, assign -1 to that element.*/


#include<iostream>
#include <stack>
#include <vector>
#include <climits>
using namespace std;

vector<int> NextGreaterNumber(vector<int> array){
    vector<int> NGE;
    stack<int> S;
    for(int i = 0; i<array.size(); i++){
        for(int j = i+1; j<array.size(); j++){
            if(array[i]<array[j]){
                S.push(array[j]);
                break;
            }
        }
        int min = INT_MAX;
        if(S.empty()){
            NGE.push_back(-1);
        }
        else{
                NGE.push_back(S.top());   
                S.pop();
            }
        }
        return NGE;
    }
    


void display(vector<int> a){
    for(int i = 0; i<a.size(); i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}



int main(){
    vector<int> array;
    array.push_back(4);
    array.push_back(5);
    array.push_back(2);
    array.push_back(10);
    array.push_back(8);
    display(array);

    vector<int> NGE = NextGreaterNumber(array);
    display(NGE);

    return 0;
}