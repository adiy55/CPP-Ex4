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

    int Assassin::coupCheckBalance() const {
        int cost = 3;
        if (_coins < cost) {
            throw std::invalid_argument{"Not enough coins for coup!"};
        }
        return cost;
    }

}