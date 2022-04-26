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

        std::string _name;
        int _coins;

        Player(Game &game, const std::string &name);

    public:

        void income();

        void foreign_aid();

        void coup(Player &player);

        virtual std::string role() const = 0;

        int coins() const;

    };

}


#endif //CPP_EX4_PLAYER_HPP
