#include "doctest.h"
#include "Duke.hpp"
#include "Assassin.hpp"
#include "Ambassador.hpp"
#include "Captain.hpp"
#include "Contessa.hpp"
#include "Game.hpp"

using namespace coup;

TEST_CASE ("Basic Functions") {
    Game game{};
    Duke duke{game, "Moshe"};
    Assassin assassin{game, "Yossi"};
    Ambassador ambassador{game, "Meirav"};
    Captain captain{game, "Reut"};
    Contessa contessa{game, "Gilad"};

            SUBCASE("Add a player with an existing role or name") {
                CHECK_NOTHROW((Duke{game, "Alvin"}));
                CHECK_NOTHROW((Ambassador{game, "Alvin"}));
    }

            SUBCASE("Count coins") {
        duke.tax();
        assassin.foreign_aid();
        ambassador.income();
        captain.income();
        contessa.foreign_aid();

                CHECK(duke.coins() == 3);
                CHECK(assassin.coins() == 2);
                CHECK(ambassador.coins() == 1);
                CHECK(captain.coins() == 1);
                CHECK(contessa.coins() == 2);

        duke.block(contessa);

                CHECK(contessa.coins() == 0);

    }

            SUBCASE("Role") { // check virtual function
                CHECK(duke.role() == "Duke");
                CHECK(assassin.role() == "Assassin");
                CHECK(ambassador.role() == "Ambassador");
                CHECK(captain.role() == "Captain");
                CHECK(contessa.role() == "Contessa");
    }

            SUBCASE("Check that order of players is the order of insertion in the game") {
        std::vector<std::string> players = game.players();
        if (players.size() == 5) {
                    CHECK(players[0] == "Moshe");
                    CHECK(players[1] == "Yossi");
                    CHECK(players[2] == "Meirav");
                    CHECK(players[3] == "Reut");
                    CHECK(players[4] == "Gilad");
        }
    }

            SUBCASE("No players in game") {
        Game game2{};
                CHECK_THROWS(game2.winner(););
                CHECK_THROWS(game2.turn(););
    }

            SUBCASE("No winner- game has not ended") {
                CHECK_THROWS(game.winner(););
    }
}

TEST_CASE ("Bad Input- Basic Player Actions") {
    Game game{};
    Duke duke{game, "Moshe"};
    Assassin assassin{game, "Yossi"};
    Ambassador ambassador{game, "Meirav"};
    Captain captain{game, "Reut"};
    Contessa contessa{game, "Gilad"};

    duke.income();
    assassin.income();
    ambassador.income();
    captain.income();
    contessa.income();

            SUBCASE("Incorrect player turn") {
                CHECK_THROWS(assassin.income(););
                CHECK_THROWS(captain.foreign_aid(););
                CHECK_THROWS(contessa.income());
    }

            SUBCASE("Not enough coins for coup") {
                CHECK_THROWS(duke.coup(assassin););
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

            SUBCASE("Check that turn matches after coup") {
        duke.tax();
        assassin.foreign_aid();
        ambassador.transfer(duke, captain);
        captain.steal(duke);
        contessa.income();

                SUBCASE("Player index - before") {
            duke.income();
            assassin.coup(duke);
                    CHECK(game.turn() == "Meirav");
        }

                SUBCASE("Player index - after") {
            duke.tax();
            assassin.income();
            ambassador.transfer(assassin, captain);
            captain.foreign_aid();
            contessa.foreign_aid();

            duke.tax();
            assassin.income();
            ambassador.income();

            captain.coup(contessa);
                    CHECK(game.turn() == "Moshe");
            duke.coup(assassin);
                    CHECK(game.turn() == "Meirav");
        }
    }

}

TEST_CASE ("Captain & Ambassador Tests") {
    Game game{};
    Duke duke{game, "Moshe"};
    Assassin assassin{game, "Yossi"};
    Ambassador ambassador{game, "Meirav"};
    Captain captain{game, "Reut"};
    Contessa contessa{game, "Gilad"};

    duke.income();
    assassin.income();
    ambassador.income();
    captain.income();
    contessa.income();

    duke.income();
    assassin.income();

            SUBCASE("Invalid block- nothing to block") {
                CHECK_THROWS(ambassador.block(captain););
    }
            SUBCASE("Valid steal") {
        ambassador.income();
                CHECK_NOTHROW(captain.steal(ambassador););

                SUBCASE("Valid block") {
            contessa.income();
            duke.income();
            assassin.income();
                    CHECK_NOTHROW(ambassador.block(captain););

                    SUBCASE("Invalid block- already blocked action") {
                        CHECK_THROWS(ambassador.block(captain););
            }
        }
    }

            SUBCASE("Captain Tests- invalid steal") { // steals from himself
        ambassador.income();
                CHECK_THROWS(captain.steal(captain););
    }

}

TEST_CASE ("Assassin Tests- can coup with 3 coins") {
    Game game{};
    Duke duke{game, "Moshe"};
    Assassin assassin{game, "Yossi"};
    Ambassador ambassador{game, "Meirav"};
    Captain captain{game, "Reut"};
    Contessa contessa{game, "Gilad"};

    duke.income();
    assassin.income();
    ambassador.income();
    captain.income();
    contessa.income();

            SUBCASE("Valid coup") {
        duke.income();
                SUBCASE("Case 1") {
            assassin.income();
            ambassador.transfer(contessa, assassin);
            captain.income();
            contessa.income();
            duke.income();
                    CHECK_NOTHROW(assassin.coup(captain));
        }
                SUBCASE("Case 2") {
            assassin.foreign_aid();
            ambassador.income();
            captain.income();
            contessa.income();
            duke.income();
                    CHECK_NOTHROW(assassin.coup(duke));
        }
    }

            SUBCASE("Invalid coup") {
                SUBCASE("Case 1") {
            duke.income();
            assassin.foreign_aid();
            ambassador.income();
            captain.income();
            contessa.income();
            duke.block(assassin);
                    CHECK_THROWS(assassin.coup(ambassador));
        }
    }

}

TEST_CASE ("Ambassador Tests- can transfer coins between players") {
    Game game{};
    Duke duke{game, "Moshe"};
    Assassin assassin{game, "Yossi"};
    Ambassador ambassador{game, "Meirav"};
    Captain captain{game, "Reut"};
    Contessa contessa{game, "Gilad"};

    duke.income();
    assassin.income();
    ambassador.income();
    captain.income();
    contessa.income();

    duke.income();
    assassin.income();

            SUBCASE("Invalid transfer- ambassador to ambassador") {
                CHECK_THROWS(ambassador.transfer(ambassador, ambassador););
    }

            SUBCASE("Valid transfer- enough coins") {
        ambassador.transfer(duke, captain);
    }
}

TEST_CASE ("Contessa Tests- can block Assassin coup") {
    Game game{};
    Duke duke{game, "Moshe"};
    Assassin assassin{game, "Yossi"};
    Ambassador ambassador{game, "Meirav"};
    Captain captain{game, "Reut"};
    Contessa contessa{game, "Gilad"};

    duke.income();
    assassin.income();
    ambassador.income();
    captain.income();
    contessa.income();

    duke.tax();
    assassin.foreign_aid();
    ambassador.income();
    captain.income();
    contessa.foreign_aid();

            SUBCASE("Valid block") {
        duke.tax();
        assassin.coup(contessa);
        ambassador.income();
        captain.income();
                CHECK_NOTHROW(contessa.block(assassin););

                SUBCASE("Invalid block- already blocked action") {
                    CHECK_THROWS(contessa.block(assassin););
        }
    }

            SUBCASE("Invalid block") {
        duke.tax();
        assassin.income();
        ambassador.income();
        captain.income();

                SUBCASE("Case 1- blocks herself") {
                    CHECK_THROWS(contessa.block(contessa););
        }

                SUBCASE("Case 2- Contessa can't block Duke") {
            contessa.income();
            duke.coup(contessa);
            assassin.income();
            ambassador.income();
            captain.income();
                    CHECK_THROWS(contessa.block(duke););
        }

                SUBCASE("Case 3- Assassin didn't coup Contessa") {
                    CHECK_THROWS(contessa.block(assassin););
        }
    }
}

TEST_CASE ("Duke Tests") {
    Game game{};
    Duke duke{game, "Moshe"};
    Assassin assassin{game, "Yossi"};
    Ambassador ambassador{game, "Meirav"};
    Captain captain{game, "Reut"};
    Contessa contessa{game, "Gilad"};

    duke.foreign_aid();
    assassin.income();
    ambassador.income();
    captain.foreign_aid();
    contessa.income();

            SUBCASE("Check tax") {
        duke.tax();
                CHECK(duke.coins() == 5);
    }

            SUBCASE("Valid block") {
                CHECK_NOTHROW(duke.block(captain););

                SUBCASE("Invalid block- already blocked action") {
                    CHECK_THROWS(duke.block(captain););
        }
    }

            SUBCASE("Invalid block") {
                SUBCASE("Case 1- nothing to block") {
                    CHECK_THROWS(duke.block(contessa););
        }
                SUBCASE("Case 2- duke blocks himself") {
                    CHECK_THROWS(duke.block(duke););
        }
    }

}