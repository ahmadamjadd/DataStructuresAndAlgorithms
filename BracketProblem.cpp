#include <iostream>
using namespace std;

class Stack{
    private:
    int size;
    char *array;
    int top;

    public:
    Stack(int size){
        this->size = size;
        array = new char[size];
        top = -1;
    }

    void push(char val){
        array[++top] = val;
    }

    char pop(){
        return array[top--];
    }

    bool isEmpty(){
        return top == -1;
    }

    char top1(){
        return array[top];
    }

    // Priority logic for opening brackets (optional but does not impact closing brackets)
    int priority(char ch){
        if(ch == '[') return 2;
        if(ch == '{') return 1;
        if(ch == '(') return 0;
        return -1;  // Invalid character or closing brackets
    }

    bool match(char ch1, char ch2){
        return (ch1 == '[' && ch2 == ']') ||
               (ch1 == '{' && ch2 == '}') ||
               (ch1 == '(' && ch2 == ')');
    }

    bool parenthesis_check(const char* exp){
        for(int i = 0; exp[i] != '\0'; i++){
            // Push opening parentheses
            if(exp[i] == '[' || exp[i] == '{' || exp[i] == '('){
                push(exp[i]);
            }

            // For closing parentheses, check for match and pop
            else if(exp[i] == ']' || exp[i] == ')' || exp[i] == '}'){
                if(isEmpty()){ 
                    return false;  // Unmatched closing parenthesis
                }
                char topChar = pop();
                if(!match(topChar, exp[i])){
                    return false;  // Parentheses do not match
                }
            }
        }
        return isEmpty();  // Stack should be empty if all parentheses are balanced
    }
};

int main(){
    Stack S(100);
    const char* exp = "[1+{2+(3-0)}]";  // Test expression

    if(S.parenthesis_check(exp)) {
        cout << "Everything is FINE!" << endl;
    } else {
        cout << "Mismatched parentheses!" << endl;
    }

    return 0;
}

