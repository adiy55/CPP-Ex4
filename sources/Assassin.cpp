#include "Assassin.hpp"

using namespace constants;

namespace coup {

    Assassin::Assassin(Game &game, const std::string &name)
            : Player{game, name} {}

    std::string Assassin::role() const {
        return "Assassin";
    }

    int Assassin::getCoupPrice() const {
        return _coins >= REGULAR_COUP_PRICE ? REGULAR_COUP_PRICE : ASSASSIN_COUP_PRICE;
    }

    void Assassin::coup(Player &player) {
        if (this->getCoupPrice() == REGULAR_COUP_PRICE) {
            this->turnWrapper([this, &player] {
                this->basicCoup(player);
            });
        } else { // coup with 3 coins
            this->turnWrapper([this, &player] {
                uint player_index = this->basicCoup(player);
                _executables[COUP_RECOVER_PLAYER] = {[this, &player, player_index] {
                    _game.insertPlayer(player, player_index);
                    player.setInGame();
                }};
            });
        }
    }

}