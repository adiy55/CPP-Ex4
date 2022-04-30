//
// Created by adiya on 4/25/2022.
//

#ifndef CPP_EX4_PLAYER_HPP
#define CPP_EX4_PLAYER_HPP

#include <string>
#include <vector>
#include <functional>
#include "Game.hpp"
#include "Constants.hpp"

typedef std::unordered_map<int, std::function<void()>> func_map;

namespace coup {

    class Game; // forward declaration (circular dependency)

    class Player {
    private:

        const int _regular_coup_price{7};

    protected:

        Game &_game;
        std::string _name;
        int _coins;
        func_map _executables;

        Player(Game &game, const std::string &name);

        int coupCheckBalance() const;

        virtual int getCoupPrice() const;

        static void blockAction(Player &p, int action);

    public:

        void income();

        void foreign_aid();

        virtual void coup(Player &player);

        virtual std::string role() const = 0;

        int coins() const;

        // helper functions

        std::string getName() const;

        void checkPositiveBalance() const;

        void updateCoins(int coins);

        func_map &getExecutables();

        void setupTurn();

    };

}


#endif //CPP_EX4_PLAYER_HPP
