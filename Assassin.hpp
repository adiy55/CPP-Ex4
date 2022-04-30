#ifndef CPP_EX4_ASSASSIN_HPP
#define CPP_EX4_ASSASSIN_HPP


#include "Player.hpp"

namespace coup {

    class Assassin : public Player {

    private:

        const int _assassin_coup_price{3};

    public:

        Assassin(Game &game, const std::string &name);

        std::string role() const override;

        void coup(Player &player) override;

    };

}

#endif //CPP_EX4_ASSASSIN_HPP
