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
};

#endif
