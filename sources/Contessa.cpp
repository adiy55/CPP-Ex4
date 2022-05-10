#include "Contessa.hpp"

using namespace constants;

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