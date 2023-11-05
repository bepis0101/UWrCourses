#pragma once
#include "bot.hpp"
using namespace std;
namespace game
{
    class Game : state::State
    {
        private:
            void print();

        public:
            Game();
            void gameplay();
    };
};
