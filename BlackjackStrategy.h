#ifndef BLACKJACKSTRATEGY_H
#define BLACKJACKSTRATEGY_H

#include <vector>
#include <string>

class BlackjackStrategy {
private:
    int hiLoCount;

    bool isFaceCard(const std::string& card);
    bool isLowCard(const std::string& card);
    int cardValue(const std::string& card);
    void countCard(const std::string& card);

public:
    BlackjackStrategy();

    void countCards(const std::vector<std::string>& hand);
    int calculateBet(int currentBet);
    bool shouldSplit(const std::vector<std::string>& dealerHand, const std::vector<std::string>& playerHand);
    int calculatePoints(const std::vector<std::string>& hand);
    std::pair<std::string, int> getOptimalMove(int currentBet, std::vector<std::string> dealerHand, std::vector<std::string> playerHand, bool noSplit = false);
};

#endif
