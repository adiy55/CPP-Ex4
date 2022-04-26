//
// Created by adiya on 4/25/2022.
//

#ifndef CPP_EX4_PLAYER_HPP
#define CPP_EX4_PLAYER_HPP

#include <string>
#include "Game.hpp"

namespace coup {

    class Player {

    protected:
        Game _game;
        std::string _name;
        int _coins;

        Player(Game& game, const std::string& name);

    public:

        void income(); // -1 coin

        void foreign_aid(); // -2 coins

        void coup(Player& player); // -7 coins

        virtual std::string role() = 0;

        int coins();

    };

}


#endif //CPP_EX4_PLAYER_HPP
