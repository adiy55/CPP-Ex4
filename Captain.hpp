//
// Created by adiya on 4/25/2022.
//

#ifndef CPP_EX4_CAPTAIN_HPP
#define CPP_EX4_CAPTAIN_HPP

#include "Player.hpp"

namespace coup {

    class Captain : public Player {

    public:

        Captain(Game& game, const std::string& name);

        std::string role() override;

        void block(Player& player);

        void steal(Player& player);

    };

}

#endif //CPP_EX4_CAPTAIN_HPP
