//
// Created by adiya on 4/25/2022.
//

#include "Assassin.hpp"

namespace coup {

    Assassin::Assassin(Game &game, const std::string &name)
            : Player{game, name} {}

    std::string Assassin::role() const {
        return "Assassin";
    }

    int Assassin::getCoupPrice() const {
        return _assassin_coup_price;
    }

    void Assassin::coup(Player &player) {
        Player::coup(player);
        int player_index = _game.getErasedPlayerIndex();
        _executables[COUP_RECOVER_PLAYER] = {[this, &player, player_index] {
            _game.insertPlayer(player, player_index);
        }};
    }

}