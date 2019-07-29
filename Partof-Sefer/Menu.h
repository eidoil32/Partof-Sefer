#pragma once
#pragma warning(disable:4996)
#include <iostream>
using namespace std;
			
#include <vector>
#include <string>
#include "io_utils.h"

constexpr auto	MENU_OPTION_1 = "Add friend",MENU_OPTION_2 = "Add fanlist", MENU_OPTION_3 = "Add status to friend\\fanlist",
				MENU_OPTION_4 = "Show all friend\\fanlist status",MENU_OPTION_5 = "Make friend connection",
				MENU_OPTION_6 = "Add a fan to fanlist",MENU_OPTION_7 = "Show all friends and fanlists",
				MENU_OPTION_8 = "Show all friend's friends or fanlist's fans",MENU_OPTION_9 = "Compare who is the coolest", 
				MENU_OPTION_10 = "Show recent status", MENU_OPTION_11 = "Compare between status", 
				MENU_OPTION_12 = "Save or Load Database" , MENU_OPTION_13 = "exit";

const char MENU_FIRST_LETTER_UPPERCASE = 'A', MENU_FIRST_LETTER_LOWERCASE = 'a', MENU_LAST_LETTER_UPPERCASE = 'D', MENU_LAST_LETTER_LOWERCASE = 'd';

const int   MENU_PAGE_ADD_MEMBER = 1, MENU_ADD_FANPAGE = 2,
			MENU_PAGE_ADD_STATUS = 3, MENU_PAGE_ALL_USER_STATUS = 4,
			MENU_PAGE_BONDING = 5, MENU_PAGE_ADD_MEMBER_TO_FANPAGE = 6,
			MENU_PAGE_SHOW_ALL = 7, MENU_PAGE_FRIEND_S_FRIENDS = 8, MENU_PAGE_COMPARE_STATUS = 11,
			MENU_PAGE_EXIT = 13, MENU_PAGE_RECENT = 10, MENU_PAGE_SAVE_OR_LOAD_DATABASE = 12, MENU_CHECK_WHO_HAVE_BIGGER = 9, SELECT_NONE =-1,
			UP_KEY = 72, DOWN_KEY = 80, LEFT_KEY = 75, RIGHT_KEY = 77, ENTER_KEY = 13, EXIT_KEY = 27,
			END_OF_MENU = 13, START_OF_MENU = 1, MENU_LINE_SIZE = 80, CORD_X_Y_SIZE = 13, MENU_OPTIONS_SIZE = 13, SPEED_LOGO = 60;

const int	SMALL_MENU_SIZE = 3, MAX_STRING_SIZE = 50; //for small menu only

int smallMenu(char(&arr)[5][MAX_STRING_SIZE], int size, int currentChoice);

class Menu
{
private:
	int select;
	int x[CORD_X_Y_SIZE], y[CORD_X_Y_SIZE], startX, startY;
	vector<string> menuOptionsArray;
	bool firstTime;
public:
	Menu();
	int printMenu();
	void printWhiteMenu(int except);
	void PrintSelectable(int select);
};