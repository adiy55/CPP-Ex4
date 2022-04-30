//
// Created by adiya on 4/25/2022.
//

#include <stdexcept>
#include "Player.hpp"
#include "Game.hpp"

typedef std::unordered_map<int, std::function<void()>> func_map; // todo: void?

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
        _executables[BLOCK_FOREIGN_AID] = {[this] { updateCoins(-2); }};
    }

    /**
     * Eliminate opponent from game.
     * @param player
     */
    void Player::coup(Player &player) {
        this->setupTurn();
        int cost = this->coupCheckBalance();
        this->updateCoins(-cost);
        _game.removePlayer(player);
    }

    /**
     * @return number of coins the player has
     */
    int Player::coins() const {
        return _coins;
    }

    // helper functions

    int Player::coupCheckBalance() const {
        int cost = this->getCoupPrice(); // call virtual function
        if (_coins < cost) {
            throw std::logic_error{"Not enough coins for coup!"};
        }
        return cost;
    }

    int Player::getCoupPrice() const {
        return _regular_coup_price;
    }

    void Player::checkPositiveBalance() const {
        if (_coins < 1) {
            throw std::logic_error{"Not enough coins!"};
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
        func_map &executables = p.getExecutables();
        if (executables.count(action) != 1) {
            throw std::invalid_argument{"No action to remove!"};
        }
        executables[action]();
        executables.erase(action);
    }

    void Player::setupTurn() {
        if (_name != _game.turn()) {
            if (_game.turn() != _name) { throw std::runtime_error{"Not your turn!"}; }
        }
        if (!_executables.empty()) { _executables = {}; }
        _game.incrementTurn();
    }

}