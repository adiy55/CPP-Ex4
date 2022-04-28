//
// Created by adiya on 4/25/2022.
//

#include <stdexcept>
#include "Game.hpp"

namespace coup {

    Game::Game()
            : _players{}, _player_idx{0} {}

    std::string Game::turn() {
        if (_players.size() == _player_idx) {
            _player_idx = 0;
        }
        Player &p = _players[_player_idx++];
        return p.role();
    }

    std::vector<std::string> Game::players() {
        std::vector<std::string> names;
        std::for_each(_players.begin(), _players.end(), [&names](Player &p) { names.push_back(p.getName()); });
        return names;
    }

    std::string Game::winner() {
        Game::checkWinner();
        Player &p = _players[0];
        return p.getName();
    }

    // helper functions

    void Game::insertPlayer(Player &p) {
        _players.emplace_back(p); // emplace back constructs an object into the vector container
        // in this case the object is: std::reference_wrapper<Player>
    }

    void Game::checkWinner() const {
        if (_players.size() > 1) {
            throw std::range_error{"The game has not ended!"};
        }
        if (_players.empty()) {
            throw std::length_error{"There are no players in the game!"};
        }
    }

}