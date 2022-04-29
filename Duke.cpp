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
        this->runExecutables();
        func_map &executables = player.getExecutables();
        for (auto &[key, value]: executables) {
            if (key == FOREIGN_AID) {
                executables.erase(key);
            }
        }
        player.updateCoins(-2);
    }

    /**
     * Take 3 coins.
     */
    void Duke::tax() {
        this->runExecutables();
        this->updateCoins(3);
    }

}

