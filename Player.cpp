//
// Created by adiya on 4/25/2022.
//

#include "Player.hpp"
#include "Game.hpp"

namespace coup {


    Player::Player(Game &game, const std::string &name)
            : _game{game}, _name{name}, _coins{0} {}

    /**
     * Take one coin.
     */
    void Player::income() {
        ++_coins;
    }

    /**
     * Take two coins.
     */
    void Player::foreign_aid() {
        _coins += 2;
    }

    void Player::coup(Player &player) {}

    /**
     * @return number of coins the player has
     */
    int Player::coins() const {
        return _coins;
    }

}
