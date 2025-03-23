#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Player { /* Player structure data type, includes a string type player name and an int type player score */
    string name;
    int score;
};

struct dealer { /* Dealer structure data type, includes an int type dealer score */
    string name;
    int score;
};

int drawCard() {
    return rand() % 10 + 1; /* Drawing a card function, each call draws a card with a value between 1 and 10 */
}

// Initialize player
void initializePlayer(Player* player, string name) {
   player->name = name; 
   player->score = drawCard() + drawCard(); /* Using the structure variable above, initialize the player and simultaneously draw two initial cards */
}
// Display player score
void displayScore(Player* player) {
   cout << player->name <<" Score: " << player->score << endl;  /* Display the player's current hand value */
}
// Player's turn
void playerTurn(Player* player) {
    char choice;
    while (player->score < 21) {
        cout << "Do you want to draw a card? (h = draw, s = stop) : ";
        cin >> choice;
        if (choice == 'h') {
            int newCard = drawCard() ; // Prompt for drawing a card; declare a variable and call the draw card function
            player->score += newCard ;  /* Add the value of the newly drawn card to the player's current score and display the total score */
             cout << player->name << " drew " << " points, current total: " << player->score << endl;
            if (player->score > 21) {
                cout << player->name << " busted! Game over.\n";
                return;
            }
        }
        else if (choice == 's') {
            break;
        }
    }
}
// Dealer's turn
void dealerTurn(Player* dealer) {
    while (dealer->score < 17) { // The dealer must draw until reaching at least 17
        int newCard = drawCard(); // Prompt for drawing a card; declare a variable and call the draw card function
        dealer->score += newCard; /* If the dealer's score is less than 17, continue to draw cards until the dealer's score is at least 17, then print the dealer's score */
        cout << "Dealer drew " << newCard << " points, current total: " << dealer->score << endl;
        if (dealer->score > 21) { // If the dealer exceeds 21 points
            cout << "Dealer busted! Player wins!" << endl;
            return; // Game over
        }
    }
}
// Determine the winner
void determineWinner(Player* player, Player* dealer) {
    if (player->score > 21) {
        cout << "You busted! Dealer wins!\n";
    }
    else if (dealer->score > 21 || player->score > dealer->score) {
        cout << "You win!\n";
    }
    else if (player->score == dealer->score) {
        cout << "It's a tie!\n";
    }
    else {
        cout << "Dealer wins!\n";
    }
}

// Main program
int main() {
    srand(time(0));

    Player player, dealer;
    initializePlayer(&player, "Player");
    initializePlayer(&dealer, "Dealer");

    displayScore(&player);
    playerTurn(&player);

    if (player.score <= 21) { // Only let the dealer play if the player has not busted
        cout << "\nDealer's turn...\n";
        displayScore(&dealer);
        dealerTurn(&dealer);
        determineWinner(&player, &dealer);
    }

    return 0;
}
