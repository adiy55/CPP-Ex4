#ifndef CPP_EX4_GAME_HPP
#define CPP_EX4_GAME_HPP

#include <vector>
#include <string>
#include <functional>
#include "Player.hpp"
#include "Constants.hpp"

typedef unsigned int uint;

/**
 * "std::reference_wrapper is a class template that wraps a reference in a copyable, assignable object.
 * It is frequently used as a mechanism to store references inside standard containers (like std::vector)
 * which cannot normally hold references."
 * https://en.cppreference.com/w/cpp/utility/functional/reference_wrapper
 * The method "get" is used to access the stored reference.
 */

namespace coup {

    class Player; // forward declaration (circular dependency)

    class Game {

    private:

        std::vector<std::reference_wrapper<Player>> _players;
        uint _player_idx;
        bool _is_started;

        void checkWinner() const;

        void checkInsert() const;

        void checkNotStarted() const;

    public:

        Game();

        std::string turn();

        std::vector<std::string> players();

        std::string winner();

        // helper functions

        void insertPlayer(Player &p);

        void insertPlayer(Player &p, uint index);

        uint removePlayer(Player &p);

        void incrementTurn();

    };

}

#endif //CPP_EX4_GAME_HPP
