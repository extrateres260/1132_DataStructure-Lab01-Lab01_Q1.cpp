
#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

// 定義 Stack 的節點結構

struct Node {
    char data; // 存儲字符 (運算子或括號)
    Node* next; // 指向下一個節點
};

// 使用 linked list 實作 Stack
class Stack {
private:
    Node* top;   // 指向堆疊頂端
public:
    Stack() { top = nullptr; } // 初始化堆疊

    // Push 操作:將元素放入堆疊
    void push(char ch) {
        Node* newNode = new Node; // Create a new node
        newNode->data = ch;       // Set the data of the new node
        newNode->next = top;      // Link the new node to the previous top
        top = newNode;            // Update the top pointer to the new node
    }

    // Pop 操作:移除並回傳頂端元素
    char pop() {
        if (top == nullptr) { // Check if the stack is empty
            cout << "Stack is empty!" << endl;
            return '\0'; // Return null character if stack is empty
        }
        char ch = top->data; // Get the data from the top node
        Node* temp = top;    // Store the current top node
        top = top->next;     // Update the top pointer to the next node
        delete temp;         // Delete the old top node
        return ch;          // Return the popped character
    }

    // Peek 操作:取得頂端元素但不移除
    char peek() {
        if (top == nullptr) { // Check if the stack is empty
            cout << "Stack is empty!" << endl;
            return '\0'; // Return null character if stack is empty
        }
        return top->data; // Return the data from the top node
    }

    // 判斷堆疊是否為空
    bool isEmpty() {
        return top == nullptr; // Return true if top is null (stack is empty)
    }
};

// 判斷運算子(加減乘除)的優先順序
int precedence(char oper) {
    switch (oper) { // Check the operator
        case '+':
        case '-':
            return 1; // Lowest precedence
        case '*':
        case '/':
            return 2; // Higher precedence
        default:
            return 0; // Unknown operator
    }
}

// 將中序表達式 (infix) 轉換為後序表達式 (postfix)
void InfixToPostfix(const char* infix, char* postfix) {
    Stack stack; // Create a stack for operators
    int j = 0;   // Index for postfix expression

    for (int i = 0; infix[i] != '\0'; i++) { // Loop through each character in the infix expression
        char ch = infix[i]; // Current character

        if (isalnum(ch)) { // If the character is an operand (number or letter)
            postfix[j++] = ch; // Add it to the postfix expression
        } else if (ch == '(') { // If the character is a left parenthesis
            stack.push(ch); // Push it onto the stack
        } else if (ch == ')') { // If the character is a right parenthesis
            while (!stack.isEmpty() && stack.peek() != '(') { // Pop until left parenthesis is found
                postfix[j++] = stack.pop(); // Add operators to postfix expression
            }
            stack.pop(); // Pop the left parenthesis from the stack
        } else { // If the character is an operator (+, -, *, /)
            while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(ch)) { // Check precedence
                postfix[j++] = stack.pop(); // Pop operators from the stack to postfix expression
            }
            stack.push(ch); // Push the current operator onto the stack
        }
    }

    while (!stack.isEmpty()) { // Pop all remaining operators from the stack
        postfix[j++] = stack.pop(); // Add them to postfix expression
    }
    postfix[j] = '\0'; // Null-terminate the postfix expression string
}

int main() {
    char infix[100], postfix[100];
    cout << "Enter an Infix expression: ";
    cin >> infix; // 輸入中序表達式
    InfixToPostfix(infix, postfix); // 轉換為後序表達式
    cout << "Postfix expression: " << postfix << endl; // 輸出後序表達式
    return 0;
}
