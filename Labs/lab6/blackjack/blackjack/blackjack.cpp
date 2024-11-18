#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;
/**
 need a card struct
 need a function to display the card within struct
 need function createSuit ->
 need a function to draw a card
 */

/*
 card struct needs to have pointvalue, a char to represent the face A-K, a char to represent suit
 method get display name which returns the cards attributes
 */
struct Card {
    int pointValue;
    char face;
    char suit;
    
    std::string getDisplayName(){
        std::string faceName;
        switch (face) {
            case 'A': faceName = "A"; break;
            case 'K': faceName = "K"; break;
            case 'Q': faceName = "Q"; break;
            case 'J': faceName = "J"; break;
            case 'T': faceName = "T"; break;
            default:  faceName = std::string(1, face); break;
        }
        std::string suitName;
        switch (suit) {
            case 'C': suitName = "Clubs"; break;
            case 'D': suitName = "Diamonds"; break;
            case 'H': suitName = "Hearts"; break;
            case 'S': suitName = "Spades"; break;
        }
        return faceName + " of " + suitName;
    }
};

/*
 createSuit function:
 takes a 1 char input(suit) and returns a vector of card objects
 should create all cards in a normal deck
 */
std::vector<Card> createSuit(char suit) {
    //create vector of cards to take in all of the cards of the suit
    std::vector<Card> suitCards;
    //make an array of all of the possible faces
    //make an array of all possible point values
    //arrays indexes are synced so can iterate through simultaneously to set values and faces
    char faces[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    int pointValues[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
    
    /*
     for loop iterates 13 times (13 cards per suit)
     declares a new card struct on each iteration
     loads the card face into the face attribute of the card struct
     sets the suit of the new card to the passed suit
     sets the pointvalue of the new card to the current index of pointvalues array
     pushes the new card to the suitCards vector
     */
    for(int i = 0; i < 13; i++){
        Card card;
        card.face = faces[i];
        card.suit = suit;
        card.pointValue = pointValues[i];
        suitCards.push_back(card);
    }
    return suitCards;
}

/*
 drawcard function:
 input vector of cards, pops a card from the front an returns
 */
Card drawCard(std::vector<Card>& pile){
    //check to make sure there are still cards in the pile if not throw error and exit
    if(pile.empty()){
        std::cerr << "Pile is empty" << std::endl;
        exit(EXIT_FAILURE);
    }
    //make a new card and load the front val of the vector into it
    Card drawnCard = pile.front();
    //delete the card that was taken from the pile from the pile
    pile.erase(pile.begin());
    return drawnCard;
}

/*
 function shuffle
 input, passed vector of cards returns randomized vector
 */
void shuffle(std::vector<Card>& pile){
    for(int i = 0; i < pile.size(); i++){
        /*generate a new random index each time incremeted by iterator i, swap current element to that index
        */
        int randIndex = i + rand() % (pile.size() - i);
        std::swap(pile[i], pile[randIndex]);
    }
    
}

/*
 function showPileContents:
 input, vector of cards uses member function to display each cards contents
 */
void showPileContents(std::vector<Card>& pile){
    for(int i = 0; i < pile.size(); i++){
        //for each card in the pile call the member function to see the card attributes
        std::cout << pile[i].getDisplayName() << std::endl;
    }
}

/*
 combineCardPiles:
 input: two vectors of cards, combines them into a single vector of cards and returns the vector
 */
std::vector<Card> combineCardPiles(const std::vector<Card>& pile1, const std::vector<Card>& pile2){
    //make new vector that has the first pile into it
    std::vector<Card> combinedPile = pile1;
    //incrementally load the second pile into the new combined pile
    for(int i = 0; i < pile2.size(); i++){
        combinedPile.push_back(pile2[i]);
    }
    return combinedPile;
}

/*
 function scoreHand:
 input: vector of cards, returns an integer representing the pointvalue of all of the cards combined
 for blackjack need to add extra conditional handling to switch aces between 11 to 1
 */
int scoreHand(const std::vector<Card>& hand) {
    int handTotal = 0;
    for(int i = 0; i < hand.size(); i++){
        //add to handtotal by accessing the pointvalue aspect of the card struct
        handTotal += hand[i].pointValue;
    }
    return handTotal;
}

/*
 function determineWinnder:
 input: two ints, the score of player and dealer, and a string message by reference.
 updates the string to appropriate message based on score and determines the winner via int
 for blackjack
 if playerscore is > 21 player busts instantly loses same for dealer
 if playerscore is > dealerscore player wins, vice versa dealer wins
 4 if/else if statements one else for control
 */
int determineWinner(int playerScore, int dealerScore, std::string& message){
    if(playerScore > 21){
        message = "Player busts!";
        return -1;
    }
    else if(dealerScore > 21){
        message = "Dealer busts, you win!";
        return 1;
    }
    else if(playerScore > dealerScore){
        message = "Player wins!";
        return 1;
    }
    else if(playerScore < dealerScore){
        message = "Dealer wins!";
        return -1;
    }
    else {
        message = "its a tie!";
        return 0;
    }
}

/*
 main function for gameplay, should output:
 Let's play BlackJack!
 The rules are simple! It's you versus the dealer.
 You and the dealer start with two cards, and each of you has an opportunity to draw cards. The winner is the one that gets closer to 21 without going over
 Good Luck!
 There are 48 cards remaining in the deck.
 The Dealer is showing a: 2 of Diamonds
 You currently have the following cards:
 5 of Spades
 4 of Diamonds
 What would you like to do?
 [H]it - Draw another card
 ISltand - Lock-in your hand
 H
 There are 47 cards remaining in the deck.
 The Dealer is showing a: 2 of Diamonds
 You currently have the following cards:
 5 of Spades
 4 of Diamonds
 A of Clubs
 What would you like to do?
 [H]it - Draw another card [S]tand - Lock-in your hand
 S
 The dealer ended with the following cards:
 2 of Diamonds
 7 of Diamonds
 K of Clubs
 You got 20
 Dealer got 19
 You win!
 Congrats!
 */
int main() {
    //seed random number for shuffle
    srand(time(NULL));
    
    //first print welcome message
    // Print initial messages
    std::cout << "Let's play BlackJack!" << std::endl;
    std::cout << std::endl << "The rules are simple! It's you versus the dealer." << std::endl;
    std::cout << "You and the dealer start with two cards, and each of you has an opportunity to draw cards. The winner is the one that gets closer to 21 without going over" << std::endl;
    std::cout << std::endl << "Good Luck!" << std::endl;
    
    //first create the entire deck (4 calls to createSuit) and use combineCardPiles to add them all to the deck
    std::vector<Card> deck;
    deck = combineCardPiles(deck, createSuit('C'));
    deck = combineCardPiles(deck, createSuit('H'));
    deck = combineCardPiles(deck, createSuit('D'));
    deck = combineCardPiles(deck, createSuit('S'));
    
    //now shuffle the deck
    shuffle(deck);
    
    //make two different hands one for player, one for dealer
    std::vector<Card> playerHand;
    std::vector<Card> dealerHand;
    
    //now each hand gets two cards
    playerHand.push_back(drawCard(deck));
    dealerHand.push_back(drawCard(deck));
    playerHand.push_back(drawCard(deck));
    dealerHand.push_back(drawCard(deck));
    
    //now for gameplay
    //player goes first, going to use a while loop and break out when player does not want to hit
    bool playerTurn = true;
    while(playerTurn){
        //first print out remaining cards in the deck
        std::cout << std::endl << "There are " << deck.size() << " cards remaining in the deck." << std::endl;
        
        //show the dealer's card
        std::cout << std::endl << "The Dealer is showing a: " << dealerHand.front().getDisplayName() << std::endl;
        
        //show the player their current hand
        std::cout << "You currently have the following cards:" << std::endl;
        showPileContents(playerHand);
        
        //give the player the option to either hit or stand
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "[H]it - Draw another card" << std::endl;
        std::cout << "[S]tand - Lock-in your hand" << std::endl;
        char choice;
        std::cin >> choice;
        
        //handle invalid input, while choice does not equal an accepted input keep prompting player for valid input
        while((choice != 'H') && (choice != 'h') && (choice != 'S') && (choice != 's')){
            std::cout << "Invalid input please try again" << std::endl;
            std::cout << "What would you like to do?" << std::endl;
            std::cout << "[H]it - Draw another card" << std::endl;
            std::cout << "[S]tand - Lock-in your hand" << std::endl;
            char choice;
            std::cin >> choice;
        }
        
        //now handle valid choices
        //if player wants to hit, add another card to their hand
        if (choice == 'H' || choice == 'h') {
            playerHand.push_back(drawCard(deck));
            int playerScore = scoreHand(playerHand);
            //score hand and check to make sure player didnt bust
            //if player busts break out of while loop game is over
            if(playerScore > 21) playerTurn = false;
        }
        //if player chooses stand move down through the gameplay
        else if(choice == 'S' || choice == 's') playerTurn = false;
    }
    //now its the dealers turn
    int dealerScore = scoreHand(dealerHand);
    //simple logic for dealer redraw
    while(dealerScore < 17) {
        dealerHand.push_back(drawCard(deck));
        dealerScore = scoreHand(dealerHand);
    }
    
    //now calculate the finals
    int playerScore = scoreHand(playerHand);
    
    //now game end sequence
    std::string resultMessage;
    int winner = determineWinner(playerScore, dealerScore, resultMessage);
    
    //display endgame per project requirements
    //show dealer final hand
    std::cout << std::endl << "The dealer ended with the following cards:" << std::endl;
    showPileContents(dealerHand);
    
    std::cout << "You got " << playerScore << std::endl;
    std::cout << "Dealer got " << dealerScore << std::endl;
    
    std::cout << resultMessage << std::endl;
    //decide winner
    if(winner == 1) {
        std::cout << "Congrats!" << std::endl;
    }
    else if(winner == -1) {
        std::cout << "Better luck next time!" << std::endl;
    }
    return 0;
}
