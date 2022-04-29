//
// Created by adiya on 4/25/2022.
//

#include <stdexcept>
#include "Player.hpp"
#include "Game.hpp"

typedef std::unordered_map<int, std::function<void()>> func_map;

namespace coup {

    Player::Player(Game &game, const std::string &name)
            : _game{game}, _name{name}, _coins{0}, _action{NONE}, _executables{} {
        _game.insertPlayer(*this);
    }

    /**
     * Take one coin.
     */
    void Player::income() {
        this->runExecutables();
//        _executables[INCOME] = {[this] { updateCoins(1); }};
        this->updateCoins(1);
    }

    /**
     * Take two coins.
     */
    void Player::foreign_aid() {
        this->runExecutables();
        _executables[FOREIGN_AID] = {[this] { updateCoins(2); }};
    }

    /**
     * Eliminate opponent from game.
     * @param player
     */
    void Player::coup(Player &player) {
        this->runExecutables();
        int cost = this->coupCheckBalance();
        _executables[COUP] = {[this, &player, cost] {
            _game.removePlayer(player); // todo: run executables before removing?
            this->updateCoins(-cost);
        }};
    }

    /**
     * @return number of coins the player has
     */
    int Player::coins() const {
        return _coins;
    }

    // helper functions

    int Player::coupCheckBalance() const {
        int cost = 7;
        if (_coins < cost) {
            throw std::invalid_argument{"Not enough coins for coup!"};
        }
        return cost;
    }

    void Player::checkPositiveBalance() const {
        if (_coins < 1) {
            throw std::invalid_argument{"Not enough coins!"};
        }
    }

    void Player::updateCoins(int coins) {
        _coins += coins;
    }

    std::string Player::getName() const {
        return _name;
    }

    func_map &Player::getExecutables() {
        return _executables;
    }

    void Player::runExecutables() {
        for (auto &[key, value]: _executables) {
            value();
        }
        _executables = {};
    }

}
