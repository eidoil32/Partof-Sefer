#include "Menu.h"

Menu::Menu()
{
	select = 1;
	startX = 0;
	firstTime = true;
	startY = 8;
	for (int i = 0; i < CORD_X_Y_SIZE; i++)
		y[i] = i + 8;
	for (int i = 0; i < CORD_X_Y_SIZE; i++)
		x[i] = 0;

	menuOptionsArray.reserve(MENU_OPTIONS_SIZE);

	menuOptionsArray.push_back(MENU_OPTION_1);
	menuOptionsArray.push_back(MENU_OPTION_2);
	menuOptionsArray.push_back(MENU_OPTION_3);
	menuOptionsArray.push_back(MENU_OPTION_4);
	menuOptionsArray.push_back(MENU_OPTION_5);
	menuOptionsArray.push_back(MENU_OPTION_6);
	menuOptionsArray.push_back(MENU_OPTION_7);
	menuOptionsArray.push_back(MENU_OPTION_8);
	menuOptionsArray.push_back(MENU_OPTION_9);
	menuOptionsArray.push_back(MENU_OPTION_10);
	menuOptionsArray.push_back(MENU_OPTION_11);
	menuOptionsArray.push_back(MENU_OPTION_12);
	menuOptionsArray.push_back(MENU_OPTION_13);
}

void printLogo(bool firstTime)
{
	int x, y, n, speed = (firstTime ? SPEED_LOGO : 0);
	setTextColor(Color::CYAN);
	if (firstTime == true)
	{ x = 0; y = 18; n = 10; }
	else
	{ x = 9; y = 9; n = 10; }
	for (int i = x, j = y; i < n; i++, j--)
	{
		clear_screen();
		gotoxy(i, 0);
		cout << R"(MMMMMM   MMMMMM  MMMMMM?      .MMMMMM  MMM. MMM  MM=.MMMMMM  ZMMMMM )";
		gotoxy(j, 1);
		cout << R"(     M   M    M   M   MI       M   =M    M    M   M       M  DM   M.)";
		gotoxy(i, 2);
		cout << R"(     M   M    M   M   MI       M   =M    M    .M.M        M  DM   M.)";
		gotoxy(j, 3);
		cout << R"(     M   MMM  M   M   MI       MMM =M    M      MM        M   MMM M.)";
		gotoxy(i, 4);
		cout << R"(     M        M   M   M?           =M    M       .M       M       M.)";
		gotoxy(j, 5);
		cout << R"(     M   MMMMM=   +MMMM            =M    M  MMMMMMM.      M   MMMMM.)";
		gotoxy(i, 6);
		cout << R"(                                   =M                               )";
		cout << endl << endl;
		Sleep(speed);
	}

	setTextColor(Color::WHITE);
}

void printChoice(int select,bool firstTime)
{
	printLogo(firstTime);
	switch (select)
	{
	case MENU_PAGE_ADD_MEMBER:
		cout << "Menu: Add Friend\nHere you can add here a new friend to the system.\n";
		break;
	case MENU_ADD_FANPAGE:
		cout << "Menu: Add Fan list\nHere you can add here a new Fan list to the system.\n";
		break;
	case MENU_PAGE_ADD_STATUS:
		cout << "Menu: Add status to friend\\fanlist\nHere you can post a new status for any friend\\fanlist\n";
		break;
	case MENU_PAGE_ALL_USER_STATUS:
		cout << "Menu: Show all friend\\fanlist status\nHere you can see what friend or fanlist publish\n";
		break;
	case MENU_PAGE_BONDING:
		cout << "Menu: Make friend connection\nHere you can make new friendship!\n";
		break;
	case MENU_PAGE_ADD_MEMBER_TO_FANPAGE:
		cout << "Menu: Add a fan to fanlist\nHere you can add new fans to any fanlist\n";
		break;
	case MENU_PAGE_SHOW_ALL:
		cout << "Menu: Show all friends and fanlists\nHere you can see who is sign to out system\n";
		break;
	case MENU_PAGE_FRIEND_S_FRIENDS:
		cout << "Menu: Show all friend's friends or fanlist's fans\nHere you can see who friend of and member or fanlist\n";
		break;
	case MENU_PAGE_SAVE_OR_LOAD_DATABASE:
		cout << "Menu: Save Facebook database to text file\nHere you can save all data of facebook like users and status to text file\n";
		break;
	case MENU_PAGE_EXIT:
		clear_screen();
		setTextColor(Color::CYAN);
		cout << R"(
	 %MMMMMMM   MMMMMMMM    MMMMMMMM   MMMMMMMM      MMMMMMM (MM   MM. /MMMMMM                          
	MM(        MM/    &MM  MM/    &MM  MM    %MM     MM   MM   MM MM   /MM                              
	MM   *MMM *MM      MM *MM      MM  MM     MM     MMMMMM/    MMM    /MMMMM                           
	MM/    MM  MM(    &MM  MM(    &MM  MM    MM%     MM   MM*   MM(    /MM                              
	 MMMMMMMM   MMMMMMM&    MMMMMMM&   MMMMMMM       MMMMMMM    MM(    /MMMMMM   
)" << endl;
		Sleep(1000);
		setTextColor(Color::WHITE);
		break;
	case MENU_PAGE_RECENT:
		cout << "Menu: Show recent status\nHere you can see the recent status of any friend of friend\n";
		break;
	case MENU_CHECK_WHO_HAVE_BIGGER:
		cout << "Menu: Compare who is the coolest\nNew option! Now you can check who is the collest member in the system!\n" <<
			"Please choose the type of user you want to compare : \n";
		break;
	case MENU_PAGE_COMPARE_STATUS:
		cout << "Menu: Compare between two status\nNew option! Now you can check if two status is the same!\n"
			<< "Please choose the type of user you want to compare:\n";
		break;
	default:
		break;
	}
	for (int i = 0; i < MENU_LINE_SIZE; i++)
		cout << "_";
	cout << endl;
}

int Menu::printMenu()
{
	bool Enter = false;
	char choose;
	int oldSelect = 0;

	ShowConsoleCursor(false);
	clear_screen();

	printLogo(firstTime);
	firstTime = false;

	printWhiteMenu(SELECT_NONE);
	cin.clear();
	while (!Enter)
	{
		if (select != oldSelect)
			PrintSelectable(select);
		oldSelect = select;
		if (_kbhit())
		{
			choose = getch();
			if (choose > '0' && choose <= '9' )
			{
				clear_screen();
				printChoice(choose - '0', firstTime);
				ShowConsoleCursor(true);
				return choose - '0';
			}
			if((choose >= MENU_FIRST_LETTER_UPPERCASE && choose <= MENU_LAST_LETTER_UPPERCASE) ||
				(choose >= MENU_FIRST_LETTER_LOWERCASE && choose <= MENU_LAST_LETTER_LOWERCASE))
			{
				if ((choose >= MENU_FIRST_LETTER_UPPERCASE && choose <= MENU_LAST_LETTER_UPPERCASE))
					select = choose - MENU_FIRST_LETTER_UPPERCASE + 10;
				else
					select = choose - MENU_FIRST_LETTER_LOWERCASE + 10;
				clear_screen();
				printChoice(select, firstTime);
				ShowConsoleCursor(true);
				return (select);
			}
			if (choose == ENTER_KEY)
			{
				clear_screen();
				printChoice(select, firstTime);
				ShowConsoleCursor(true);
				return select;
			}
			if (choose == EXIT_KEY)
			{
				printChoice(MENU_PAGE_EXIT, false);
				return MENU_PAGE_EXIT;
			}
			if (choose == UP_KEY)
				if(select != START_OF_MENU)
					select--;
			if (choose == DOWN_KEY)
				if (select != END_OF_MENU)
					select++;
		}
	}

	select = 0;
	return 0;
}

void Menu::printWhiteMenu(int except)
{
	for (int i = 0; i < MENU_OPTIONS_SIZE; i++)
	{
		if (except != (i + 1))
		{
			gotoxy(x[i], y[i]);
			if (i + 1 >= 10)
				cout << "[" << (char)(i + MENU_FIRST_LETTER_UPPERCASE - 9) << "] ";
			else
				cout << "[" << i + 1 << "] ";
			cout << menuOptionsArray[i];
		}
	}
}

void Menu::PrintSelectable(int select)
{
	setTextColor(Color::LIGHTCYAN);

	gotoxy(x[select - 1], y[select - 1]);
	if (select >= 10)
		cout << "[" << (char)(select+ MENU_FIRST_LETTER_UPPERCASE -10) << "] ";
	else
		cout << "[" << select << "] ";
	cout << menuOptionsArray[select - 1];

	setTextColor(Color::WHITE);
	printWhiteMenu(select);
}

int smallMenu(char(&arr)[5][MAX_STRING_SIZE], int size, int currentChoice)
{
	bool finish = false;
	int choice = 1, oldchoice = 1, startY;
	char ch;

	if (currentChoice == MENU_CHECK_WHO_HAVE_BIGGER || currentChoice == MENU_PAGE_COMPARE_STATUS)
		startY = 12;
	else
		startY = 11;

	clear_screen();
	printChoice(currentChoice, false);
	ShowConsoleCursor(false);

	for (int i = 0; i < size; i++)
	{
		if (choice == i+1)
			setTextColor(Color::LIGHTCYAN);
		else
			setTextColor(Color::WHITE);
		cout << arr[i] << endl;
	}

	while (!finish)
	{
		if (_kbhit())
		{
			ch = getch();
			if (ch <= (size + '0') && ch >= '1')
			{
				ShowConsoleCursor(true);
				return ch -'0';
			}
			if (ch == ENTER_KEY)
			{
				ShowConsoleCursor(true);
				return choice;
			}
			if (ch == UP_KEY)
				if (choice != 1)
					choice--;
			if (ch == DOWN_KEY)
				if (choice != size)
					choice++;
		}
		if (choice != oldchoice)
		{
			gotoxy(0, startY);
			for (int i = 0; i < size; i++)
			{
				if (choice == i + 1)
					setTextColor(Color::LIGHTCYAN);
				else
					setTextColor(Color::WHITE);
				cout << arr[i] << endl;
			}
			setTextColor(Color::WHITE); //if i was in last choice
		}
		oldchoice = choice;
	}
	cin.ignore();
	return size;
}