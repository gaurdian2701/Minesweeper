#pragma once

#include <iostream>
#include <bits/stdc++.h>

class Player
{
    private:
        std::pair<int, int> click;
    
    public:
        Player()
        {
            std::cout << "Player is ready.\n\n";
        }

        ~Player()
        {
            click = {0, 0};
            std::cout << "Player has left the game.\n\n";
        }

        std::pair<int, int> TakeTurn()
        {
            std::cout << "Enter the index where you want to click:\n";
            std::cin >> click.first;
            std::cin >> click.second;

            return click;
        }
};