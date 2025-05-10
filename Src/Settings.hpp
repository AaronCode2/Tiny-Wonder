#pragma once

enum class GameMode {

    EXPLORE = 0,
    BUILD,
    TRADE
};

namespace Settings {

    extern GameMode gameMode;
}