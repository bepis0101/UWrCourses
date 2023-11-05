#include "gameplay.hpp"
using namespace std;
using namespace game;

Game::Game() : state::State() {}

void Game::print()
{
    cout << ' ';
    for(int i = 1; i <= 3; i++)
    {
        cout << ' ' << i; 
    }
    cout << "\n";
    for(int i = 1; i <= 3; i++)
    {
        cout << (char)('A' + (i-1)) << ' ';
        for(int j = 1; j < 3; j++)
        {
            if(board[i-1][j-1] == 0) cout << ".|";
            if(board[i-1][j-1] == 1) cout << "X|";
            if(board[i-1][j-1] == 2) cout << "O|";
        }
        if(board[i-1][2] == 0) cout << ".\n ";
        if(board[i-1][2] == 1) cout << "X\n ";
        if(board[i-1][2] == 2) cout << "O\n ";
        cout << ' '; 
        if(i <= 2)
        {
            for(int j = 1; j < 6; j++) cout << '-';
        }
        cout << "\n";
    }
    cout << "\n";
}


void Game::gameplay()
{
    cout << "1. Aby wystartowac jako kolko wpisz 1\n";
    cout << "2. Aby wystartowac jako krzyzyk wpisz 2\n";
    int whoStarts;
    cin >> whoStarts;
    if(whoStarts == 1)
    {
        while(true)
        {
            this->print();
            string s; cin >> s;
            uint8_t x; 
            uint8_t y;
            if(s[0] > s[1])
            {
                x = toupper(s[0])-'A';
                y = s[1]-'1';
            }
            else
            {
                x = toupper(s[1])-'A';
                y = s[0]-'1';
            }
            if(x > 2 or y > 2) throw invalid_argument("field doesnt exist");
            if(!this->isFree(x, y)) throw invalid_argument("field taken");
            this->set_O(x, y);
            this->print();
            if(this->checkWin() == 2)
            {
                cout << "WYGRANA O\n";
                return;
            }
            auto pb = bot::move(*this);
            this->set_X(pb.first, pb.second);
            if(this->checkWin() == 1)
            {
                cout << "WYGRANA X\n";
                return;
            }
        }
    }
    else
    {
        while(true)
        {
            auto pb = bot::move(*this);
            this->set_O(pb.first, pb.second);
            if(this->checkWin() == 1)
            {
                cout << "WYGRANA O\n";
                return;
            }
            this->print();
            string s; cin >> s;
            uint8_t x;
            uint8_t y;
            if(s[0] > s[1])
            {
                x = toupper(s[0])-'A';
                y = s[1]-'1';
            }
            else
            {
                x = toupper(s[1])-'A';
                y = s[0]-'1';
            }
            if(x > 2 or y > 2) throw invalid_argument("field doesnt exist");
            if(!this->isFree(x, y)) throw invalid_argument("field taken");
            this->set_X(x, y);
            this->print();
            if(this->checkWin() == 2)
            {
                cout << "WYGRANA X\n";
                return;
            }
        }
    }
}