#ifndef CPP_EX4_CAPTAIN_HPP
#define CPP_EX4_CAPTAIN_HPP

#include "Player.hpp"

namespace coup {

    class Captain : public Player {

    private:
        void validateSteal(Player &p);

        using Player::getName;
        using Player::checkPositiveBalance;
        using Player::updateCoins;
        using Player::getExecutables;

    public:

        Captain(Game &game, const std::string &name);

        std::string role() const override;

        void block(Player &player);

        void steal(Player &player);

    };

}

#endif //CPP_EX4_CAPTAIN_HPP
