#include<iostream>
#include<stack>
#include<cctype>
#include<string>
#include<cstring>
using namespace std;


std::string removespaces(const std::string& a) {
    const char* b = a.c_str();
    char* b2 = new char[a.length() + 1]; // +1 for null terminator
    int j = 0; // Index for the new char array

    for (int i = 0; i < a.length(); i++) {
        if (b[i] != ' ') { // Only copy non-space characters
            b2[j] = b[i];
            j++;
        }
    }
    b2[j] = '\0'; // Null-terminate the new string

    std::string result(b2); // Create a std::string from the char array

    delete[] b2; // Free the allocated memory
    return result; // Return the new string
}


int EvaluatingPostFixExpression(string exp){
    stack<int> s;
    for(int i = 0; i<exp.length(); i++){
        if(isalnum(exp[i])){
            string a(1, exp[i]);
            int num = stoi(a);
            s.push(num);
        }
        else{
            int num1 = s.top();
            s.pop();
            int num2 = s.top();
            s.pop();
            int result;
            char choice = exp[i];
            switch(choice){
                case '+':{
                    result = num1 + num2; 
                    break; 
                }
                case '-':
                {
                    result = num1 - num2;
                    break;
                }
                case '*':
                {
                    result = num1 * num2;
                    break;
                }
                case '/':
                {
                    result = num1 / num2;
                    break;
                }
            }

            s.push(result);
        }

        
    }
    return s.top();
}

int main(){
    string a = "2 3 + 5 *";
    a = removespaces(a);
    int ans = EvaluatingPostFixExpression(a);
    cout<<ans<<endl;
    return 0;
}