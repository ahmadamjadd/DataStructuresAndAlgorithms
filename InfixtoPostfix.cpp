#include <iostream>
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

bool isnotavariable(char ch) {
    if (ch == '-' || ch == '+' || ch == '*' || ch == '/' || ch == '$' || ch == '^') {
        return true;
    }
    if (ch == '[' || ch == '{' || ch == '(' || ch == ')' || ch == '}' || ch == ']') {
        return true;
    }
    return false;
}

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

char* infixtopostfix(const char* exp) {
    Stack S(100);
    char* array = new char[100];
    int j = 0;

    for (int i = 0; exp[i] != '\0'; i++) {
        if (!isnotavariable(exp[i])) {
            array[j++] = exp[i];
        } else if (exp[i] == '[' || exp[i] == '{' || exp[i] == '(') {
            S.push(exp[i]);
        } else if (exp[i] == ']' || exp[i] == '}' || exp[i] == ')') {
            while (S.top1() != '[' && S.top1() != '{' && S.top1() != '(') {
                array[j++] = S.pop();
            }
            S.pop();
        } else {
            while (!S.isEmpty() && precedence(S.top1()) >= precedence(exp[i])) {
                array[j++] = S.pop();
            }
            S.push(exp[i]);
        }
    }

    while (!S.isEmpty()) {
        array[j++] = S.pop();
    }

    array[j] = '\0';
    return array;
}

int main() {
    const char* exp = "A+(B*C-(D/E^F)*G)*H";
    char* array = infixtopostfix(exp);

    for (int i = 0; array[i] != '\0'; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    delete[] array;
    return 0;
}



/*#include <iostream>
#include <cctype> // For isdigit() and isalpha()

void checkCharacter(char c) {
    if (std::isdigit(c) || std::isalpha(c)) {
        std::cout << c << " is an operand.\n";
    } else if (strchr("+-*%^&|!~=", c)) {
        std::cout << c << " is an operator.\n";
    } else {
        std::cout << c << " is neither an operand nor an operator.\n";
    }
}

int main() {
    const char* str = "a+b*c-d";
    
    for (const char* p = str; *p != '\0'; ++p) {
        checkCharacter(*p);
    }

    return 0;
}
*/