#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

// 表示單張撲克牌的類別
class Card {
public:
    string colors; //儲存撲克牌的花色
    string rank; //儲存撲克牌的數值
    Card(string s, string r) : colors(s), rank(r) {} //建立constructor來初始化物件，當Card物件建立時，它會自動執行這個函式，並把s和r的值存入colors和rank
    void display() const { //顯示撲克牌的資訊
        cout << rank << " of " << colors << endl;
    }
};

// 實作Stack
class Stack {
private:
    vector<Card> stack; //表示stack是一個能存放Card類別物件的vector

public:
    void push(const Card& card) {
        if(stack.size()==52) {
          cout << "Stack is full!" << endl;
          return;
        }
        else{
        stack.push_back(card);
       }
    }

    Card pop() {
        if (stack.empty()) {
                cout << "Stack is empty!" << endl;
                return Card("None", "None");
        } else {
               Card lastCard = stack.back();  // Get the top card
               stack.pop_back();  // Remove the top card from the stack
               return lastCard;  // Return the top card
           }
       }


    bool isEmpty() const {
        if(stack.empty()) {
            return true;
        }
    }
};

// 代表一副撲克牌的類別
class Deck {
private:
    vector<Card> cards; // 存放未洗牌的撲克牌
    Stack shuffledDeck; // 存放洗過的牌，用實作的stack來管理
public:
    Deck() { //建立constructor來初始化物件
        string colors[] = { "Hearts", "Diamonds", "Clubs", "Spades" }; //儲存撲克牌的花色
        string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" }; //儲存撲克牌的數值

        //利用迴圈將52張牌加入cards這個vector裡面
        for (int i = 0; i < 4; i++) { // 四種花色
            for (int j = 0; j < 13; j++) { // 13 種點數
                cards.push_back(Card(colors[i], ranks[j]));
            }
        }
    }

    //洗牌(Hint:使用shuffle函數)
    void shuffleDeck() {

        srand(time(0));  // Non-deterministic random number generator
        random_shuffle(cards.begin(), cards.end());  // shuffle the cards

        // Push shuffled cards to the stack
        for (Card& num : cards) {
            shuffledDeck.push(num);
        }
    }
    //發牌
     void drawAllCards() {
        while (!shuffledDeck.isEmpty()) { // Continue while the stack is not empty
                Card c = shuffledDeck.pop();  // Pop the top card from the stack
                c.display();                   // Display the popped card
        }
     }
};

int main() {
    Deck deck; //建立deck產生52張撲克牌
    deck.shuffleDeck(); //進行洗牌並放入堆疊
    cout << "Shuffled deck:" << endl;
    deck.drawAllCards(); //依序取出堆疊內的牌並顯示
    return 0;
}
