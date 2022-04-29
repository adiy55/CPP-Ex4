//
// Created by adiya on 4/26/2022.
//

#include "doctest.h"
#include "Duke.hpp"
#include "Assassin.hpp"
#include "Ambassador.hpp"
#include "Captain.hpp"
#include "Contessa.hpp"
#include "Game.hpp"

using namespace coup;

TEST_CASE ("Good Input") {
    Game game_1{};
    Duke duke{game_1, "Moshe"};
    Assassin assassin{game_1, "Yossi"};
    Ambassador ambassador{game_1, "Meirav"};
    Captain captain{game_1, "Reut"};
    Contessa contessa{game_1, "Gilad"};

            SUBCASE("Add a player with an existing role") {
                CHECK_NOTHROW((Duke{game_1, "Alvin"}));
    }

            SUBCASE("Count coins") {

    }

            SUBCASE("Role") { // check virtual function
                CHECK(duke.role() == "Duke");
                CHECK(assassin.role() == "Assassin");
                CHECK(ambassador.role() == "Ambassador");
                CHECK(captain.role() == "Captain");
                CHECK(contessa.role() == "Contessa");
    }

            SUBCASE("Check that order of players is the order of insertion to the game") {

    }
}

TEST_CASE ("Bad Input- Player Actions") {
    Game game_1{};
    Duke duke{game_1, "Moshe"};
    Assassin assassin{game_1, "Yossi"};
    Ambassador ambassador{game_1, "Meirav"};
    Captain captain{game_1, "Reut"};
    Contessa contessa{game_1, "Gilad"};

            SUBCASE("Not the players turn") {
                CHECK_THROWS(assassin.income(););
                CHECK_THROWS(captain.foreign_aid(););
                CHECK_THROWS(contessa.income());
    }

            SUBCASE("Not enough coins for coup") {

    }

            SUBCASE("Blocking an operation that can not be blocked") {
        duke.tax();
        assassin.income();
        ambassador.income();
                CHECK_THROWS(captain.block(duke););
                CHECK_THROWS(captain.block(assassin););
                CHECK_THROWS(captain.block(ambassador););
        captain.foreign_aid();
                CHECK_THROWS(contessa.block(duke););
                CHECK_THROWS(contessa.block(assassin););
                CHECK_THROWS(contessa.block(ambassador););
                CHECK_THROWS(contessa.block(captain););
    }

}

TEST_CASE ("Ambassador Tests") {
    Game game_1{};
    Duke duke{game_1, "Moshe"};
    Assassin assassin{game_1, "Yossi"};
    Ambassador ambassador{game_1, "Meirav"};
    Captain captain{game_1, "Reut"};
    Contessa contessa{game_1, "Gilad"};

            SUBCASE("Bad Input- Not enough coins for transfer") {
                CHECK_THROWS(duke.coup(assassin););
        duke.income();
        assassin.income();
                CHECK_THROWS(ambassador.transfer(captain, duke);); // captain has 0 coins
                CHECK(duke.coins() == 1);
                CHECK_NOTHROW(ambassador.transfer(duke, captain);); // duke has 1 coin
    }

            SUBCASE("Good Input- Enough coins for transfer") {

    }
}