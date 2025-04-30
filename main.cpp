#include <iostream>
#include "BlackjackStrategy.h"

int main() {
    BlackjackStrategy strategy;

    
    std::vector<std::string> dealer = {"6"};
    std::vector<std::string> player = {"A", "6"};


    int currentBet = 100;

    auto result = strategy.getOptimalMove(currentBet, dealer, player);
    std::cout << "Move: " << result.first << ", Next Bet: " << result.second << std::endl;

    return 0;

}