#include "Ambassador.hpp"

namespace coup {

    Ambassador::Ambassador(Game &game, const std::string &name)
            : Player{game, name} {}

    std::string Ambassador::role() const {
        return "Ambassador";
    }

    void Ambassador::transfer(Player &from, Player &to) {}

    void Ambassador::block(Player &player) {}

}