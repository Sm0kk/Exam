#pragma once
#include<fstream>
#include<vector>
#include<iostream>
#include <string>
#include<list>
#include<windows.h>
#include<iomanip>
#include<map>
#include<algorithm>
using namespace std;

enum Choice
{
	USERMODE = 1, ADMINMODE, LOGINUSER = 1, REGISTERUSER, CHANGE_LOGIN_PASSWORD = 1, SAVE_LOAD_DATA, RETURNTOMAIN, EXIT = 3, USER_MANAGEMENT=3, VIEW_STAT, TEST_MANAGEMENT, PREV_MENU_2
};

string adminPath = "Admin.dat";
string usersPath = "Users.dat";
string userTestRes = "UserTestRes.bin";
string test1 = "Discrete_Mathematics.bin";
string test2 = "Mathematical_analysis.bin";
string test3 = "Quantum_physics.bin";
string test4 = "Mechanics.bin";

string encrypt(string data)
{
	for (size_t i = 0; i < data.size(); i++)
	{
		data[i] += 3;
	}
	return data;
}
string decipher(string data)
{
	for (size_t i = 0; i < data.size(); i++)
	{
		data[i] -= 3;
	}
	return data;
}
int menu3_user()
{
	int choice;
	bool goodChoice = true;
	while (goodChoice) {
	cout << "1 - View your previous tests results\n2 - Take a new test\n0 - Return to previous menu\n: ";
	cin >> choice;
	if (choice > -1 && choice < 3)
	{
		return choice;
	}
	cout << "Bad choice. try again\n";
	}
}

int menu_message(string message, int i)
{
	bool goodChoice = true;
	int choice;
	while (goodChoice) {
		cout << message << endl;
		cin >> choice;
		if (choice > 0 && choice < i)
		{
			return choice;
		}
		cout << "Bad choice. try again\n";
	}
}