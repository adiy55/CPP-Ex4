#ifndef CPP_EX4_PLAYER_HPP
#define CPP_EX4_PLAYER_HPP

#include <string>
#include <vector>
#include <functional>
#include "Game.hpp"

typedef unsigned int uint;

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

    public:

        void income();

        void foreign_aid();

        virtual void coup(Player &player);

        virtual std::string role() const = 0;

        int coins() const;

    };

}


#endif //CPP_EX4_PLAYER_HPP
