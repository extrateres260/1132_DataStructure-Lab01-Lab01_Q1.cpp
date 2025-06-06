#include <iostream>
#include <cctype>
#include <cstring>
#include <stack>
#include <stdlib.h>
#include <cmath>
using namespace std;

// 定義 Stack 的節點結構
struct Node {
    char data;  // 存儲字符 (運算子或括號)
    Node* next; // 指向下一個節點
};

// 使用 linked list 實作 Stack
class Stack {
private:
    Node* top; // 指向堆疊頂端
    int size;
public:
    Stack() { top = nullptr;size=0;} // 初始化堆疊

    // Push 操作：將元素放入堆疊
    void push(char ch) {
        Node* newNode = new Node();  // 創建新資料
        newNode -> data = ch;   // 放入資料
        newNode -> next = nullptr;  // 遇先指向下一筆資料
        if (top== nullptr){  // 當這個linked list為空時
            top = newNode;  // 直接放入top
        }else{
            Node *nowNode = top;  // 遍歷link list找到最後一個資料
            while(nowNode->next!=nullptr){
                nowNode = nowNode->next;
            }
            nowNode->next=newNode; // 放入新資料
        }
        size++;// 資料加一
    }

    // Pop 操作：移除並回傳頂端元素
    char pop() {
        if (isEmpty()){ // 報錯：linked list 為空
            cout<<"Linked List is empty"<<endl;
            return '\0';
        }
        Node *nowNode = top, *deledNode; // 找到目標資料的前一位
        if (size!=1){ // 資料有多筆
            for(int i=0; i<(size-2) ;i++){  // 遍歷linked list
                nowNode = nowNode -> next;
            }
            deledNode = nowNode->next; // 找到待查資料
            nowNode->next = nullptr; // 取消資料連結
        }else{ // 當資料只有一筆
            deledNode = top; // 找出待查資料
            top=nullptr; // 取消資料連結
        }
        char ans = deledNode->data; // 取出資料
        delete deledNode; // 刪除Node
        size--; // 資料減一
        return ans;
    }

    // Peek 操作：取得頂端元素但不移除
    char peek() {
        if (isEmpty()){ // 報錯：linked list 為空
            cout<<"Linked List is empty"<<endl;
            return '\0';
        }
        Node *nowNode = top; // 找到目標資料
        for (int i = 0;i < size-1;i++){
            nowNode = nowNode->next;
        }
        return nowNode->data; // 回傳資料
    }

    // 判斷堆疊是否為空
    bool isEmpty() {
        return (size==0);
    }
};

// 判斷運算子(加減乘除) 的優先順序
int precedence(char op) {
    if ((op>='0' && op<='9')||(op>='A' && op<='Z')||op=='.'){  // 純數字權限最小，ASCII辨識
        return 5;
    }else if (op=='('){ // 左括號 權限第2小
        return 4;
    }else if (op=='+' || op=='-'){ // 加、減號 權限第3小
        return 3;
    }else if (op=='*' || op=='/' || op=='%'){ // 乘、除號 權限第4小
        return 2;
    }else if (op=='^'){ // 指數權限最大
        return 1;
    }else if(op==')'){ // 右括號 權限最大
        return 0;
    }else{ // 不合法符號
        return -1;
    }
}

// 將中序表達式 (infix) 轉換為後序表達式 (postfix)
void InfixToPostfix(const char* infix, char* postfix) {
    Stack stack;
    char back;
    int infixIndex =0,postIndex=0;
    bool expectUnary = true; //判斷是一元的正、負號還是二元加、減號
    while (infix[infixIndex]!='\0'){
        switch (precedence(infix[infixIndex])){
            case 5: // 一般數字，用空格區分不同數字
                postfix[postIndex++]=' ';
                while(precedence(infix[infixIndex])==5){
                    postfix[postIndex++]=infix[infixIndex++];
                }
                postfix[postIndex++]=' ';
                infixIndex--;
                expectUnary = false; // 前方有數字，確定為二元
                break;
            case 4: // 左括號 '('
                stack.push(infix[infixIndex]);
                expectUnary = true;
                break;
            case 3: // 加減 '+' '-'
                if (expectUnary){
                    postfix[postIndex++]=' ';
                    postfix[postIndex++]='0';
                    postfix[postIndex++]=' ';
                    stack.push(infix[infixIndex]);
                }else{
                    while (!stack.isEmpty()){ 
                        back= stack.peek();  //抓出最上面一筆
                        if (precedence(back)<=3){ // 如果權限比較大就取出來放
                            postfix[postIndex++]= stack.pop();
                        }else break; // 沒有的話，結束判斷權級
                    }
                    stack.push(infix[infixIndex]); //推入本次結果
                }
                expectUnary = true;
                break;
            case 2: // 乘除 '*' '/' '%'
                while (!stack.isEmpty()){ 
                    back= stack.peek();  //抓出最上面一筆
                    if (precedence(back)<=2){ // 如果權限比較大就取出來放
                        postfix[postIndex++]= stack.pop();
                    }else break; // 沒有的話，結束判斷權級
                }
                expectUnary = true;
                stack.push(infix[infixIndex]); //推入本次結果
                break;
                
            case 1:  // 指數 '^'
                // 右結合性處理，先檢查堆疊頂端是否也是 '^'
                while (!stack.isEmpty() && precedence(stack.peek()) == 1) {
                    postfix[postIndex++] = stack.pop();
                }
                stack.push(infix[infixIndex]);
                expectUnary = true;
                break;
            case 0: // 右括號 ')'
                back = stack.pop();
                while (precedence(back)!=4){ //撈資料撈到左括號(4)為止
                    postfix[postIndex++]=back;
                    back=stack.pop();
                }
                expectUnary = false; //表達式完成，經計算後會變成一個數字
                break;
            default:
                break;
        }
        infixIndex++; //處理下一個資料
    }
    while (!stack.isEmpty()){ // 判斷完成取完剩餘資料
        char back=stack.pop();
        postfix[postIndex++]=back;
    }
    postfix[postIndex++]='\0'; //下入終止符號
}

double calculator(char* postfix){
    stack<double> NumStack;
    int index=0;
    while (postfix[index]!='\0'){
        if (postfix[index]==' '){ // 當遇到空格時，跳過
            index++;
            continue;
        }
        if (precedence(postfix[index])==5){ // 當遇到數字時，將其轉換為 double 並放入堆疊
            char tmp[10];int t_index=0;
            while (precedence(postfix[index])==5)tmp[t_index++]=postfix[index++]; // 讀入多位數字
            tmp[t_index++]='\0'; // 加入結束符號
            double num = atof(tmp);
            NumStack.push(num);
        }else{
            double Num1 = NumStack.top(); // 取出堆疊頂端的數字
            NumStack.pop();
            double Num2 = NumStack.top(); // 取出堆疊第二個數字
            NumStack.pop();
            switch (postfix[index]){ // 根據運算子進行計算
                case '+': NumStack.push(Num2+Num1);break;
                case '-': NumStack.push(Num2-Num1);break;
                case '*': NumStack.push(Num2*Num1);break;
                case '/': NumStack.push(Num2/Num1);break;
                case '%': NumStack.push((int)Num2%(int)Num1);break; // 取餘數
                case '^': NumStack.push(pow(Num2,Num1));break; // 指數運算
                default: break;
            }
        }
        index++;
    }
    return NumStack.top();
}
int main() {
    char infix[100], postfix[100];
    cout << "Enter an Infix expression: ";
    cin.getline(infix, 100); // 輸入中序表達式

    InfixToPostfix(infix, postfix); // 轉換為後序表達式
    cout << "Postfix expression: " << postfix << endl; // 輸出後序表達式
    cout << "ans:"<<calculator(postfix)<<endl;
    return 0;
}
// chatgpt url:https://chatgpt.com/share/680e0256-9060-8010-a59b-c43f7040ab52
