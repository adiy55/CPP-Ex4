#ifndef CPP_EX4_PLAYER_HPP
#define CPP_EX4_PLAYER_HPP

#include <string>
#include <vector>
#include <functional>
#include "Game.hpp"
#include "Constants.hpp"

typedef unsigned int uint;

typedef std::unordered_map<int, std::function<void()>> func_map;
// callables are implicitly converted to std::function
// lambda is not a type std::function

namespace coup {

    class Game; // forward declaration (circular dependency)

    class Player {

    protected:

        Game &_game;
        std::string _name;
        int _coins;
        func_map _executables;
        bool _is_in_game;

        Player(Game &game, const std::string &name);

        int coupCheckBalance() const;

        virtual int getCoupPrice() const;

        void blockAction(Player &p, int action);

        void turnWrapper(const std::function<void()> &function);

        void checkCoupNecessary() const;

        uint basicCoup(Player &player);

        void validatePlayersInGame(std::initializer_list<std::reference_wrapper<Player>> players) const;

        void checkInGame() const;

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

        void setInGame();

    };

}


#endif //CPP_EX4_PLAYER_HPP
