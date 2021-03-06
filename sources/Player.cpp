#include <stdexcept>
#include "Player.hpp"
#include "Game.hpp"

using namespace constants;

typedef std::unordered_map<int, std::function<void()>> func_map;

namespace coup {

    Player::Player(Game &game, const std::string &name)
            : _game{game}, _name{name}, _coins{0}, _is_in_game{false} {
        _game.insertPlayer(*this);
        _is_in_game = true; // update only after successful insertion
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
        this->validatePlayersInGame({player});
        int cost = this->coupCheckBalance();
        this->updateCoins(-cost);
        player._is_in_game = false;
        return _game.removePlayer(player); // return player index for recovery (in Assassin)
    }

    /**
     * Function checks for a valid executable function and reverses an action.
     * @param p reference to player that is blocked
     * @param action enum from Constants.hpp
     */
    void Player::blockAction(Player &p, int action) {
        this->validatePlayersInGame({p});
        if (this == &p) { throw std::invalid_argument{"Can not block yourself!"}; }
        func_map &executables = p.getExecutables();
        if (executables.count(action) != 1) { throw std::invalid_argument{"No action to remove!"}; }
        executables[action]();
        executables.erase(action);
    }

    /**
     * Wrapper function for validation before executing the function and incrementing the turn after.
     * @param func method the player called
     */
    void Player::turnWrapper(const std::function<void()> &func) {
        this->checkInGame();
        if (_name != _game.turn()) { throw std::runtime_error{"Not your turn!"}; }
        if (!_executables.empty()) { _executables = {}; }
        func();
        _game.incrementTurn();
    }

    /**
     * @param players initializer list
     */
    void Player::validatePlayersInGame(std::initializer_list<std::reference_wrapper<Player>> players) const {
        for (const Player &p: players) {
            if (&p._game != &_game) { throw std::runtime_error{"Players are from different games!"}; }
            p.checkInGame();
        }
    }

    void Player::checkCoupNecessary() const {
        if (_coins > MAX_COINS_COUP) { throw std::runtime_error{"Player has to coup! Has 10 or more coins!"}; }
    }

    int Player::coupCheckBalance() const {
        int cost = this->getCoupPrice(); // call virtual function
        if (_coins < cost) { throw std::logic_error{"Not enough coins for coup!"}; }
        return cost;
    }

    int Player::getCoupPrice() const {
        return REGULAR_COUP_PRICE;
    }

    void Player::checkPositiveBalance() const {
        if (_coins <= MIN_COINS) { throw std::logic_error{"Not enough coins!"}; }
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

    void Player::checkInGame() const {
        if (!_is_in_game) { throw std::runtime_error{"Player is not in the game!"}; }
    }

    void Player::setInGame() {
        _is_in_game = true;
    }

}