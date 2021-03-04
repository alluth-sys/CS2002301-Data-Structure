#include <iostream>
#pragma warning(disable: 4996)
#define MAX 80
using namespace std;

bool isOperand(char c);
int value(char c); //char to int
int prec(char c); // return precedence
bool check_bracket(char input[]);
bool check_input(char input[]);
int calculatePostfix(char* exp);

template <typename T>
class Stack {
    T top;

public:
    T a[MAX]; // Maximum size of Stack 

    Stack() { top = -1; }
    void push(T x) {
        a[++top] = x;
    }
    T pop() {
        T x = a[top--];
        return x;
    }
    T getTop() {
        return a[top];
    }
    inline bool isEmpty() {
        return (top < 0);
    }
};



int main() {
    char expr[MAX];//MAX expression is 80

    while (cin >> expr) {
        int len = 0;
        int result;
        char* postfix;

        //count length of string for scanning
        while (expr[len] != '\0') {
            len++;
        }

        //check bracket is balanced or not
        if ((check_bracket(expr) && check_input(expr))) {

            //Postfix to infix
            Stack<char> stack;
            stack.push('#'); // to prevent underflow
            char postfix[MAX] = {'\0'};
            int postfixPos = 0;

            for (int i = 0; i < len; i++) {
                if (isOperand(expr[i])) {
                    postfix[postfixPos] = expr[i];
                    postfixPos++;
                    if (!isOperand(expr[i + 1])) {
                        postfix[postfixPos] = ' ';
                        postfixPos++;
                    }
                }
                else if (expr[i] == '(') {
                    stack.push('(');
                }
                else if (expr[i] == ')') {
                    while (stack.getTop() != '#' && stack.getTop() != '(') {
                        char c = stack.pop();
                        postfix[postfixPos] = c;
                        postfix[postfixPos + 1] = ' ';
                        postfixPos += 2;
                    }
                    if (stack.getTop() == '(') {
                        char c = stack.pop();
                    }
                }
                else {
                    while (stack.getTop() != '#' && prec(expr[i]) <= prec(stack.getTop()))
                    {
                        char c = stack.pop();
                        postfix[postfixPos] = c;
                        postfix[postfixPos + 1] = ' ';
                        postfixPos += 2;

                    }
                    stack.push(expr[i]);
                }
            }

            while (stack.getTop() != '#')
            {
                char c = stack.pop();
                postfix[postfixPos] = c;
                postfix[postfixPos + 1] = ' ';
                postfixPos += 2;
            }
            if (postfix[postfixPos-1] == ' ') {
                postfix[postfixPos-1] = '\0';
                postfixPos--;
            }

            for (int i = 0; i < postfixPos; i++) {
                cout << postfix[i];
            }

            cout << endl;

            int result = calculatePostfix(postfix);
            cout << result << endl;

        }

        else {
            cout << "invalid" << endl;
        }

    }
}

//////////////////////////// function definition //////////////////////////////////

bool isOperand(char c) { return (c >= '0' && c <= '9'); }

int value(char c) { return (c - '0'); }

int prec(char c)
{
    if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}


int calculatePostfix(char* exp)
{
    Stack<int> stack;
    int i = 0;
    int num;

    int len = 0;
    while (exp[i] != '\0') {
        len++;
        i++;
    }

    for (i = 0; i < len; ++i)
    {
        if (isdigit(exp[i])) {
            int k = i;
            int temp = value(exp[i]);
            while (isdigit(exp[k + 1])) {
                temp *= 10;
                int add = value(exp[k + 1]);
                temp += add;
                k++;
                i++;
            }
            stack.push(temp);
        }
        else if (exp[i] == ' ') {
            continue;
        }
        else
        {
            int val1 = stack.pop();
            int val2 = stack.pop();
            switch (exp[i])
            {
            case '+': stack.push(val2 + val1); break;
            case '-': stack.push(val2 - val1); break;
            case '*': stack.push(val2 * val1); break;
            case '/': stack.push(val2 / val1); break;
            }
        }
    }
    return stack.getTop();
}

bool check_bracket(char input[]) {
    int left_bracket = 0;
    int right_bracket = 0;
    int len = 0;

    while (input[len] != '\0') {
        len++;
    }

    for (int i = 0; i < len; i++) {
        if (input[i] == '(') {
            left_bracket++;
        }
        else if (input[i] == ')') {
            right_bracket++;
        }
    }

    if (right_bracket == left_bracket) {
        return true;
    }
    return false;
}

bool check_input(char input[]) {
    if (input[0] == '\0') return false;
    if (check_bracket(input)) {
        for (int i = 0; input[i] != '\0'; ++i) {
            if (input[i] == '+' || input[i] == '-' || input[i] == '*') {
                if (input[i + 1] == '+' || input[i + 1] == '-' || input[i + 1] == '*' || input[i + 1] == ')' || input[i + 1] == '\0') {
                    return false;
                }
            }
            else if (input[i] == '(') {
                if (input[i + 1] == ')' || input[i + 1] == '+' || input[i + 1] == '-' || input[i + 1] == '*' || input[i + 1] == '\0')
                    return false;
            }
            else if (input[i] == ')') {
                if (input[i + 1] == '(')return false;
                if (input[i + 1] != '+' && input[i + 1] != '-' && input[i + 1] != '*' && input[i + 1] != ')' && input[i + 1] != '\0')return false;
            }
            else {
                if (input[i + 1] == '(')return false;
            }
        }
        return true;
    }
    else return false;
}
