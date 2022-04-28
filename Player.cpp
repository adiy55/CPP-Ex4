//
// Created by adiya on 4/25/2022.
//

#include <stdexcept>
#include "Player.hpp"
#include "Game.hpp"

namespace coup {

    Player::Player(Game &game, const std::string &name)
            : _game(game), _name{name}, _coins{0} {
        _game.insertPlayer(*this);
    }

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

    /**
     * Eliminate opponent from game.
     * @param player
     */
    void Player::coup(Player &player) {
        this->coupCheckBalance();
        _coins -= 7;


    }

    /**
     * @return number of coins the player has
     */
    int Player::coins() const {
        return _coins;
    }

    // helper functions

    void Player::coupCheckBalance() const {
        int balance = this->role() == "Assassin" ? 3 : 7;
        if (_coins < balance) {
            throw std::invalid_argument{"Not enough coins for coup!"};
        }
    }

    void Player::checkPositiveBalance() const {
        if (_coins < 1) {
            throw std::invalid_argument{"Not enough coins!"};
        }
    }

    void Player::updateBalance(int coins) {
        _coins += coins;
    }

    std::string Player::getName() const {
        return _name;
    }

}
