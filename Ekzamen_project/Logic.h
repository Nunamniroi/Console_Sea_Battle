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

	//===================����������� �������� ����================================================================================================================================================
	void PrintField(const int& x, const int& y, void(*function)(int& i, int& j, std::vector<std::vector<char>>& field));


	//===================���������� �������� ���� (�������������� � ������)========================================================================================================================
	//=============��������������=============//
	void AutoFieldFilling();

	//=============������=============//
	void ManualFieldFilling(Player& secondPlayer);

	//========================��������������� ������ ��� ���������� ����===========================================================================================================================
	//=====�������� �� ���������� �������� �����������======//
	void VerticalInputCheck(int firstColumn, int secondColumn, int firstRow, int& beginRow, int secondRow, int& endRow, int& beginColumn, int& endColumn);

	//=====�������� �� ���������� �������� �������������=====//
	void HorizontalInputCheck(int firstRow, int secondRow, int& beginRow, int& endRow, int firstColumn, int& beginColumn, int secondColumn, int& endColumn);

	//==========����� �������� ��������� ����� ������ � ����� �������============//
	void RandomPoint(int& randNum, int& firstRow, int& secondRow, int& firstColumn, int& secondColumn);


	//===============����� ��� ����� ��������� � ������� �� ������================================================================================================================================
	void CorectCoordinatesInput(std::string& beginPointInputText, std::string& point, int& firstRow, int& firstColumn, Player& secondPlayer);


	//=====================�������� (���� � ������)================================================================================================================================================
	//============����=========//
	void AutoShooting(Player& enemy);

	//============������=========//
	void ManualShooting(Player& enemy);
};

void PrintPlayerField(int& i, int& j, std::vector<std::vector<char>>& field);

void PrintEnemyField(int& i, int& j, std::vector<std::vector<char>>& field);