#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class Stack {
private:
    int size;
    string* array;
    int top;

public:
    Stack(int size) {
        this->size = size;
        array = new string[size];
        top = -1;
    }

    void push(const string& val) {
        array[++top] = val;
    }

    string pop() {
        return array[top--];
    }

    bool isEmpty() {
        return top == -1;
    }

    string top1() {
        return array[top];
    }

    int priority(char ch) {
        if (ch == '[') return 2;
        if (ch == '{') return 1;
        if (ch == '(') return 0;
        return -1;
    }

    bool match(char ch1, char ch2) {
        return (ch1 == '[' && ch2 == ']') ||
               (ch1 == '{' && ch2 == '}') ||
               (ch1 == '(' && ch2 == ')');
    }

    ~Stack() {
        delete[] array;
    }
};

string prefixToInfix(const string& exp) {
    Stack s(100);

    for (int i = exp.length() - 1; i >= 0; i--) {
        if (isalnum(exp[i])) {
            s.push(string(1, exp[i]));
        } else {
            string A = s.pop();
            string B = s.pop();
            string combined = "(" + A + " " + exp[i] + " " + B + ")";
            s.push(combined);
        }
    }

    return s.pop();
}

int main() {
    string prefix = "*+ABC";  
    string infix = prefixToInfix(prefix);
    cout << "Infix: " << infix << endl; 
    return 0;
}