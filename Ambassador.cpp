//
// Created by adiya on 4/25/2022.
//

#include <stdexcept>
#include "Ambassador.hpp"

namespace coup {

    Ambassador::Ambassador(Game &game, const std::string &name)
            : Player{game, name} {}

    std::string Ambassador::role() const {
        return "Ambassador";
    }

    void Ambassador::transfer(Player &from, Player &to) {
        this->setupTurn();
        from.checkPositiveBalance();
        from.updateCoins(-1);
        to.updateCoins(1);
    }

    void Ambassador::block(Player &player) {
        blockAction(player, STEAL_BLOCK);
    }

}