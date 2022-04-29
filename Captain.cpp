//
// Created by adiya on 4/25/2022.
//

#include "Captain.hpp"

namespace coup {

    Captain::Captain(Game &game, const std::string &name)
            : Player{game, name} {}

    std::string Captain::role() const {
        return "Captain";
    }

    void Captain::block(Player &player) {
        blockAction(player, BLOCK_STEAL);
    }

    void Captain::steal(Player &player) {
        this->setupTurn();
        validateSteal(player);
        player.updateCoins(-2);
        this->updateCoins(2);
        _executables[BLOCK_STEAL] = {[this, &player] {
            player.updateCoins(2);
            this->updateCoins(-2);
        }};
    }

    void Captain::validateSteal(Player &p) {
        if (p.coins() < 2) {
            throw std::invalid_argument{"Not enough coins to steal from player!"};
        }
    }

}