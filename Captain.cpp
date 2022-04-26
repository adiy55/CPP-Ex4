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

    void Captain::block(Player &player) {}

    void Captain::steal(Player &player) {}

}