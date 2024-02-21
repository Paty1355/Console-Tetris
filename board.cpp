#include <iostream>
#include <iomanip>
#include "naglowek.h"

int board[20][10];

void generateTab() {//Wype�nienie tablicy 0, aby �atwiej by�o kontrolowa� gdzie znajduje si� klocek
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            board[i][j] = 0;
        }
    }
}

void showBoard() {//wy�wietlenie planszy
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