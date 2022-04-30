//
// Created by adiya on 4/25/2022.
//

#include <vector>
#include <string>
#include "Game.hpp"

namespace coup {

    Game::Game()
            : _player_idx{0} {}

    std::string Game::turn() {
        return _players.empty() ? "" : _players[0].get().role();
    }

    std::vector<std::string> Game::players() {
        return _players.empty() ? std::vector<std::string>{} : std::vector<std::string>{_players[0].get().role()};
    }

    std::string Game::winner() {
        return _players.empty() ? "" : _players[0].get().role();
    }

}