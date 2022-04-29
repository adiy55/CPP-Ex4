//
// Created by adiya on 4/25/2022.
//

#include "Duke.hpp"

namespace coup {

    Duke::Duke(Game &game, const std::string &name)
            : Player{game, name} {}

    std::string Duke::role() const { // virtual function
        return "Duke";
    }

    /**
     * Block foreign aid of an opponent player.
     * @param player
     */
    void Duke::block(Player &player) {
        blockAction(player, BLOCK_FOREIGN_AID);
    }

    /**
     * Take 3 coins.
     */
    void Duke::tax() {
        this->setupTurn();
        this->updateCoins(3);
    }

}

