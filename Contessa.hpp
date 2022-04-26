//
// Created by adiya on 4/25/2022.
//

#ifndef CPP_EX4_CONTESSA_HPP
#define CPP_EX4_CONTESSA_HPP

#include "Player.hpp"

namespace coup {

    class Contessa : public Player {

    public:

        Contessa(Game &game, const std::string &name);

        std::string role() const override;

        void block(Player &player);

    };

}

#endif //CPP_EX4_CONTESSA_HPP
