#include "Player.hpp"
#include "Game.hpp"

namespace coup {


    Player::Player(Game &game, const std::string &name)
            : _game{game}, _name{name}, _coins{0} {}

    void Player::income() {}

    void Player::foreign_aid() {}

    void Player::coup(Player &player) {}

    int Player::coins() const { return _coins; }

}
