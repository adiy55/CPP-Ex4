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

