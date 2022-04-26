//
// Created by adiya on 4/25/2022.
//

#ifndef CPP_EX4_GAME_HPP
#define CPP_EX4_GAME_HPP

#include <vector>
#include <string>

namespace coup {

    class Game {

    private:

        std::vector<std::string> _players;

    public:

        Game();

        std::string turn();

        std::vector<std::string> players();

        std::string winner();

        // helper functions

        void insertPlayer(const std::string& name);

    };

}

#endif //CPP_EX4_GAME_HPP
