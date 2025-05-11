#include "expression_evaluator.h"
#include <cctype>
#include <cstring>
#include <stack>
#include <stdlib.h>
#include <cmath>
using namespace std;

struct Node {
    char data;
    Node* next;
};

class Stack {
private:
    Node* top;
    int size;
public:
    Stack() { top = nullptr; size = 0; }

    void push(char ch) {
        Node* newNode = new Node();
        newNode->data = ch;
        newNode->next = nullptr;
        if (top == nullptr) {
            top = newNode;
        } else {
            Node* nowNode = top;
            while (nowNode->next != nullptr) {
                nowNode = nowNode->next;
            }
            nowNode->next = newNode;
        }
        size++;
    }

    char pop() {
        if (isEmpty()) return '\0';
        Node *nowNode = top, *deledNode;
        if (size != 1) {
            for (int i = 0; i < (size - 2); i++) {
                nowNode = nowNode->next;
            }
            deledNode = nowNode->next;
            nowNode->next = nullptr;
        } else {
            deledNode = top;
            top = nullptr;
        }
        char ans = deledNode->data;
        delete deledNode;
        size--;
        return ans;
    }

    char peek() {
        if (isEmpty()) return '\0';
        Node* nowNode = top;
        for (int i = 0; i < size - 1; i++) {
            nowNode = nowNode->next;
        }
        return nowNode->data;
    }

    bool isEmpty() {
        return (size == 0);
    }
};

int precedence(char op) {
    if ((op >= '0' && op <= '9') || (op >= 'A' && op <= 'Z') || op == '.')
        return 5;
    else if (op == '(')
        return 4;
    else if (op == '+' || op == '-')
        return 3;
    else if (op == '*' || op == '/' || op == '%')
        return 2;
    else if (op == '^')
        return 1;
    else if (op == ')')
        return 0;
    else
        return -1;
}

void InfixToPostfix(const char* infix, char* postfix) {
    if (strlen(infix) == 0) {
        postfix[0] = '\0';
        return;
    }

    Stack stack;
    char back;
    int infixIndex = 0, postIndex = 0;
    bool expectUnary = true;

    while (infix[infixIndex] != '\0') {
        switch (precedence(infix[infixIndex])) {
        case 5:
            postfix[postIndex++] = ' ';
            while (precedence(infix[infixIndex]) == 5)
                postfix[postIndex++] = infix[infixIndex++];
            postfix[postIndex++] = ' ';
            infixIndex--;
            expectUnary = false;
            break;
        case 4:
            stack.push(infix[infixIndex]);
            expectUnary = true;
            break;
        case 3:
            if (expectUnary) {
                postfix[postIndex++] = ' ';
                postfix[postIndex++] = '0';
                postfix[postIndex++] = ' ';
                stack.push(infix[infixIndex]);
            } else {
                while (!stack.isEmpty()) {
                    back = stack.peek();
                    if (precedence(back) <= 3)
                        postfix[postIndex++] = stack.pop();
                    else break;
                }
                stack.push(infix[infixIndex]);
            }
            expectUnary = true;
            break;
        case 2:
            while (!stack.isEmpty()) {
                back = stack.peek();
                if (precedence(back) <= 2)
                    postfix[postIndex++] = stack.pop();
                else break;
            }
            stack.push(infix[infixIndex]);
            expectUnary = true;
            break;
        case 1:
            while (!stack.isEmpty() && precedence(stack.peek()) == 1)
                postfix[postIndex++] = stack.pop();
            stack.push(infix[infixIndex]);
            expectUnary = true;
            break;
        case 0:
            back = stack.pop();
            while (precedence(back) != 4 && back != '\0') {
                postfix[postIndex++] = back;
                back = stack.pop();
            }
            expectUnary = false;
            break;
        default:
            break;
        }
        infixIndex++;
    }

    while (!stack.isEmpty())
        postfix[postIndex++] = stack.pop();
    postfix[postIndex++] = '\0';
}

double calculator(char* postfix) {
    if (strlen(postfix) == 0)
        return 0;

    stack<double> NumStack;
    int index = 0;

    while (postfix[index] != '\0') {
        if (postfix[index] == ' ') {
            index++;
            continue;
        }
        if (precedence(postfix[index]) == 5) {
            char tmp[20]; int t_index = 0;
            while (precedence(postfix[index]) == 5 && t_index < 19)
                tmp[t_index++] = postfix[index++];
            tmp[t_index] = '\0';
            double num = atof(tmp);
            NumStack.push(num);
        } else {
            if (NumStack.size() < 2) return 0;
            double Num1 = NumStack.top(); NumStack.pop();
            double Num2 = NumStack.top(); NumStack.pop();
            switch (postfix[index]) {
            case '+': NumStack.push(Num2 + Num1); break;
            case '-': NumStack.push(Num2 - Num1); break;
            case '*': NumStack.push(Num2 * Num1); break;
            case '/': NumStack.push(Num2 / Num1); break;
            case '%': NumStack.push((int)Num2 % (int)Num1); break;
            case '^': NumStack.push(pow(Num2, Num1)); break;
            default: break;
            }
        }
        index++;
    }
    return NumStack.top();
}
