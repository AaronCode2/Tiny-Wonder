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

    gettingMoney = (bool) GetRandomValue(0, 1);
    iName = GetRandomValue(0, 29);

    plantRequired = (PLANTS) GetRandomValue(1, 5);
    cost = GetRandomValue(5, 50) * (int) plantRequired;

    if(!gettingMoney) {

        itemsToGiveOrNeeded = GetRandomValue(-30, 30) - GetRandomValue(1, 100) * (int) plantRequired;
        cost += GetRandomValue(0, itemsToGiveOrNeeded) * (int) plantRequired;
    } else  {

        itemsToGiveOrNeeded =  GetRandomValue(1, 40);
        cost += GetRandomValue(0, itemsToGiveOrNeeded) * GetRandomValue(1, 9);        
    }
}
