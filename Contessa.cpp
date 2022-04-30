//
// Created by adiya on 4/25/2022.
//

#include "Contessa.hpp"

namespace coup {

    Contessa::Contessa(Game &game, const std::string &name)
            : Player{game, name} {}

    std::string Contessa::role() const {
        return "Contessa";
    }

    void Contessa::block(Player &player) {
        this->blockAction(player, COUP_RECOVER_PLAYER);
    }

}