//
// Created by adiya on 4/25/2022.
//

#ifndef CPP_EX4_PLAYER_HPP
#define CPP_EX4_PLAYER_HPP

#include <string>
#include "Game.hpp"

namespace coup {

    class Player {
    private:

        void coupCheckBalance() const;

    protected:

        Game &_game;
        std::string _name;
        int _coins;

        Player(Game &game, const std::string &name);

    public:

        void income();

        void foreign_aid();

        void coup(Player &player);

        virtual std::string role() const = 0;

        int coins() const;

        // helper functions

        void checkPositiveBalance() const;

        void updateBalance(int coins);

    };

}


#endif //CPP_EX4_PLAYER_HPP
