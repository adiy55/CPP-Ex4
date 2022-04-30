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

    public:

        Game();

        std::string turn();

        std::vector<std::string> players();

        std::string winner();


    };

}

#endif //CPP_EX4_GAME_HPP
