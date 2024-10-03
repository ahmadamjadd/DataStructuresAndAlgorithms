#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

class Stack {
private:
    int size;
    char* array;
    int top;

public:
    Stack(int size) {
        this->size = size;
        array = new char[size];
        top = -1;
    }

    ~Stack() {
        delete[] array;
    }

    void push(char val) {
        array[++top] = val;
    }

    char pop() {
        return array[top--];
    }

    bool isEmpty() {
        return top == -1;
    }

    char top1() {
        return array[top];
    }

    bool match(char ch1, char ch2) {
        return (ch1 == '[' && ch2 == ']') ||
               (ch1 == '{' && ch2 == '}') ||
               (ch1 == '(' && ch2 == ')');
    }
};

int precedence(char ch) {
    if (ch == '^') {
        return 3;
    }
    if (ch == '*' || ch == '/') {
        return 2;
    }
    if (ch == '+' || ch == '-') {
        return 1;
    }
    return 0;
}

void reverse(char* exp) {
    int length = strlen(exp);
    for (int i = 0; i < length / 2; i++) {
        swap(exp[i], exp[length - i - 1]);
    }
}

void swapBrackets(char* exp) {
    for (int i = 0; exp[i] != '\0'; i++) {
        if (exp[i] == '(')
            exp[i] = ')';
        else if (exp[i] == ')')
            exp[i] = '(';
    }
}

char* infixtoprefix(const char* exp) {
    Stack S(100);
    char* result = new char[100];
    char* reversedExp = new char[100];
    strcpy(reversedExp, exp);

    reverse(reversedExp);
    swapBrackets(reversedExp);

    int j = 0;
    for (int i = 0; reversedExp[i] != '\0'; i++) {
        if (isalnum(reversedExp[i])) {
            result[j++] = reversedExp[i];
        } else if (reversedExp[i] == '(') {
            S.push(reversedExp[i]);
        } else if (reversedExp[i] == ')') {
            while (S.top1() != '(') {
                result[j++] = S.pop();
            }
            S.pop();
        } else {
            while (!S.isEmpty() && precedence(S.top1()) >= precedence(reversedExp[i])) {
                result[j++] = S.pop();
            }
            S.push(reversedExp[i]);
        }
    }

    while (!S.isEmpty()) {
        result[j++] = S.pop();
    }

    result[j] = '\0';

    reverse(result);
    delete[] reversedExp;
    return result;
}

int main() {
    const char* exp = "A+(B*C-(D/E^F)*G)*H";
    char* prefix = infixtoprefix(exp);

    cout << "Prefix Expression: " << prefix << endl;

    delete[] prefix;
    return 0;
}
