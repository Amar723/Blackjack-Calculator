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

bool BlackjackStrategy::shouldSplit(const std::vector<std::string>& dealerHand, const std::vector<std::string>& playerHand) {
    if (playerHand.size() != 2 || playerHand[0] != playerHand[1]) {
        return false;

        // should not split if already split once or if card 1 and 2 are not equal
    }

    // blackjack strategy from internet regarding player vs dealer during split
    std::string card = playerHand[0];
    std::string dealerUp = dealerHand[0];

    if (card == "A" || card == "8") {
        return true;
    }

    if (card == "9") {
        if (dealerUp == "7" || isFaceCard(dealerUp)) {
            return false;
        }
        return true;
    }

    if (isLowCard(card)) {
        return true;
    }

    return false;
}

int BlackjackStrategy::calculatePoints(const std::vector<std::string>& hand) {
    int points = 0;
    int numAces = 0;

    for (const auto& card : hand) {
        if (card == "A") {
            points += 11;
            numAces++;
        } else {
            points += cardValue(card);
        }
    }

    while (points > 21 && numAces > 0) {
        points -= 10; // take the ace as a 1 if we bust with ace in our play
        numAces--;
    }

    return points;
}

std::pair<std::string, int> BlackjackStrategy::getOptimalMove(int currentBet, std::vector<std::string> dealerHand, std::vector<std::string> playerHand, bool noSplit) {
    for (auto& card : dealerHand) {
        std::transform(card.begin(), card.end(), card.begin(), ::toupper);
    }

    for (auto& card : playerHand) {
        std::transform(card.begin(), card.end(), card.begin(), ::toupper);
    }


    countCards(dealerHand);
    countCards(playerHand);

    int nextBet = calculateBet(currentBet);

    if (!noSplit && shouldSplit(dealerHand, playerHand)) {
        return {"split", nextBet};
    }

    int points = calculatePoints(playerHand);

    if (points < 17) {
        return {"hit", nextBet};
    } else if (points > 21) {
        return {"stand", nextBet};
    } else if (points == 17 && playerHand.size() == 2 && 
               (playerHand[0] == "A" || playerHand[1] == "A")) {
        return {"double", nextBet};
    }

    return {"stand", nextBet};
}
