#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

struct Player { // 玩家結構體，包括姓名和分數
    string name; // 玩家姓名
    int score; // 玩家分數
};

class Card { // 創建一張卡牌類，代表一張撲克牌
public:
    string suit; // 花色
    string rank; // 點數
    Card() {}
    Card(string s, string r) : suit(s), rank(r) {}
    void display() const {
        cout << rank << " of " << suit << endl;
    }
};

class Deck { // 撲克牌類，負責生成和洗牌
private:
    Card cards[52]; // 52張牌
    int index; // 當前發牌索引
public:
    Deck() : index(0) { // 初始化撲克牌
        string suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" }; // 四種花色
        string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" }; // 13個點數
        int k = 0;
        for (int i = 0; i < 4; i++) { // 四種花色
            for (int j = 0; j < 13; j++) { // 13個點數
                cards[k] = Card(suits[i], ranks[j]);
                k++;
            }
        }
    }
    void shuffleDeck() { // 洗牌
        srand(time(0));
        for (int i = 51; i > 0; i--) { // 從最後一張牌開始遍歷
            int j = rand() % (i + 1); // 生成一個隨機索引j
            swap(cards[i], cards[j]); // 交換兩張牌
        }
    }
    // 獲取指定位置的牌
    Card getCard(int i) const {
        return cards[i];
    }
};

// 隊列類
class Queue {
private:
    vector<Card> deck; // 存儲牌的容器
    int Front; // 指向隊列的前端
    int Rear; // 指向隊列的尾端
    int capacity; // 容器的最大容量
public:
    // 構造函數
    Queue(int size) : Front(-1), Rear(-1), capacity(size) {}

    // 將元素插入隊列的尾部
    void enqueue(Card card) {
        // 提示：檢查隊列是否已滿，滿了就打印消息；否則，將卡片插入隊列（使用 push_back），並移動 Rear 指針
        if(isFull()) { // 檢查隊列是否已滿
            cout << "Oops! 隊列已滿!" << endl;
        }
        else {
            deck.push_back(card); // 插入卡片
            Rear++; // 移動到尾端
        }
    }

    // 移除隊列的前端元素
    void dequeue() {
        // 提示：檢查隊列是否為空，如果為空打印消息；如果不為空，移動 Front 指針
        // 如果 Front 等於 Rear，重置 Front 和 Rear，並清空隊列（使用 clear 函數）
        if(isEmpty()) { // 檢查隊列是否為空
          cout << "Oops! 隊列為空!" << endl;
        }
        else {
          Front++; // 移除前端元素
        }

        if(Front == Rear) { // 檢查移除元素後隊列是否為空，如果是則重置 Front 和 Rear
            Front = -1;
            Rear = -1;
        }
    }

    Card front() { // 獲取隊列的前端元素
        if (isEmpty()) { // 檢查隊列是否為空
            cout << "隊列為空，無法獲取前端卡片!" << endl;
            return Card("", "");
        }
        return deck[Front];
    }

    bool isEmpty() const { // 檢查隊列是否為空
        // 提示：前端和尾端的關係，檢查兩種情況（使用 &&）
        return Front == -1 && Rear == -1;
    }

    bool isFull() const { // 檢查隊列是否已滿
        // 提示：檢查 deck 的大小和容量
        if(Rear == capacity) { // 如果 Rear 等於容量，隊列已滿
            cout <<"隊列已滿! " << endl;
            return true;
        }
        else {
            return false;
        }
    }
};

void initializeDeck(Queue& cardDeck) { // 初始化並洗牌
    Deck deck;
    cout << "初始牌堆: \n";
    for (int i = 0; i < 52; i++) {
        deck.getCard(i).display(); // 打印原始牌堆
    }
    deck.shuffleDeck(); // 洗牌
    cout << "\n洗牌後的牌堆: \n";
    for (int i = 0; i < 52; i++) {
        deck.getCard(i).display(); // 打印洗牌後的牌堆
    }
    // 提示：將洗好的牌放入牌堆中
    // 使用循環將洗牌後的牌（deck.getCard(i)）放入隊列
    for(int i=0; i<52; i++) {
        cardDeck.enqueue(deck.getCard(i)); // 使用 enqueue 函數將每張卡片放入隊列
    }
}

void initializePlayer(Player* player, string name, Queue& cardDeck) { // 初始化玩家並發兩張卡
    player->name = name; // 玩家姓名
    player->score = 0; // 玩家分數
    cout << player->name << " 抽到的卡牌: ";
    for (int i = 0; i < 2; i++) { // 發兩張卡
        // 提示：從牌堆中抽一張卡，然後移除這張卡
        // 注意：卡片的變數類型是 Card，並且使用 front 來抽卡
        Card drawnCard = cardDeck.front(); // 用於儲存抽到的卡片
        cardDeck.dequeue(); // 移除抽到的卡片

        // 打印抽到的卡片
        drawnCard.display();

        cout << drawnCard.rank << " of " << drawnCard.suit << " ";
        if (drawnCard.rank == "A") player->score += 1; // 計算 Ace 的分數
        else if (drawnCard.rank == "J" || drawnCard.rank == "Q" || drawnCard.rank == "K")
            player->score += 10; // 計算 J、Q、K 的分數
        else
            player->score += stoi(drawnCard.rank); // 計算 2-10 的分數
    }
    cout << "\n";
    cout << player->name << " 的初始分數: " << player->score << endl; // 打印玩家的初始分數
}

void playerTurn(Player* player, Queue& cardDeck) { // 玩家回合
    char choice;
    while (player->score < 21 && !cardDeck.isEmpty()) { // 玩家分數小於 21 且牌堆不為空
        cout << player->name << " 目前分數: " << player->score
             << " 你要抽卡嗎? (h = 抽卡, s = 停止): "; // 顯示選項
        cin >> choice; // 輸入選擇
        if (choice == 'h') { // 如果玩家選擇抽卡
            // 提示：從牌堆中抽一張卡，然後移除這張卡
            // 注意：卡片的變數類型是 Card，並且使用 front 來抽卡
            Card newCard = cardDeck.front(); // 用來儲存抽到的卡片
            cardDeck.dequeue(); // 移除抽到的卡片

            if (newCard.rank == "A") player->score += 1; // 計算 Ace 的分數
            else if (newCard.rank == "J" || newCard.rank == "Q" || newCard.rank == "K")
                player->score += 10; // 計算 J、Q、K 的分數
            else
                player->score += stoi(newCard.rank); // 計算 2-10 的分數
            // 打印抽到的卡片和總分數
            cout << player->name << " 抽到了: " << newCard.rank << " of "
                 << newCard.suit << " 總分: " << player->score << endl;
            if (player->score > 21) { // 如果玩家分數超過 21
                cout << player->name << " 爆掉了! 遊戲結束。\n"; // 玩家爆掉，莊家贏
                return;
            }
        }
        else if (choice == 's') { // 如果玩家選擇停止
            cout << player->name << " 選擇停止，總分: " << player->score << endl; // 打印總分
            break;
        }
        else {
            cout << "請輸入有效的選項 (h = 抽卡, s = 停止)!" << endl; // 無效輸入
        }
    }
}

void dealerTurn(Player* dealer, Queue& cardDeck) { // 莊家回合
    while (dealer->score < 17 && !cardDeck.isEmpty()) { // 莊家分數小於 17 且牌堆不為空
        // 提示：從牌堆中抽一張卡，然後移除這張卡
        // 注意：卡片的變數類型是 Card，並且使用 front 來抽卡
        Card newCard = cardDeck.front(); // 用來儲存抽到的卡片
        cardDeck.dequeue(); // 移除它

        if (newCard.rank == "A") dealer->score += 1; // 計算 Ace 的分數
        else if (newCard.rank == "J" || newCard.rank == "Q" || newCard.rank == "K")
            dealer->score += 10; // 計算 J、Q、K 的分數
        else
            dealer->score += stoi(newCard.rank); // 計算 2-10 的分數
        // 打印抽到的卡片和總分數
        cout << "莊家抽到了: " << newCard.rank << " of " << newCard.suit
             << " 莊家當前總分: " << dealer->score << endl;
        if (dealer->score > 21) { // 如果莊家分數超過 21
            cout << "莊家爆掉了! 玩家獲勝!" << endl; // 玩家獲勝
            return;
        }
    }
}

// 決定獲勝者
void determineWinner(Player* player, Player* dealer) {
    if (player->score > 21) cout << player->name << " 爆掉了! 莊家獲勝!\n"; // 玩家爆掉，莊家獲勝
    else if (dealer->score > 21 || player->score > dealer->score)
        cout << player->name << " 獲勝!\n"; // 莊家爆掉或玩家分數較高，玩家獲勝
    else if (player->score == dealer->score) cout << "平手!\n"; // 莊家和玩家分數相同，平手
    else cout << "莊家獲勝!\n"; // 莊家分數較高，莊家獲勝
}

int main() {
    srand(time(0));
    Queue cardDeck(52); // 宣告牌堆
    initializeDeck(cardDeck); // 初始化牌堆
    Player player, dealer; // 宣告並初始化玩家和莊家
    initializePlayer(&player, "玩家", cardDeck);
    initializePlayer(&dealer, "莊家", cardDeck);
    playerTurn(&player, cardDeck);
    if (player.score <= 21) {
        cout << "\n莊家回合...\n";
        dealerTurn(&dealer, cardDeck);
        determineWinner(&player, &dealer);
    }
    return 0;
}
