//
// Created by adiya on 4/25/2022.
//

#include <stdexcept>
#include "Player.hpp"
#include "Game.hpp"

typedef std::unordered_map<int, std::function<void()>> func_map;

namespace coup {

    Player::Player(Game &game, const std::string &name)
            : _game{game}, _name{name}, _coins{0}, _executables{} {
        _game.insertPlayer(*this);
    }

    /**
     * Take one coin.
     */
    void Player::income() {
        this->setupTurn();
        this->updateCoins(1);
    }

    /**
     * Take two coins.
     */
    void Player::foreign_aid() {
        this->setupTurn();
        this->updateCoins(2);
        _executables[FOREIGN_AID_BLOCK] = {[this] { updateCoins(-2); }};
    }

    /**
     * Eliminate opponent from game.
     * @param player
     */
    void Player::coup(Player &player) {
        this->setupTurn();
        int cost = this->coupCheckBalance();
        this->updateCoins(-cost);
        int player_index = _game.removePlayer(player); // todo: check -1?
        _game.removePlayer(player);
        _executables[COUP_RECOVER] = {[&player, player_index] {
            player._game.insertPlayer(player, player_index);
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

    void Player::blockAction(Player &p, int action) {
        bool removed = false;
        func_map executables = p.getExecutables();
        for (auto &[key, value]: executables) {
            if (key == action) {
                executables.erase(key);
                removed = true;
            }
        }
        if (!removed) {
            throw std::logic_error{"No action to remove!"};
        }
    }

    void Player::setupTurn() {
        if (_name != _game.turn()) {
            if (_game.turn() != _name) { throw std::runtime_error{"Not your turn!"}; }
        }
        _executables = {};
        _game.incrementTurn();
    }

}
