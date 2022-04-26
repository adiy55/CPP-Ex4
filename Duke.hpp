//
// Created by adiya on 4/25/2022.
//

#ifndef CPP_EX4_DUKE_HPP
#define CPP_EX4_DUKE_HPP

#include "Player.hpp"

namespace coup {

    class Duke : public Player {

    public:

        Duke(Game& game, const std::string& role);

        std::string role() override;

        void block(Player& player);

        void tax();

    };

}

#endif //CPP_EX4_DUKE_HPP
