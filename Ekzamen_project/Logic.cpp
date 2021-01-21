#include "Logic.h"

Player::Player() : healPoints(20)
{
    field.resize(10);
    for_each(field.begin(), field.end(), [](vector<char>& fieldRow)
        {
            fieldRow.resize(10, ' ');
        });
}

int Player::getHealPoints() { return healPoints; }

//===================Отображение игрового поля==========================================================================================================
void Player::PrintField(const int& x, const int& y, void(*function)(int& i, int& j, std::vector<std::vector<char>>& field))
{
    COORD position = { x,y }; //позиция x и y
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(hConsole, position);
    wcout << L"   1   2   3   4   5   6   7   8   9   10\n";
    position.Y++;

    SetConsoleCursorPosition(hConsole, position);
    wcout << L" ┏━━━┯━━━┯━━━┯━━━┯━━━┯━━━┯━━━┯━━━┯━━━┯━━━┓\n";
    position.Y++;


    SetConsoleCursorPosition(hConsole, position);
    for (int i = 0; i < 10; i++)
    {
        char Letter = 'A';
        for (int j = 0; j <= 41; j++)
        {
            if (j == 0)
            {
                wcout << (char)(Letter + i);
            }
            else if (j == 1 || j == 41)
            {
                wcout << L"┃";
            }
            else if ((j - 1) % 4 == 0)
            {
                wcout << L"│";
            }
            else
            {
                function(i, j, field);
            }
        }
        wcout << endl;
        if (i < 9)
        {
            position.Y++;
            SetConsoleCursorPosition(hConsole, position);

            wcout << L" ┠───┼───┼───┼───┼───┼───┼───┼───┼───┼───┨";
            wcout << endl;
        }
        position.Y++;
        SetConsoleCursorPosition(hConsole, position);
    }
    wcout << L" ┗━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┛\n";
}

//===================Заполнение игрового поля (автоматическое и ручное)==========================================================================================================
//=============Автоматическое=============//
void Player::AutoFieldFilling()
{
    int firstRow = 0;
    int firstColumn = 0;
    int secondRow = 0;
    int secondColumn = 0;

    int currentShipSize = 0;
    int battleship = 0; //4 палубный - 1
    int cruisers = 0; //3 палубный - 2
    int submarines = 0; //2 палубный - 3
    int destroyers = 0; //1 палубный - 4

    bool shipsArePlaced = false;

    int randNum = 2;

    while (!shipsArePlaced) {
        RandomPoint(randNum, firstRow, secondRow, firstColumn, secondColumn);

        if (!(field.at(firstRow).at(firstColumn) == '#' || field.at(firstRow).at(firstColumn) == '`'
            || field.at(secondRow).at(secondColumn) == '#' || field.at(secondRow).at(secondColumn) == '`'))
        {
            if ((abs(firstRow - secondRow) < 4 && abs(firstColumn - secondColumn) < 4) && (battleship < 1 || cruisers < 2 || submarines < 3 || destroyers < 4))
            {
                int beginRow = 0;
                int endRow = 0;
                int beginColumn = 0;
                int endColumn = 0;

                if (firstRow != secondRow && firstColumn == secondColumn)
                {
                    currentShipSize = abs(firstRow - secondRow) + 1;
                    switch (currentShipSize)
                    {
                    case 2:
                    {
                        if (submarines < 3)
                        {
                            submarines++;
                            HorizontalInputCheck(firstRow, secondRow, beginRow, endRow, firstColumn, beginColumn, secondColumn, endColumn);
                        }
                        break;
                    }
                    case 3:
                    {
                        if (cruisers < 2)
                        {
                            cruisers++;
                            HorizontalInputCheck(firstRow, secondRow, beginRow, endRow, firstColumn, beginColumn, secondColumn, endColumn);
                        }
                        break;
                    }
                    case 4:
                    {
                        if (battleship < 1)
                        {
                            battleship++;
                            HorizontalInputCheck(firstRow, secondRow, beginRow, endRow, firstColumn, beginColumn, secondColumn, endColumn);
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }
                else if (firstRow == secondRow && firstColumn != secondColumn)
                {
                    currentShipSize = abs(firstColumn - secondColumn) + 1;
                    switch (currentShipSize)
                    {
                    case 2:
                    {
                        if (submarines < 3)
                        {
                            submarines++;
                            VerticalInputCheck(firstColumn, secondColumn, firstRow, beginRow, secondRow, endRow, beginColumn, endColumn);
                        }
                        break;
                    }
                    case 3:
                    {
                        if (cruisers < 2)
                        {
                            cruisers++;
                            VerticalInputCheck(firstColumn, secondColumn, firstRow, beginRow, secondRow, endRow, beginColumn, endColumn);
                        }
                        break;
                    }
                    case 4:
                    {
                        if (battleship < 1)
                        {
                            battleship++;
                            VerticalInputCheck(firstColumn, secondColumn, firstRow, beginRow, secondRow, endRow, beginColumn, endColumn);
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }
                else if (firstRow == secondRow && firstColumn == secondColumn)
                {
                    if (destroyers < 4)
                    {
                        destroyers++;
                        //=============================
                        if (firstRow - 1 < 0)
                        {
                            beginRow = firstRow;
                        }
                        else
                        {
                            beginRow = firstRow - 1;
                        }
                        //=============================
                        if (secondRow + 2 > 10)
                        {
                            endRow = secondRow + 1;
                        }
                        else
                        {
                            endRow = secondRow + 2;
                        }
                        //=============================
                        //=============================
                        if (secondColumn - 1 < 0)
                        {
                            beginColumn = secondColumn;
                        }
                        else
                        {
                            beginColumn = secondColumn - 1;
                        }
                        //=============================
                        if (firstColumn + 2 > 10)
                        {
                            endColumn = firstColumn + 1;
                        }
                        else
                        {
                            endColumn = firstColumn + 2;
                        }
                        //=============================
                        for (int i = beginRow; i < endRow; i++)
                        {
                            for (int j = beginColumn; j < endColumn; j++)
                            {
                                if (i == secondRow && j == secondColumn)
                                    field.at(i).at(j) = '#';
                                else
                                    field.at(i).at(j) = '`';
                            }
                        }
                    }
                }
            }
            if (battleship == 1 && cruisers == 2 && submarines == 3 && destroyers == 4)
            {
                shipsArePlaced = true;
            }
        }
    }
}

//=============Ручное=============//
void Player::ManualFieldFilling(Player& secondPlayer)
{
    string point;

    int firstRow = 0;
    int firstColumn = 0;
    int secondRow = 0;
    int secondColumn = 0;

    int currentShipSize = 0;
    int battleship = 0; //4 палубный - 1
    int cruisers = 0; //3 палубный - 2
    int submarines = 0; //2 палубный - 3
    int destroyers = 0; //1 палубный - 4

    bool shipsArePlaced = false;

    while (!shipsArePlaced) {
        string textCorectCoordinatesInput = "\n\n\t\t\t\t\t\tEnter begin of your ship: ";
        CorectCoordinatesInput(textCorectCoordinatesInput, point, firstRow, firstColumn, secondPlayer);
        textCorectCoordinatesInput = "\n\n\t\t\t\t\t\tEnter end of your ship: ";
        CorectCoordinatesInput(textCorectCoordinatesInput, point, secondRow, secondColumn, secondPlayer);

        if (field.at(firstRow).at(firstColumn) == '#' || field.at(firstRow).at(firstColumn) == '`'
            || field.at(secondRow).at(secondColumn) == '#' || field.at(secondRow).at(secondColumn) == '`')
        {
            wcout << "\n\n\t\t\t\t\t\tERROR! This point of field is disable!\n\n";
            Sleep(1500);
        }
        else
        {
            if ((abs(firstRow - secondRow) < 4 && abs(firstColumn - secondColumn) < 4) && (battleship < 1 || cruisers < 2 || submarines < 3 || destroyers < 4))
            {
                int beginRow = 0;
                int endRow = 0;
                int beginColumn = 0;
                int endColumn = 0;

                if (firstRow != secondRow && firstColumn == secondColumn)
                {
                    currentShipSize = abs(firstRow - secondRow) + 1;
                    switch (currentShipSize)
                    {
                    case 2:
                    {
                        if (submarines < 3)
                        {
                            submarines++;
                            HorizontalInputCheck(firstRow, secondRow, beginRow, endRow, firstColumn, beginColumn, secondColumn, endColumn);
                        }
                        else
                        {
                            wcout << "\n\n\t\t\t\t\t\tERROR! You have all ships of this size you need!\n";
                            Sleep(1500);
                        }
                        break;
                    }
                    case 3:
                    {
                        if (cruisers < 2)
                        {
                            cruisers++;
                            HorizontalInputCheck(firstRow, secondRow, beginRow, endRow, firstColumn, beginColumn, secondColumn, endColumn);
                        }
                        else
                        {
                            wcout << "\n\n\t\t\t\t\t\tERROR! You have all ships of this size you need!\n";
                            Sleep(1500);
                        }
                        break;
                    }
                    case 4:
                    {
                        if (battleship < 1)
                        {
                            battleship++;
                            HorizontalInputCheck(firstRow, secondRow, beginRow, endRow, firstColumn, beginColumn, secondColumn, endColumn);
                        }
                        else
                        {
                            wcout << "\n\n\t\t\t\t\t\tERROR! You have all ships of this size you need!\n";
                            Sleep(1500);
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }
                else if (firstRow == secondRow && firstColumn != secondColumn)
                {
                    currentShipSize = abs(firstColumn - secondColumn) + 1;
                    switch (currentShipSize)
                    {
                    case 2:
                    {
                        if (submarines < 3)
                        {
                            submarines++;
                            VerticalInputCheck(firstColumn, secondColumn, firstRow, beginRow, secondRow, endRow, beginColumn, endColumn);
                        }
                        else
                        {
                            wcout << "\n\n\t\t\t\t\t\tERROR! You have all ships of this size you need!\n";
                            Sleep(1500);
                        }
                        break;
                    }
                    case 3:
                    {
                        if (cruisers < 2)
                        {
                            cruisers++;
                            VerticalInputCheck(firstColumn, secondColumn, firstRow, beginRow, secondRow, endRow, beginColumn, endColumn);
                        }
                        else
                        {
                            wcout << "\n\n\t\t\t\t\t\tERROR! You have all ships of this size you need!\n";
                            Sleep(1500);
                        }
                        break;
                    }
                    case 4:
                    {
                        if (battleship < 1)
                        {
                            battleship++;
                            VerticalInputCheck(firstColumn, secondColumn, firstRow, beginRow, secondRow, endRow, beginColumn, endColumn);
                        }
                        else
                        {
                            wcout << "\n\n\t\t\t\t\t\tERROR! You have all ships of this size you need!\n";
                            Sleep(1500);
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }
                else if (firstRow == secondRow && firstColumn == secondColumn)
                {
                    if (destroyers < 4)
                    {
                        destroyers++;
                        //=============================
                        if (firstRow - 1 < 0)
                        {
                            beginRow = firstRow;
                        }
                        else
                        {
                            beginRow = firstRow - 1;
                        }
                        //=============================
                        if (secondRow + 2 > 10)
                        {
                            endRow = secondRow + 1;
                        }
                        else
                        {
                            endRow = secondRow + 2;
                        }
                        //=============================
                        //=============================
                        if (secondColumn - 1 < 0)
                        {
                            beginColumn = secondColumn;
                        }
                        else
                        {
                            beginColumn = secondColumn - 1;
                        }
                        //=============================
                        if (firstColumn + 2 > 10)
                        {
                            endColumn = firstColumn + 1;
                        }
                        else
                        {
                            endColumn = firstColumn + 2;
                        }
                        //=============================
                        for (int i = beginRow; i < endRow; i++)
                        {
                            for (int j = beginColumn; j < endColumn; j++)
                            {
                                if (i == secondRow && j == secondColumn)
                                    field.at(i).at(j) = '#';
                                else
                                    field.at(i).at(j) = '`';
                            }
                        }
                    }
                    else
                    {
                        wcout << "\n\n\t\t\t\t\t\tERROR! You have all ships of this size you need!\n";
                        Sleep(1500);
                    }
                }
                else
                {
                    wcout << "\n\n\t\t\t\t\t\tERROR!" << endl << endl;
                    Sleep(1500);
                }
            }
            else
            {
                wcout << "\n\n\t\t\t\t\t\tERROR! Your ship is too big\n";
                Sleep(1500);
            }
            system("cls");
            if (battleship == 1 && cruisers == 2 && submarines == 3 && destroyers == 4)
            {
                shipsArePlaced = true;
            }
        }
    }
    PrintField(40, 1, PrintPlayerField);
    wcout << "\n\n\t\t\t\t\t\tAll ships are placed\n";
    Sleep(1500);
}

//========================Вспомогательные методы для заполнения поля===========================================================================================================================
//=====Проверка на размещение кораблей вертикально======
void Player::VerticalInputCheck(int firstColumn, int secondColumn, int firstRow, int& beginRow, int secondRow, int& endRow, int& beginColumn, int& endColumn)
{
    if (firstColumn < secondColumn)
    {
        //=============================
        if (firstRow - 1 < 0)
        {
            beginRow = firstRow;
        }
        else
        {
            beginRow = firstRow - 1;
        }
        //=============================
        if (secondRow + 2 > 10)
        {
            endRow = secondRow + 1;
        }
        else
        {
            endRow = secondRow + 2;
        }
        //=============================
        //=============================
        if (firstColumn - 1 < 0)
        {
            beginColumn = firstColumn;
        }
        else
        {
            beginColumn = firstColumn - 1;
        }
        //=============================
        if (secondColumn + 2 > 10)
        {
            endColumn = secondColumn + 1;
        }
        else
        {
            endColumn = secondColumn + 2;
        }
        //=============================
        for (int i = beginRow; i < endRow; i++)
        {
            for (int j = beginColumn; j < endColumn; j++)
            {
                if (i == secondRow && j >= firstColumn && j <= secondColumn)
                    field.at(i).at(j) = '#';
                else
                    field.at(i).at(j) = '`';
            }
        }
    }
    else
    {
        //=============================
        if (firstRow - 1 < 0)
        {
            beginRow = firstRow;
        }
        else
        {
            beginRow = firstRow - 1;
        }
        //=============================
        if (secondRow + 2 > 10)
        {
            endRow = secondRow + 1;
        }
        else
        {
            endRow = secondRow + 2;
        }
        //=============================
        //=============================
        if (secondColumn - 1 < 0)
        {
            beginColumn = secondColumn;
        }
        else
        {
            beginColumn = secondColumn - 1;
        }
        //=============================
        if (firstColumn + 2 > 10)
        {
            endColumn = firstColumn + 1;
        }
        else
        {
            endColumn = firstColumn + 2;
        }
        //=============================
        for (int i = beginRow; i < endRow; i++)
        {
            for (int j = beginColumn; j < endColumn; j++)
            {
                if (i == secondRow && j >= secondColumn && j <= firstColumn)
                    field.at(i).at(j) = '#';
                else
                    field.at(i).at(j) = '`';
            }
        }
    }
}

//=====Проверка на размещение кораблей горизонтально=====//
void Player::HorizontalInputCheck(int firstRow, int secondRow, int& beginRow, int& endRow, int firstColumn, int& beginColumn, int secondColumn, int& endColumn)
{
    if (firstRow < secondRow)
    {
        //=============================
        if (firstRow - 1 < 0)
        {
            beginRow = firstRow;
        }
        else
        {
            beginRow = firstRow - 1;
        }
        //=============================
        if (secondRow + 2 > 10)
        {
            endRow = secondRow + 1;
        }
        else
        {
            endRow = secondRow + 2;
        }
        //=============================
        //=============================
        if (firstColumn - 1 < 0)
        {
            beginColumn = firstColumn;
        }
        else
        {
            beginColumn = firstColumn - 1;
        }
        //=============================
        if (secondColumn + 2 > 10)
        {
            endColumn = secondColumn + 1;
        }
        else
        {
            endColumn = secondColumn + 2;
        }
        //=============================

        for (int i = beginRow; i < endRow; i++)
        {
            for (int j = beginColumn; j < endColumn; j++)
            {
                if (i >= firstRow && i <= secondRow && j == firstColumn)
                    field.at(i).at(j) = '#';
                else
                    field.at(i).at(j) = '`';
            }
        }
    }
    else
    {
        //=============================
        if (secondRow - 1 < 0)
        {
            beginRow = secondRow;
        }
        else
        {
            beginRow = secondRow - 1;
        }
        //=============================
        if (firstRow + 2 > 10)
        {
            endRow = firstRow + 1;
        }
        else
        {
            endRow = firstRow + 2;
        }
        //=============================
        //=============================
        if (firstColumn - 1 < 0)
        {
            beginColumn = firstColumn;
        }
        else
        {
            beginColumn = firstColumn - 1;
        }
        //=============================
        if (secondColumn + 2 > 10)
        {
            endColumn = secondColumn + 1;
        }
        else
        {
            endColumn = secondColumn + 2;
        }
        //=============================

        for (int i = beginRow; i < endRow; i++)
        {
            for (int j = beginColumn; j < endColumn; j++)
            {
                if (i >= secondRow && i <= firstRow && j == firstColumn)
                    field.at(i).at(j) = '#';
                else
                    field.at(i).at(j) = '`';
            }
        }
    }
}

//==========Метод создания случайных точек начала и конца корабля============//
void Player::RandomPoint(int& randNum, int& firstRow, int& secondRow, int& firstColumn, int& secondColumn)
{
    if (randNum % 2 == 0)
    {
        firstRow = rand() % 10;
        secondRow = firstRow;
        firstColumn = rand() % 10;
        secondColumn = rand() % 10;

        randNum = rand() % 10 + 1;
    }
    else
    {
        firstColumn = rand() % 10;
        secondColumn = firstRow;
        firstRow = rand() % 10;
        secondRow = rand() % 10;

        randNum = rand() % 10 + 1;
    }
}
//===============Метод для ввода координат с зашитой от дурака==============================================================================================
void Player::CorectCoordinatesInput(std::string& beginPointInputText, std::string& point, int& firstRow, int& firstColumn, Player& secondPlayer)
{
    COORD position; //позиция x и y
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    bool isSuccessInput = false;
    do
    {
        system("cls");

        position = { 40, 0 };
        SetConsoleCursorPosition(hConsole, position);
        wcout << "Your field\n";
        PrintField(40, 1, PrintPlayerField);

        position = { 130, 0 };
        SetConsoleCursorPosition(hConsole, position);
        wcout << "Enemy field\n";
        secondPlayer.PrintField(130, 1, PrintEnemyField);

        wcout << endl << endl;
        wcout << "\t\t\t\t\t\t" <<beginPointInputText.c_str();
        cin >> point;
        cin.ignore();

        if ((point[0] < 65 || point[0] > 74) || point.size() > 3)
        {
            wcout << "\t\t\t\t\t\tERROR. Wrong input\n\n";
            system("pause");
            system("cls");
        }
        else
        {
            firstRow = point[0] - 65;
            point[0] = '0';
            firstColumn = (atoi(point.c_str())) - 1;
            if (firstColumn >= 0 && firstColumn < 10)
            {
                isSuccessInput = true;
            }
            else
            {
                wcout << "\t\t\t\t\t\tERROR. Wrong input\n\n";
                system("pause");
            }
        }
    } while (!isSuccessInput);
}
//=====================Стрельба (авто и ручная)================================================================================================================================================
//============Авто=========//
void Player::AutoShooting(Player& enemy)
{
    int pointRow = 0;
    int pointColumn = 0;

    bool newFirePosition = false;
    do
    {
        pointRow = rand() % 10;
        pointColumn = rand() % 10;
        if (enemy.field.at(pointRow).at(pointColumn) != 'X' && enemy.field.at(pointRow).at(pointColumn) != 'O')
        {
            newFirePosition = true;
        }
    } while (!newFirePosition);
    if (enemy.field.at(pointRow).at(pointColumn) == '#')
    {
        enemy.field.at(pointRow).at(pointColumn) = 'X';
        enemy.healPoints--;
    }
    else
    {
        enemy.field.at(pointRow).at(pointColumn) = 'O';
    }
        
}

//============Ручная=========//
void Player::ManualShooting(Player& enemy)
{
    string point;
    int pointRow = 0;
    int pointColumn = 0;

    string textCorectCoordinatesInput = "Enter fire point: ";
    CorectCoordinatesInput(textCorectCoordinatesInput, point, pointRow, pointColumn, enemy);

    if (enemy.field.at(pointRow).at(pointColumn) == '#')
    {
        enemy.field.at(pointRow).at(pointColumn) = 'X';
        enemy.healPoints--;
    }
    else
    {
        enemy.field.at(pointRow).at(pointColumn) = 'O';
    }
}

//==================Функции которые используются в качестве параметра методу PrintField класса Player, для отображения поля===========================================================================
void PrintPlayerField(int& i, int& j, std::vector<std::vector<char>>& field)
{
    if ((j + 1) % 4 == 0)
        wcout << field[i][(j - 1) / 4];
    else
        wcout << ' ';
}

void PrintEnemyField(int& i, int& j, std::vector<std::vector<char>>& field)
{
    if ((j + 1) % 4 == 0)
        if (field[i][(j - 1) / 4] != '#' && field[i][(j - 1) / 4] != '`')
            wcout << field[i][(j - 1) / 4];
        else
            wcout << ' ';
    else
        wcout << ' ';
}
//================================================================================================================================================================================================