//
// Created by adiya on 4/25/2022.
//

#include <stdexcept>
#include "Game.hpp"

namespace coup {

    Game::Game()
            : _players{}, _player_idx{0}, _erased_player_idx{-1} {}

    std::string Game::turn() {
        return _players[_player_idx].get().getName();
    }

    std::vector<std::string> Game::players() {
        std::vector<std::string> names;
        std::for_each(_players.begin(), _players.end(), [&names](const Player &p) { names.push_back(p.getName()); });
        return names;
    }

    std::string Game::winner() {
        Game::checkWinner();
        return _players[0].get().getName();
    }

    // helper functions

    void Game::insertPlayer(Player &p) {
        _players.emplace_back(p); // emplace back constructs an object into the vector container
        // in this case the object is: std::reference_wrapper<Player>
    }

    void Game::insertPlayer(Player &p, int index) {
        _players.insert(_players.begin() + index, p);
    }

    void Game::checkWinner() const {
        if (_players.size() > 1) {
            throw std::range_error{"The game has not ended!"};
        }
        if (_players.empty()) {
            throw std::length_error{"There are no players in the game!"};
        }
    }

    void Game::removePlayer(Player &p) {
        bool erased = false;
        for (uint i = 0; i < _players.size(); i++) {
            if (&_players[i].get() == &p) {
                _players.erase(_players.begin() + i);
                erased = true;
                if (_player_idx - 1 > i) { // remove player before current index
                    --_player_idx;
                } else { // remove player after current index
                    _player_idx = _player_idx % _players.size();
                }
                _erased_player_idx = static_cast<int>(i);
            }
        }
        if (!erased) {
            throw std::runtime_error{"Could not find player to remove!"};
        }
    }

    void Game::incrementTurn() {
        _player_idx = ++_player_idx % _players.size();
    }

    int Game::getErasedPlayerIndex() const {
        if (_erased_player_idx < 0) {
            throw std::out_of_range{"Invalid index- out of bounds!"};
        }
        return _erased_player_idx;
    }
}