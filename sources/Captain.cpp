#include "Captain.hpp"

using namespace constants;

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
            int n_coins = this->validateSteal(player);
            player.updateCoins(-n_coins);
            this->updateCoins(n_coins);
            _executables[BLOCK_STEAL] = {[this, &player, n_coins] {
                player.updateCoins(n_coins);
                this->updateCoins(-n_coins);
            }};
        });
    }

    int Captain::validateSteal(Player &p) {
        this->validatePlayersInGame({p});
        if (this == &p) { throw std::invalid_argument{"Captain can not steal from himself!"}; }
        int n_coins = p.coins();
        if (n_coins > MAX_STEAL_PRICE) { n_coins = MAX_STEAL_PRICE; }
        return n_coins;
    }

}