#include "Assassin.hpp"

namespace coup {

    Assassin::Assassin(Game &game, const std::string &name)
            : Player{game, name} {}

    std::string Assassin::role() const {
        return "Assassin";
    }

    int Assassin::getCoupPrice() const {
        return _coins >= _regular_coup_price ? _regular_coup_price : _assassin_coup_price;
    }

    void Assassin::coup(Player &player) {
        if (this->getCoupPrice() == _regular_coup_price) {
            this->turnWrapper([this, &player] {
                this->basicCoup(player);
            });
        } else {
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