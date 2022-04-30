#ifndef CPP_EX4_AMBASSADOR_HPP
#define CPP_EX4_AMBASSADOR_HPP

#include "Player.hpp"

namespace coup {

    class Ambassador : public Player {

    private:

        void validateTransfer(Player &from, Player &to) const;

        using Player::coupCheckBalance;
        using Player::getCoupPrice;
        using Player::blockAction;
        using Player::getName;
        using Player::checkPositiveBalance;
        using Player::updateCoins;
        using Player::getExecutables;
        using Player::turnWrapper;

    public:

        Ambassador(Game &game, const std::string &name);

        std::string role() const override;

        void transfer(Player &from, Player &to);

        void block(Player &player);

    };

}

#endif //CPP_EX4_AMBASSADOR_HPP
