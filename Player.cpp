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
        this->turnWrapper([this] {
            this->checkCoupNecessary();
            this->updateCoins(1);
        });
    }

    /**
     * Take two coins.
     */
    void Player::foreign_aid() {
        this->turnWrapper([this] {
            this->checkCoupNecessary();
            this->updateCoins(2);
            _executables[BLOCK_FOREIGN_AID] = {[this] { updateCoins(-2); }};
        });
    }

    /**
     * Eliminate opponent from game.
     * @param player
     */
    void Player::coup(Player &player) {
        this->turnWrapper([this, &player] {
            this->basicCoup(player);
        });
    }

    /**
     * @return number of coins the player has
     */
    int Player::coins() const {
        return _coins;
    }

    // helper functions

    uint Player::basicCoup(Player &player) {
        int cost = this->coupCheckBalance();
        this->updateCoins(-cost);
        return _game.removePlayer(player);
    }

    void Player::blockAction(Player &p, int action) {
        if (this == &p) { throw std::invalid_argument{"Can not block yourself!"}; }
        func_map &executables = p.getExecutables();
        if (executables.count(action) != 1) { throw std::invalid_argument{"No action to remove!"}; }
        executables[action]();
        executables.erase(action);
    }

    void Player::turnWrapper(const std::function<void()> &func) {
        if (_name != _game.turn()) { throw std::runtime_error{"Not your turn!"}; }
        if (!_executables.empty()) { _executables = {}; }
        func();
        _game.incrementTurn();
    }

    void Player::checkCoupNecessary() const {
        if (_coins > 10) { throw std::runtime_error{"Player has to coup! Has 10 or more coins!"}; }
    }

    int Player::coupCheckBalance() const {
        int cost = this->getCoupPrice(); // call virtual function
        if (_coins < cost) { throw std::logic_error{"Not enough coins for coup!"}; }
        return cost;
    }

    int Player::getCoupPrice() const {
        return _regular_coup_price;
    }

    void Player::checkPositiveBalance() const {
        if (_coins < 1) { throw std::logic_error{"Not enough coins!"}; }
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

}