#include "Dealer.hpp"

std::string Dealer::dealerNames[30] = {

    "Titus", "Aaron", "Nathan", "Jenny", "Gracy", "Ben",
    "James", "Robert", "Thomas", "Linda", "Susan", "Betty",
    "Daniel", "Kevin", "Ryan", "Sharon", "Amanda", "Samantha",
    "Larry", "Brandon", "Benjamin", "Helen", "Hannah", "Megan",
    "Frank", "Walter", "Logan", "Martha", "Isla", "Sara",
};

Dealer::Dealer() {

    refresh();
}

void Dealer::refresh() {

    gettingMoney = GetRandomValue(0, 1);
    iName = GetRandomValue(0, 29);

    itemsToGiveOrNeeded[0] = GetRandomValue(0, 40);
    itemsToGiveOrNeeded[1] = GetRandomValue(0, 30);
    itemsToGiveOrNeeded[2] = GetRandomValue(0, 20);
    itemsToGiveOrNeeded[3] = GetRandomValue(0, 10);

    cost = GetRandomValue(5, 520);

    cost += GetRandomValue(0, itemsToGiveOrNeeded[0]);
    cost += GetRandomValue(2, itemsToGiveOrNeeded[1]);
    cost += GetRandomValue(4, itemsToGiveOrNeeded[2]);
    cost += GetRandomValue(6, itemsToGiveOrNeeded[3]);
}
