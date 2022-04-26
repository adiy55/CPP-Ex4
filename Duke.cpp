//
// Created by adiya on 4/25/2022.
//

#include "Duke.hpp"

namespace coup {

    Duke::Duke(Game &game, const std::string &name)
            : Player{game, name} {}

    std::string Duke::role() const {
        return "Duke";
    }

    void Duke::block(Player &player) {}

    void Duke::tax() {}

}

