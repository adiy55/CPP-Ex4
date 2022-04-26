//
// Created by adiya on 4/25/2022.
//

#include <vector>
#include <string>
#include "Game.hpp"

namespace coup {

    Game::Game() : _players{std::vector<std::string>{}} {}

    std::string Game::turn() {
        return _players.empty() ? "" : _players[0];
    }

    std::vector<std::string> Game::players() {
        return _players;
    }

    std::string Game::winner() {
        return _players.empty() ? "" : _players[0];
    }

    // helper functions

    void Game::insertPlayer(const std::string &name) {
        _players.push_back(name); // push back creates a copy of the element
    }

}