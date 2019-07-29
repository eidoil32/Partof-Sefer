#pragma once
#pragma warning(disable:4996)

#include "Fanlists.h"
#include "Members.h"
#include "Services.h"
#include "Date.h"
#include "Menu.h"
#include <list>
#include <vector>

const int EMPTYARRAY = 0, INT_TRUE = 1, INT_FALSE = 0, BASE_SIZE = 2, SMALL_MENU_SIZE_TO = 3;
const char YES_UPPERCASE = 'Y', YES_LOWERCASE = 'y';
const bool TYPE_FANLIST = 1, TYPE_MEMBER = 0;

void Database(vector<User*>&userArray, int &countMember, int &countFanpage);

void getFullDate(int &day, int &month, int &year);

//TEXT will go in to cout << TEXT
#define ERROR_COMMAND(TEXT)					setTextColor(Color::LIGHTRED);\
											cout << TEXT; \
											setTextColor(Color::WHITE);
//TEXT will go in to cout << TEXT
#define SUCCESS_COMMAND(TEXT)				setTextColor(Color::LIGHTGREEN);\
											cout << TEXT; \
											setTextColor(Color::WHITE);

#define COMMAND_RETURN_TO_MENU				{setTextColor(Color::LIGHTGREY);\
											cout << "press any key to return to main menu\n";\
											char anykey = getch();\
											setTextColor(Color::WHITE);}


#define TYPEID_CHECK(x,y) (typeid((x)) == typeid(y))
#define CHECK_CHOOSE(x,y) (choose > x && typeid(target) == typeid(y))
#define COUT_M_OR_F	(type ? "Fanlist" : "Member") // shortcut for cout member or fanlist based on bool 'type'

//will active 'func' function based on user choice
#define CHOOSE_BETWEEN_M_O_F(func,menu) 		if (newChoice == 1) \
													func(TYPE_MEMBER); \
												else if (newChoice == 2) \
													func(TYPE_FANLIST); \
												else if (newChoice == 3) \
													return; \
												else \
												{ \
														cout << "Wrong number, Please select one of those options:\n"; \
														doWhatUserAsk(menu); \
												} 

class Facebook
{
private:
	Menu mainmenu;
    int countMember, countFanpage;
	vector<User*> userArray;
    Facebook( const Facebook& facebook);
public:
    Facebook();
    ~Facebook();

	void start();
	int printmainmenu() { return mainmenu.printMenu(); }
    void doWhatUserAsk(int choice);
    void addNewUser(bool type);
    void AddStatus(bool type);
	void MakeNewBonding(bool type);
	void checkStatus()						const;
    void ShowStatus(bool type)				const;
    void ShowAllMembersAndFanlists()		const;
    void ShowAllFriends(bool type)			const;	
	void WhoHaveBigger()					const;
    void showRecentStatus()					const;
	vector<User*>showUsers(User *except, bool flag, User **target) const;
};