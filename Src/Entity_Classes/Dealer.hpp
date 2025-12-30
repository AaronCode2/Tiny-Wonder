#include <raylib.h>
#include <string>

class Dealer {

    public:

        Dealer();   

        void refresh();
        int cost;
        int itemsToGiveOrNeeded[5];
        bool gettingMoney;

        static std::string dealerNames;

    private:

};