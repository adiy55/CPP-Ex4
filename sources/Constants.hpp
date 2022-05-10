#ifndef CPP_EX4_CONSTANTS_HPP
#define CPP_EX4_CONSTANTS_HPP

namespace constants {


    enum Actions {

        BLOCK_FOREIGN_AID, // Duke

        BLOCK_STEAL, // Ambassador, Captain

        COUP_RECOVER_PLAYER // Contessa

    };

    const int REGULAR_COUP_PRICE{7};

    const int ASSASSIN_COUP_PRICE{3};

    const int MAX_STEAL_PRICE{2};

    const int MAX_COINS_COUP{10};

    const int MIN_COINS{0};

    const int MAX_PLAYERS{5};

}

#endif //CPP_EX4_CONSTANTS_HPP
