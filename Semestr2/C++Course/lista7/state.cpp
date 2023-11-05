#include "state.hpp"
using namespace std;
using namespace state;

State::State()
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            board[i][j] = 0;
        }
    }
}

uint8_t State::checkVertical()
{
    if(board[0][0] == 1 and board[1][0] == 1 and board[2][0] == 1) return 1;    
    if(board[0][1] == 1 and board[1][1] == 1 and board[2][1] == 1) return 1;    
    if(board[0][2] == 1 and board[1][2] == 1 and board[2][2] == 1) return 1;
    if(board[0][0] == 2 and board[1][0] == 2 and board[2][0] == 2) return 2;    
    if(board[0][1] == 2 and board[1][1] == 2 and board[2][1] == 2) return 2;    
    if(board[0][2] == 2 and board[1][2] == 2 and board[2][2] == 2) return 2;
    return 0;
}

uint8_t State::checkHorizontal()
{
    if(board[0][0] == 1 and board[0][1] == 1 and board[0][2] == 1) return 1;    
    if(board[1][0] == 1 and board[1][1] == 1 and board[1][2] == 1) return 1;    
    if(board[2][0] == 1 and board[2][1] == 1 and board[2][2] == 1) return 1;
    if(board[0][0] == 2 and board[0][1] == 2 and board[0][2] == 2) return 2;    
    if(board[1][0] == 2 and board[1][1] == 2 and board[1][2] == 2) return 2;    
    if(board[2][0] == 2 and board[2][1] == 2 and board[2][2] == 2) return 2;
    return 0;
}

uint8_t State::checkDiagonal()
{
    if(board[0][0] == 1 and board[1][1] == 1 and board[2][2] == 1) return 1;
    if(board[2][0] == 1 and board[1][1] == 1 and board[0][2] == 1) return 1;
    if(board[0][0] == 2 and board[1][1] == 2 and board[2][2] == 2) return 2;
    if(board[2][0] == 2 and board[1][1] == 2 and board[0][2] == 2) return 2;
    return 0;
}

void State::set_X(int x, int y)
{
    board[y][x] = 1;   
}

void State::set_O(int x, int y)
{
    board[y][x] = 2;
}

uint8_t State::checkWin()
{
    if(checkDiagonal() == 1 or checkHorizontal() == 1 or checkVertical() == 1) return 1;
    if(checkDiagonal() == 2 or checkHorizontal() == 2 or checkVertical() == 2) return 2;
    return 0;  
}