#ifndef CPP_EX4_CONTESSA_HPP
#define CPP_EX4_CONTESSA_HPP

#include "Player.hpp"

namespace coup {

    class Contessa : public Player {

    private:

        using Player::getName;
        using Player::checkPositiveBalance;
        using Player::updateCoins;
        using Player::getExecutables;

    public:

        Contessa(Game &game, const std::string &name);

        std::string role() const override;

        void block(Player &player);

    };

}

#endif //CPP_EX4_CONTESSA_HPP
