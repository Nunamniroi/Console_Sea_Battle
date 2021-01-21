#pragma once
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <algorithm>
#include <vector>
#include <ctime>
#include <random>
#include <windows.h>

using namespace std;

class Player
{
	vector<vector<char>> field;
	int healPoints;
public:
	Player();

	int getHealPoints();

	//===================Отображение игрового поля================================================================================================================================================
	void PrintField(const int& x, const int& y, void(*function)(int& i, int& j, std::vector<std::vector<char>>& field));


	//===================Заполнение игрового поля (автоматическое и ручное)========================================================================================================================
	//=============Автоматическое=============//
	void AutoFieldFilling();

	//=============Ручное=============//
	void ManualFieldFilling(Player& secondPlayer);

	//========================Вспомогательные методы для заполнения поля===========================================================================================================================
	//=====Проверка на размещение кораблей вертикально======//
	void VerticalInputCheck(int firstColumn, int secondColumn, int firstRow, int& beginRow, int secondRow, int& endRow, int& beginColumn, int& endColumn);

	//=====Проверка на размещение кораблей горизонтально=====//
	void HorizontalInputCheck(int firstRow, int secondRow, int& beginRow, int& endRow, int firstColumn, int& beginColumn, int secondColumn, int& endColumn);

	//==========Метод создания случайных точек начала и конца корабля============//
	void RandomPoint(int& randNum, int& firstRow, int& secondRow, int& firstColumn, int& secondColumn);


	//===============Метод для ввода координат с зашитой от дурака================================================================================================================================
	void CorectCoordinatesInput(std::string& beginPointInputText, std::string& point, int& firstRow, int& firstColumn, Player& secondPlayer);


	//=====================Стрельба (авто и ручная)================================================================================================================================================
	//============Авто=========//
	void AutoShooting(Player& enemy);

	//============Ручная=========//
	void ManualShooting(Player& enemy);
};

void PrintPlayerField(int& i, int& j, std::vector<std::vector<char>>& field);

void PrintEnemyField(int& i, int& j, std::vector<std::vector<char>>& field);