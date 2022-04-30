//
// Created by adiya on 4/25/2022.
//

#ifndef CPP_EX4_ASSASSIN_HPP
#define CPP_EX4_ASSASSIN_HPP


#include "Player.hpp"

namespace coup {

    class Assassin : public Player {

        const int _assassin_coup_price{3};

        using Player::coupCheckBalance;
        using Player::getCoupPrice;
        using Player::blockAction;
        using Player::getName;
        using Player::checkPositiveBalance;
        using Player::updateCoins;
        using Player::getExecutables;
        using Player::setupTurn;

    public:

        Assassin(Game &game, const std::string &name);

        std::string role() const override;

        int getCoupPrice() const override;

    };

}

#endif //CPP_EX4_ASSASSIN_HPP
