#pragma once

enum class GameMode {

    EXPLORE = 0,
    BUILD,
    TRADE
};

namespace GlobalVars {

    extern GameMode gameMode;
    extern bool HoveringOverMenu;
    extern bool openInventory;
}