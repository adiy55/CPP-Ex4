//
// Created by adiya on 4/25/2022.
//

#ifndef CPP_EX4_GAME_HPP
#define CPP_EX4_GAME_HPP

#include <vector>
#include <string>
#include <functional>
#include "Player.hpp"

typedef unsigned int uint;

namespace coup {

    class Player; // forward declaration (circular dependency)

    class Game {

    private:

        std::vector<std::reference_wrapper<Player>> _players;

        uint _player_idx;

        void checkWinner() const;

    public:

        Game();

        std::string turn();

        std::vector<std::string> players();

        std::string winner();

        // helper functions

        void insertPlayer(Player &p);

        void removePlayer(Player &p);

    };

}

#endif //CPP_EX4_GAME_HPP
