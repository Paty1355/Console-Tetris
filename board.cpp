#include <iostream>
#include <iomanip>
#include "naglowek.h"

int board[20][10];

void generateTab() {//Wype³nienie tablicy 0, aby ³atwiej by³o kontrolowaæ gdzie znajduje siê klocek
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            board[i][j] = 0;
        }
    }
}

void showBoard() {//wyœwietlenie planszy
    std::cout << std::setfill('-') << std::setw(13) << "\n";
    for (int i = 0; i < 20; i++) {
        std::cout << "|";
        for (int j = 0; j < 10; j++) {
            if (board[i][j] == 0)
                std::cout << " ";
            else
                std::cout << board[i][j];
        }
        std::cout << "|";
        std::cout << std::endl;
    }
    std::cout << std::setfill('-') << std::setw(13) << "\n";
    std::cout << "Score : " << score << std::endl;

}