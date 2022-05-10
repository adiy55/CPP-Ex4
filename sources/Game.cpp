#include <stdexcept>
#include "Game.hpp"

using constants::MAX_PLAYERS;

namespace coup {

    Game::Game()
            : _player_idx{0}, _is_started{false} {}

    std::string Game::turn() {
        if (_players.size() <= 1) { throw std::length_error{"Not enough players in the game!"}; }
        _is_started = true;
        return _players[_player_idx].get().getName();
    }

    std::vector<std::string> Game::players() {
        std::vector<std::string> names;
        std::for_each(_players.begin(), _players.end(), [&names](const Player &p) { names.push_back(p.getName()); });
        return names;
    }

    std::string Game::winner() {
        this->checkWinner();
        return _players[0].get().getName();
    }

    // helper functions

    void Game::insertPlayer(Player &p) {
        this->checkInsert();
        if (_is_started) { throw std::runtime_error{"Game has started!"}; }
        _players.emplace_back(p); // emplace back constructs an object into the vector container
        // in this case the object is: std::reference_wrapper<Player>
    }

    void Game::insertPlayer(Player &p, uint index) {
        this->checkInsert();
        this->checkNotStarted();
        _players.insert(_players.begin() + index, p);
        if (_player_idx >= index) { ++_player_idx; }
    }

    void Game::checkWinner() const {
        if (_players.size() > 1) { throw std::range_error{"The game has not ended!"}; }
        if (_players.empty()) { throw std::length_error{"There are no players in the game!"}; }
        this->checkNotStarted();
    }

    void Game::checkNotStarted() const {
        if (!_is_started) { throw std::runtime_error{"Game has not started!"}; }
    }

    void Game::checkInsert() const {
        if (_players.size() > MAX_PLAYERS) { throw std::length_error{"Too many players in the game!"}; }
    }

    uint Game::removePlayer(Player &p) {
        for (uint i = 0; i < _players.size(); i++) {
            if (&_players[i].get() == &p) {
                _players.erase(_players.begin() + i);
                if (_player_idx > i) { // remove player before current index
                    --_player_idx;
                } else { // remove player after current index
                    _player_idx = _player_idx % _players.size();
                }
                return i;
            }
        }
        throw std::runtime_error{"Could not find player to remove!"};
    }

    void Game::incrementTurn() {
        _player_idx = ++_player_idx % _players.size();
    }

}