#include <iostream>
#include <iomanip> //biblioteka kt�rej u�ywam do wy�wietlania planszy
#include <conio.h> //bibliotek od funkcji getch
#include <windows.h> //biblioteka od funkcji Sleep, dzi�ki kt�rej zaimplementowa�am wra�enie spadania klocka

int board[20][10]; //deklaracja planszy
int currentX = 4, currentY = 0; //deklaracja pocz�tkowego po�o�enia klocka na planszy
int score = 0; //deklaracja pocz�tkowej ilo�ci punkt�w

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

bool ifCollide(int random, char dir) {//Funkcja sprawdzaj�ca czy jest mo�liwo�� przesuni�cia klocka, dir - kierunek w kt�rym klocek ma zosta� przesuni�ty
    if (currentY + 1 > 19) { //gdy jest na ko�cu planszy zwraca false
        return false;
    }
    int dl = 0; //zmienna przechowuj�ca po�niej warto�� czy klocek ma by� przesuni�ty w prawo czy w lewo
    if (dir == 'a') dl = -1;
    else if (dir == 'd') dl = 1;

    switch (random) {//sprawdzanie dla ka�dego klocka w zale�no�ci od podanego kierunku, czy mo�e zosta� przesuni�ty
    case 1:
        if (dir != 's') {
            for (int i = 0; i < 4; i++) {
                if (board[currentY + i][currentX + dl] != 0) return false;
            }
        }
        else if (board[currentY + 1][currentX] != 0) return false;
        break;
    case 2:
        if (dir != 's') {
            if (board[currentY][currentX + 1 + dl] != 0) return false;
            else {
                if (dir == 'a' && board[currentY - 1][currentX - 1] != 0) return false;
                else if (dir == 'd' && board[currentY - 1][currentX + 3] != 0) return false;
            }
        }
        else if (board[currentY][currentX] != 0 || board[currentY + 1][currentX + 1] != 0 || board[currentY][currentX + 2] != 0) {
            return false;
        }
        break;

    case 3:
        if (dir != 's') {
            if (dir == 'a') {
                for (int i = 0; i < 2; i++) {
                    if (board[currentY - i][currentX + dl] != 0) return false;
                }
            }
            else if (dir == 'd') {
                for (int i = 0; i < 2; i++) {
                    if (board[currentY - i][currentX + 1 + dl] != 0) return false;
                }
            }
        }
        else if (board[currentY + 1][currentX] != 0 || board[currentY + 1][currentX + 1] != 0) return false;
        break;
    case 4:
        if (dir != 's') {
            if (dir == 'a') {
                for (int i = 0; i < 3; i++) {
                    if (board[currentY - i][currentX + 1 + dl] != 0) return false;
                }
            }
            else if (dir == 'd') {
                if (board[currentY - 1][currentX + 2] != 0 || board[currentY - 2][currentX + 2] != 0 || board[currentY][currentX + 3] != 0) return false;
            }
        }
        else if (board[currentY + 1][currentX + 1] != 0 || board[currentY + 1][currentX + 2] != 0) return false;
        break;
    case 5:
        if (dir != 's') {
            if (dir == 'a') {
                if (board[currentY - 1][currentX] != 0 || board[currentY - 2][currentX] != 0 || board[currentY][currentX + dl] != 0) return false;
            }
            else if (dir == 'd' && currentX < 8) {
                for (int i = 0; i < 3; i++) {
                    if (board[currentY - i][currentX + 1 + dl] != 0) return false;
                }
            }
        }
        else if (board[currentY + 1][currentX + 1] != 0 || board[currentY + 1][currentX] != 0) return false;
        break;
    case 6:
        if (dir != 's') {
            if (dir == 'a') {
                if (board[currentY][currentX - 1] != 0 || board[currentY - 1][currentX] != 0) return false;
            }
            else if (dir == 'd' && currentX < 7) {
                if (board[currentY][currentX + dl + 1] != 0 || board[currentY - 1][currentX + dl + 2] != 0) return false;
            }
        }
        else if (board[currentY + 1][currentX] != 0 || board[currentY + 1][currentX + 1] != 0 || board[currentY][currentX + 2] != 0) return false;
        break;
    case 7:
        if (dir != 's') {
            if (dir == 'a') {
                if (board[currentY][currentX] != 0 || board[currentY - 1][currentX - 1] != 0) return false;
            }
            else if (dir == 'd') {
                if (board[currentY][currentX + 3] != 0 || board[currentY - 1][currentX + 2] != 0) return false;
            }
        }
        else if (board[currentY + 1][currentX + 1] != 0 || board[currentY + 1][currentX + 2] != 0 || board[currentY][currentX] != 0) return false;
        break;
    }
    return true;
}

bool ifCanGenerate(int random) {//funkcja sprawdzaj�ca czy klocek ma miejsca na wygenerowanie si� na planszy
    if (random == 3) {
        for (int i = 0; i < 2; i++) {
            for (int j = 4; j < 6; j++) {
                if (board[i][j] != 0) {
                    return false;
                }
            }
        }
    }
    else if (random == 1) {
        for (int i = 0; i < 4; i++) {
            if (board[i][4] != 0) {
                return false;
            }
        }
    }
    else {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j + 4] != 0)
                    return false;
            }
        }
    }
    return true;
}

int generateBlock() {//funkcja generuj�ca randomowy blok na planszy
    int random_block = 1;
    srand(time(NULL));

    int block1[4][4]{//deklaracj� poszczeg�lnych blok�w w tablicach
     {1,0,0,0},
     {1,0,0,0},
     {1,0,0,0},
     {1,0,0,0},
    };
    int block2[3][3]{
     {1,1,1},
     {0,1,0},
     {0,0,0}
    };
    int block3[2][2]{
    {1,1},
    {1,1}
    };
    int block4[3][3]{
    {0,1,0},
    {0,1,0},
    {0,1,1}
    };
    int block5[3][3]{
    {0,1,0},
    {0,1,0},
    {1,1,0}
    };
    int block6[3][3]{
    {0,1,1},
    {1,1,0},
    {0,0,0}
    };
    int block7[3][3]{
    {1,1,0},
    {0,1,1},
    {0,0,0}
    };

    random_block = rand() % 7 + 1; //generowanie randomowego bloku
    currentY = 0;
    currentX = 4;
    if (ifCanGenerate(random_block)) {//sprawdzanie czy mo�e zosta� wygenerowany
        switch (random_block) {//je�li tak to w zale�no�ci od bloku generowanie go na pocz�tku planszy
        case 1:
            for (int i = 0; i < 4; i++) {
                board[i][4] = 1;
            }
            currentY = 3;
            break;
        case 2:
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (block2[i][j] == 1) board[i][j + 4] = 1;
                }
            }
            currentY = 1;
            break;
        case 3:
            for (int i = 0; i < 2; i++) {
                for (int j = 4; j < 6; j++) {
                    board[i][j] = 1;
                }
            }
            currentY = 1;
            break;
        case 4:
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (block4[i][j] == 1) board[i][j + 4] = 1;
                }
            }
            currentY = 2;
            break;
        case 5:
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (block5[i][j] == 1) board[i][j + 4] = 1;
                }
            }
            currentY = 2;
            break;
        case 6:
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (block6[i][j] == 1) board[i][j + 4] = 1;
                }
            }
            currentY = 1;
            break;
        case 7:
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (block7[i][j] == 1) board[i][j + 4] = 1;
                }
            }
            currentY = 1;
            break;
        }
    }
    else {
        return 8;
    }
    score += random_block;

    return random_block;
}

void moveDown(int random) { //funkcja przesuwaj�ca blok w d�
    if (ifCollide(random, 's')) { //sprawdzanie czy blok mo�e si� przesun��
        switch (random) { //przesuwanie w d� w zale�no�ci od bloku
        case 1:
            board[currentY - 3][currentX] = 0;
            board[currentY + 1][currentX] = 1;
            break;
        case 2:
            for (int i = currentX; i < currentX + 3; i++) {
                board[currentY - 1][i] = 0;
            }
            board[currentY][currentX] = 1;
            board[currentY + 1][currentX + 1] = 1;
            board[currentY][currentX + 2] = 1;
            break;
        case 3:
            for (int i = currentX; i < currentX + 2; i++) {
                board[currentY - 1][i] = 0;
            }
            board[currentY + 1][currentX] = 1;
            board[currentY + 1][currentX + 1] = 1;
            break;
        case 4:
            board[currentY - 2][currentX + 1] = 0;
            board[currentY][currentX + 2] = 0;
            board[currentY + 1][currentX + 1] = 1;
            board[currentY + 1][currentX + 2] = 1;
            break;
        case 5:
            board[currentY - 2][currentX + 1] = 0;
            board[currentY][currentX] = 0;
            board[currentY + 1][currentX + 1] = 1;
            board[currentY + 1][currentX] = 1;
            break;
        case 6:
            board[currentY - 1][currentX + 1] = 0;
            board[currentY - 1][currentX + 2] = 0;
            board[currentY][currentX] = 0;
            board[currentY][currentX + 2] = 1;
            board[currentY + 1][currentX] = 1;
            board[currentY + 1][currentX + 1] = 1;
            break;
        case 7:
            board[currentY - 1][currentX] = 0;
            board[currentY - 1][currentX + 1] = 0;
            board[currentY][currentX + 2] = 0;
            board[currentY][currentX] = 1;
            board[currentY + 1][currentX + 1] = 1;
            board[currentY + 1][currentX + 2] = 1;
            break;

        }
        currentY++;
        score += random;
    }
}

void menuStart();

void userInput(int random) {//Sprawdza ruch gracza
    int dl = 0;
    bool ifMoved = false; //zmienna u�ywana do sprawdzania czy klocek si� poruszy�, je�li tak to w dalszej cz�ci po ifie aktualizuje jego wsp�rzedne
    if (_kbhit()) {
        char key = _getch();

        if (key == 'a') dl = -1;
        else if (key == 'd') dl = 1;
        else if (key == '\x1b') {//Esc i wyjscie do menu
            system("cls");
            generateTab();
            currentX = 4;
            score = 0;
            menuStart();
        }
        else if (key == '4') {//Klikniecie 4 i zakonczenie programu
            system("cls");
            std::cout << "Koniec gry, tw�j wynik to: " << score << std::endl;
            exit(0);
        }

        if (ifCollide(random, key) && currentX > 0 && currentX < 9) { //przesuni�cie klocka o wybrany kierunek, je�li jest taka mo�liwo��
            switch (random) {
            case 1:
                if (key != 's') {
                    for (int i = 0; i < 4; i++) {
                        board[currentY - 3 + i][currentX] = 0;
                        board[currentY - 3 + i][currentX + dl] = 1;
                    }
                    currentX = currentX + dl;
                }
                else {
                    moveDown(random);
                }
                break;
            case 2:
                if (key != 's') {
                    if (key == 'a') {
                        board[currentY - 1][currentX + 2] = 0;
                        board[currentY - 1][currentX - 1] = 1;
                        ifMoved = true;
                    }
                    else if (key == 'd' && currentX < 7) {
                        board[currentY - 1][currentX] = 0;
                        board[currentY - 1][currentX + 3] = 1;
                        ifMoved = true;
                    }
                    if (ifMoved) {
                        board[currentY][currentX + 1] = 0;
                        board[currentY][currentX + 1 + dl] = 1;
                        currentX = currentX + dl;
                    }
                }
                else moveDown(random);
                break;
            case 3:
                if (key != 's') {
                    if (key == 'a') {
                        for (int i = 0; i < 2; i++) {
                            board[currentY - i][currentX - dl] = 0;
                            board[currentY - i][currentX + dl] = 1;
                        }
                        currentX = currentX + dl;
                    }
                    else if (key == 'd' && currentX < 8) {
                        for (int i = 0; i < 2; i++) {
                            board[currentY - i][currentX] = 0;
                            board[currentY - i][currentX + 1 + dl] = 1;
                        }
                        currentX = currentX + dl;
                    }
                }
                else {
                    moveDown(random);
                }
                break;
            case 4:
                if (key != 's') {
                    if (key == 'a') {
                        for (int i = 0; i < 3; i++) {
                            board[currentY - i][currentX + 1 + dl] = 1;
                        }
                        board[currentY - 1][currentX + 1] = 0;
                        board[currentY - 2][currentX + 1] = 0;
                        board[currentY][currentX + 2] = 0;
                        currentX = currentX + dl;
                    }
                    else if (key == 'd' && currentX < 7) {
                        for (int i = 0; i < 3; i++) {
                            board[currentY - i][currentX + dl] = 0;
                        }
                        board[currentY - 1][currentX + 2] = 1;
                        board[currentY - 2][currentX + 2] = 1;
                        board[currentY][currentX + 3] = 1;
                        currentX = currentX + dl;
                    }
                }
                else {
                    moveDown(random);
                }
                break;
            case 5:
                if (key != 's') {
                    if (key == 'a') {
                        for (int i = 0; i < 3; i++) {
                            board[currentY - i][currentX - dl] = 0;
                        }
                        board[currentY - 1][currentX] = 1;
                        board[currentY - 2][currentX] = 1;
                        board[currentY][currentX + dl] = 1;
                        currentX = currentX + dl;
                    }
                    else if (key == 'd' && currentX < 8) {
                        for (int i = 0; i < 3; i++) {
                            board[currentY - i][currentX + 1 + dl] = 1;
                        }
                        board[currentY - 1][currentX + 1] = 0;
                        board[currentY - 2][currentX + 1] = 0;
                        board[currentY][currentX] = 0;
                        currentX = currentX + dl;
                    }
                }
                else {
                    moveDown(random);
                }
                break;
            case 6:
                if (key != 's') {
                    if (key == 'a') {
                        board[currentY][currentX - 1] = 1;
                        board[currentY - 1][currentX] = 1;
                        board[currentY][currentX + 1] = 0;
                        board[currentY - 1][currentX + 2] = 0;
                        currentX = currentX + dl;
                    }
                    else if (key == 'd' && currentX < 7) {
                        board[currentY][currentX + dl + 1] = 1;
                        board[currentY - 1][currentX + dl + 2] = 1;
                        board[currentY][currentX] = 0;
                        board[currentY - 1][currentX + 1] = 0;
                        currentX = currentX + dl;
                    }
                }
                else {
                    moveDown(random);
                }
                break;
            case 7:
                if (key != 's') {
                    if (key == 'a') {
                        board[currentY][currentX] = 1;
                        board[currentY - 1][currentX - 1] = 1;
                        board[currentY][currentX + 2] = 0;
                        board[currentY - 1][currentX + 1] = 0;
                        currentX = currentX + dl;
                    }
                    else if (key == 'd' && currentX < 7) {
                        board[currentY - 1][currentX] = 0;
                        board[currentY][currentX + 1] = 0;
                        board[currentY][currentX + 3] = 1;
                        board[currentY - 1][currentX + 2] = 1;
                        currentX = currentX + dl;
                    }
                }
                else {
                    moveDown(random);
                }
                break;

            }
        }
        system("cls");
        showBoard();
    }
}

void deleteRow() { //usuwanie wiersza - je�li zape�ni�a si� linia to j� kasuje
    int all = 0, row = 0;
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j < 10; j++) {
            if (board[currentY - i][j] == 1) all++;
            else break;
        }
        if (all == 10) {
            score += 10;
            row = currentY - i;
            while (row > 0) {
                for (int p = 0; p < 10; p++) {
                    board[row][p] = board[row - 1][p];
                }
                row--;
            }
            currentY++;
        }
        all = 0;
    }
}

void play() {//funkcja od rozpocz�nia gry
    int block = generateBlock(); //wywo�anie wygenerowania klocka
    if (block != 8) {
        system("cls");
        showBoard();
        while (ifCollide(block, 's')) {//p�tla odpowiadaj�ca za spadanie klocka w d�, dop�ki mo�e
            userInput(block);
            moveDown(block);
            Sleep(200);
            system("cls");
            showBoard();
        }
        deleteRow();//sprawdzenie czy jest mo�liwo�� usuni�cia jakiej� linii
        play();
    }
    else {
        system("cls");
        std::cout << "Koniec gry, tw�j wynik to: " << score << std::endl;
        exit(0);
    }

}

void menuStart() {//wy�wietlenie i obs�u�enie Menu
    char choice = '0';

    setlocale(LC_ALL, "pl-US");

    std::cout << "Tetris LV HARD" << std::endl;
    std::cout << "Menu - Wybierz opcje 1 - 4" << std::endl;
    std::cout << "1. Zagraj" << std::endl;
    std::cout << "2. Instrukcja" << std::endl;
    std::cout << "3. Zobacz autora" << std::endl;
    std::cout << "4. Zako�cz" << std::endl;

    while (choice != '1' && choice != '2' && choice != '3' && choice != '4') {
        if (_kbhit()) {
            choice = _getch();
            switch (choice) {
            case '1':
                generateTab();
                play();
                break;
            case '2':
                system("cls");
                std::cout << "Aby gra� w Tetris u�yj klawiszy ASD" << std::endl;
                std::cout << "A - przesu� klocek w lewo" << std::endl;
                std::cout << "D - przesu� klocek w prawo" << std::endl;
                std::cout << "S - przesu� klocek w d�" << std::endl;
                std::cout << "Staraj si� u�o�y� wiersze klock�w, aby zdoby� wi�cej punkt�w" << std::endl;
                std::cout << "Gra si� ko�czy gdy klocek u g�ry nie b�dzie mia� miejsca na wygenerowanie" << std::endl;
                std::cout << "Powodzenia!" << std::endl;
                std::cout << "Je�li chcesz wr�ci� do menu wci�nij ESC, aby zako�czyc program wci�nij 4" << std::endl;
                while (choice != '4' && choice != '\x1b') {
                    choice = _getch();
                    if (choice == '\x1b') {
                        system("cls");
                        menuStart();
                    }
                    else if (choice == '4') exit(0);
                }
                break;
            case '3':
                system("cls");
                std::cout << "Patrycja Prusak Informatyka 1 semestr" << std::endl;
                std::cout << "Je�li chcesz wr�ci� do menu wci�nij ESC, aby zako�czyc program wci�nij 4" << std::endl;

                while (choice != '4' && choice != '\x1b') {
                    choice = _getch();
                    if (choice == '\x1b') {
                        system("cls");
                        menuStart();
                    }
                    else if (choice == '4') exit(0);
                }
                break;
            case '4':
                exit(0);
                break;
            }

        }
    }
}