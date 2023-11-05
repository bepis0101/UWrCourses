#pragma once
#include <bits/stdc++.h>
using namespace std;


namespace state
{
    class State
    {
        protected:
            uint8_t board[3][3];
            uint8_t checkVertical();
            uint8_t checkHorizontal();
            uint8_t checkDiagonal();

        public:
            State();
            void set_X(int x, int y);
            void set_O(int x, int y);
            uint8_t checkWin();
            inline bool isFree(int x, int y) { return !board[y][x]; }

    };

};