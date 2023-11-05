#include "bot.hpp"

using namespace std;

pair<uint8_t, uint8_t> bot::move(state::State game)
{
    srand(time(NULL));
    uint8_t x, y;
    x = rand() % 3;
    y = rand() % 3;
    while(!game.isFree(x, y))
    {
        x = rand() % 3;
        y = rand() % 3;
    }
    return {x, y};
}
