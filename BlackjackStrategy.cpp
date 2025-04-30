#include "BlackjackStrategy.h"
#include <algorithm> // to convert characters to uppercase

BlackjackStrategy::BlackjackStrategy() : hiLoCount(0) {}

bool BlackjackStrategy::isFaceCard(const std::string& card) {
    // defining if a car isFaceCard depending on symbol from main file eventually
    return (card == "T" || card == "J" || card == "Q" || card == "K" || card == "A");
}

bool BlackjackStrategy::isLowCard(const std::string& card) {

    return (card == "2" || card == "3" || card == "4" || card == "5" || card == "6");
}

int BlackjackStrategy::cardValue(const std::string& card) {
    if (card == "A") {
        return 11; // 11 if Ace
    }
    if (isFaceCard(card)) {
        return 10; // 10 if faceCard
    }


    return std::stoi(card); // value of card if none of the above
}

void BlackjackStrategy::countCard(const std::string& card) {
    if (isFaceCard(card)) {
        hiLoCount--; // 7-9 is do nothing in carcCOunting
    } else if (isLowCard(card)) { // any card below 6
        hiLoCount++;
    }
}

void BlackjackStrategy::countCards(const std::vector<std::string>& hand) {
    for (const auto& card : hand) {

        countCard(card);

    }
}

int BlackjackStrategy::calculateBet(int currentBet) {


    if (hiLoCount > 5) {
        return currentBet * 2;

    } 
    else if (hiLoCount < -5) {
        return currentBet / 2;
    }

    return currentBet;
}

