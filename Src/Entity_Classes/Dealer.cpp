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

    itemsToGiveOrNeeded = GetRandomValue(0, 40);

    plantRequired = (PLANTS) GetRandomValue(1, 5);
    cost = GetRandomValue(5, 520) * (int) plantRequired;

    cost += GetRandomValue(0, itemsToGiveOrNeeded);
}
