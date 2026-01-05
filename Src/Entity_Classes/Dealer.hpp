#include <raylib.h>
#include <string>
#include "Plant.hpp"

class Dealer {

    public:

        Dealer();   

        void refresh();
        int cost;
        int itemsToGiveOrNeeded;
        PLANTS plantRequired;
        bool gettingMoney;
        int iName;

        static std::string dealerNames[30];

    private:

};