#include <stdexcept>
#include "Ambassador.hpp"

using namespace constants;

namespace coup {

    Ambassador::Ambassador(Game &game, const std::string &name)
            : Player{game, name} {}

    std::string Ambassador::role() const {
        return "Ambassador";
    }

    void Ambassador::transfer(Player &from, Player &to) {
        this->turnWrapper([this, &from, &to] {
            this->checkCoupNecessary();
            this->validateTransfer(from, to);
            from.checkPositiveBalance();
            from.updateCoins(-1);
            to.updateCoins(1);
        });
    }

    void Ambassador::block(Player &player) {
        blockAction(player, BLOCK_STEAL);
    }

    void Ambassador::validateTransfer(Player &from, Player &to) const {
        this->validatePlayersInGame({from, to});
        if (this == &from || &from == &to) { throw std::invalid_argument{"Invalid transfer!"}; }
    }

}