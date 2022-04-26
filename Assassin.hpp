//
// Created by adiya on 4/25/2022.
//

#ifndef CPP_EX4_ASSASSIN_HPP
#define CPP_EX4_ASSASSIN_HPP


#include "Player.hpp"

namespace coup {

    class Assassin : public Player {

    public:

        Assassin(Game &game, const std::string &name);

        std::string role() const override;

    };

}

#endif //CPP_EX4_ASSASSIN_HPP
