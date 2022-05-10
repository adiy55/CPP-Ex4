#include "Duke.hpp"

using namespace constants;

namespace coup {

    Duke::Duke(Game &game, const std::string &name)
            : Player{game, name} {}

    std::string Duke::role() const {
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
        this->turnWrapper([this] {
            this->checkCoupNecessary();
            this->updateCoins(3);
        });
    }

}

