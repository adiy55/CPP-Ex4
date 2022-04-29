//
// Created by adiya on 4/25/2022.
//

#include "Assassin.hpp"

namespace coup {

    Assassin::Assassin(Game &game, const std::string &name)
            : Player{game, name} {}

    std::string Assassin::role() const {
        return "Assassin";
    }

    int Assassin::getCoupPrice() const {
        return _assassin_coup_price;
    }

}