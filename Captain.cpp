#include "Captain.hpp"

namespace coup {

    Captain::Captain(Game &game, const std::string &name)
            : Player{game, name} {}

    std::string Captain::role() const {
        return "Captain";
    }

    void Captain::block(Player &player) {
        this->blockAction(player, BLOCK_STEAL);
    }

    void Captain::steal(Player &player) {
        this->turnWrapper([this, &player] {
            this->checkCoupNecessary();
            this->validateSteal(player);
            player.updateCoins(-2);
            this->updateCoins(2);
            _executables[BLOCK_STEAL] = {[this, &player] {
                player.updateCoins(2);
                this->updateCoins(-2);
            }};
        });
    }

    void Captain::validateSteal(Player &p) {
        this->validateSameGame({p});
        if (p.coins() < 2) { throw std::invalid_argument{"Not enough coins to steal from player!"}; }
        if (this == &p) { throw std::invalid_argument{"Captain can not steal from himself!"}; }
    }

}