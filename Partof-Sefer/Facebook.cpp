#include <iostream>
using namespace std;

#include "Facebook.h"
#include "Services.h"

Facebook::Facebook()
{
	countMember = countFanpage = EMPTYARRAY;
	userArray.reserve(BASE_SIZE);
}

Facebook::~Facebook()
{
	int size = userArray.size();
	for (int i = 0; i < size; i++)
		delete userArray[i];
}

void Facebook::start()
{
	int userChoice;
	do {
		userChoice = printmainmenu();
		doWhatUserAsk(userChoice);
	} while (userChoice != MENU_PAGE_EXIT);
}

//type : 0- member, 1 - fanlist
void Facebook::addNewUser(bool type)
{
	string name;
	char ch;
	int day, month, year;
	User *newUser;

	do {
		cout << COUT_M_OR_F << " name (end with enter):\n";
		getline(cin, name);
		while(name == "")
			getline(cin, name);

		if (checkNameAlreadyExist(name, userArray, type) == INT_TRUE)
		{
			throw("User already exist!\n");
		}
		else
		{
			if (type) // user is fanlist
			{
				newUser = new Fanlist(name);
				countFanpage++;
			}
			else // user is member
			{
				cout << "Enter birthday (DD\\MM\\YYYY):\n";
				getFullDate(day, month, year);

				while ((day < 0 || day > MAX_DAY) || (month < 0 || month > MAX_MONTH) || (year < 1000 || year > CURRENT_YEAR))
				{
					cout << "You entered invaild date, please enter an vaild date (DD\\MM\\YYYY):\n";
					getFullDate(day, month, year);
				}
				Date birthday(day, month, year);
				newUser = new member(name, birthday);
				countMember++;
			}

			if (userArray.capacity() == userArray.size())
			{
				try {
					userArray.reserve(userArray.capacity() * 2);
				}
				catch (...)
				{
					delete newUser;
					throw("Unknown Error! Adding new user failed.");
				}
			}

			userArray.push_back(newUser);
			SUCCESS_COMMAND(COUT_M_OR_F << " added successfully!\n")
		}
		cout << "\nDo you want enter another " << COUT_M_OR_F << "? press Y\\N \n";
		ch = getch();
	} while (ch == YES_UPPERCASE || ch == YES_LOWERCASE);
}

void Facebook::AddStatus(bool type)
{
	User *target = nullptr;
	if ((type ? countFanpage : countMember) == 0)
		throw("There are not any " + (string)COUT_M_OR_F + " in database!!\n");
	else
	{
		cout << "Please choose which user want to post a status (write his number):\n";
		showUsers(nullptr, type, &target);
		target->poststatus();
	}
}

void Facebook::ShowStatus(bool type) const
{
	User *target = nullptr;

	if ((!type && countMember == 0) || (type && countFanpage == 0))
		throw("There are not any " + (string)COUT_M_OR_F + " in database!!\n");
	else
	{
		showUsers(nullptr, type, &target);
		target->printAllStatus();
	}
}

void Facebook::ShowAllFriends(bool type) const
{
	User *target = nullptr;
	if ((type ? countFanpage : countMember) == 0)
		throw("There are not any " + (string)COUT_M_OR_F + " in database!!\n");
	else
	{
		showUsers(nullptr, type, &target);
		target->printAllUsers();
	}
}

void Facebook::WhoHaveBigger() const
{
	User *request = nullptr, *requested = nullptr;
	int choose;
	bool type;
	char arr[5][50] = { "[1] Friend", "[2] Fanlist" , "[3] Return to main menu" };
	if (userArray.size() < 2)
		throw("Don't have enough users to check who has more friends\n");
	else
	{
		cout << "Please choose the type of user you want to compare:\n";
		choose = smallMenu(arr, 3, MENU_CHECK_WHO_HAVE_BIGGER);
		if (choose == 3)
			return;
		type = (choose == 2 ? TYPE_FANLIST : TYPE_MEMBER);
		if ((!type && countMember < 2) || (type  && countFanpage < 2))
			throw("there are no one to compare with\n");
		cout << "Please choose which user number one:\n";
		showUsers(nullptr, type, &request);

		cout << "Please choose which user number two:\n";
		showUsers(request, type, &requested);

		cout << request->getname() << " has " <<
			((*request > *requested) ? "more friends than " : ((*requested > *request) ? "less friends than " : "same number of friends as "))
			<< requested->getname() << endl;
	}
}

void Facebook::doWhatUserAsk(int userChoice)
{
	int newChoice;
	bool exitProg = false;
	char arr[5][50] = { "[1] Show all friends's friends and fanlists","[2] Show all Fanlist's fans","[3] Back to main menu\n" };
	char arrTwo[5][50] = { "[1] Add status for a friend","[2] Add new status for Fanlist","[3] Back to main menu\n" };
	char arrThree[5][50] = { "[1] Show status for a friend","[2] Show status for a Fanlist","[3] Back to main menu\n" };

	try {
		switch (userChoice)
		{
		case MENU_PAGE_ADD_MEMBER:
			addNewUser(TYPE_MEMBER);
			break;
		case MENU_ADD_FANPAGE:
			addNewUser(TYPE_FANLIST);
			break;
		case MENU_PAGE_ADD_STATUS:
			newChoice = smallMenu(arrTwo, SMALL_MENU_SIZE_TO, MENU_PAGE_ADD_STATUS);
			CHOOSE_BETWEEN_M_O_F(AddStatus, MENU_PAGE_ADD_STATUS)
			break;
		case MENU_PAGE_ALL_USER_STATUS:
			newChoice = smallMenu(arrThree, SMALL_MENU_SIZE_TO, MENU_PAGE_ALL_USER_STATUS);
			CHOOSE_BETWEEN_M_O_F(ShowStatus, MENU_PAGE_ALL_USER_STATUS)
			break;
		case MENU_PAGE_BONDING:
			MakeNewBonding(TYPE_MEMBER);
			break;
		case MENU_PAGE_ADD_MEMBER_TO_FANPAGE:
			MakeNewBonding(TYPE_FANLIST);
			break;
		case MENU_PAGE_SHOW_ALL:
			ShowAllMembersAndFanlists();
			break;
		case MENU_PAGE_FRIEND_S_FRIENDS:
			newChoice = smallMenu(arr, SMALL_MENU_SIZE_TO, MENU_PAGE_FRIEND_S_FRIENDS);
			CHOOSE_BETWEEN_M_O_F(ShowAllFriends, MENU_PAGE_FRIEND_S_FRIENDS)
			break;
		case MENU_PAGE_EXIT:
			return;
			break;
		case MENU_PAGE_RECENT:
			showRecentStatus();
			break;
		case MENU_CHECK_WHO_HAVE_BIGGER:
			WhoHaveBigger();
			break;
		case MENU_PAGE_COMPARE_STATUS:
			checkStatus();
			break;
		case MENU_PAGE_SAVE_OR_LOAD_DATABASE:
			Database(userArray,countMember,countFanpage);
			break;
		default:
			ERROR_COMMAND("Wrong number, Please select one of the options above!\n")
			newChoice = cinInt();
			doWhatUserAsk(newChoice);
			break;
		}
	}
	catch (const char * msg)
	{
		ERROR_COMMAND(msg);
	}
	catch (string msg)
	{
		ERROR_COMMAND(msg);
	}
	catch (exception error)
	{
		ERROR_COMMAND(error.what());
	}
	catch (...)
	{
		ERROR_COMMAND("Unknown Error!\n");
	}
	COMMAND_RETURN_TO_MENU
}

void Facebook::checkStatus() const 
{
	User *request = nullptr;
	status *compareOne, *compareTwo;
	int choose, chooseAnother;
	bool type, enoughStatus = false;
	char arr[5][50] = { "[1] Friend","[2] Fanlist", "[3] Return main menu" };

	if (userArray.size() < 1)
		throw("There are no enough users to check who has more friends\n");
	else
	{
		choose = smallMenu(arr, 3, MENU_PAGE_COMPARE_STATUS);
		if (choose == 3)
			return;
		else
			type = (choose == 1 ? TYPE_MEMBER : TYPE_FANLIST);
		if ((type == TYPE_MEMBER && countMember < 1) || (type == TYPE_FANLIST && countFanpage < 1))
			throw("There are no any users in database\n");
		else
		{
			cout << "Please choose which user number one:\n";
			while (!enoughStatus)
			{
				showUsers(nullptr, type, &request);
				if ((request->getstatusarray()).size() < 2)
					throw("This member doesn't have enought status!\n");
				else
					enoughStatus = true;
			}
			setTextColor(Color::LIGHTBLUE);
			cout << "Write the status number you want to compare:\n";
			setTextColor(Color::WHITE);
			request->printAllStatus();
			cin >> choose >> chooseAnother;

			compareOne = (request->getstatusarray())[choose - 1];
			compareTwo = (request->getstatusarray())[chooseAnother - 1];

			cout << "Status number " << choose << " is" << ((*compareOne == *compareTwo) ? " " : " not ") << "the same as status number " << chooseAnother << endl;
		}
	}
}

vector<User*> Facebook::showUsers(User *except, bool flag, User **target) const //flag = 0 - member, 1 - fanlist
{
	int choose, size;
	vector<User*> tempArray;

	if (flag == TYPE_FANLIST)
		tempArray = MakeRightArray(userArray, flag);
	else // is member
		tempArray = MakeRightArray(userArray, flag);

	size = tempArray.size();

	for (int i = 0; i < size; i++)
	{
		if (tempArray[i] != except)
			cout << i + 1 << ". " << tempArray[i]->getname() << endl;
	}

	choose = cinInt();

	if (choose <= 0 || choose > size || tempArray[choose - 1] == except)
	{
		while ((choose <= 0 || choose > size) || tempArray[choose - 1] == except)
		{
			if (tempArray[choose - 1] == except)
				ERROR_COMMAND("You cannot choose " << except->getname() << endl)
				cout << "Please choose vaild number, between " << 1 << " to " << size << endl;
			choose = cinInt();
		}
	}

	*target = tempArray[choose - 1];

	return tempArray;
}

void Facebook::MakeNewBonding(bool type)
{
	User *request = nullptr, *requested = nullptr;

	if (countMember == 0 || (type && countFanpage == 0))
		throw("There are no any users in database\n");
	else if (!type && countMember == 1)
		throw("lonely, I'm so lonely.... you cannot be friend of yourself(only 1 member is in the database).\n\n");
	else
	{
		cout << "Please choose which User want add friend/fan:\n";
		showUsers(nullptr, type, &request);

		cout << "Please choose which member do you want as friend:\n";
		showUsers(request, TYPE_MEMBER, &requested);// always member, fanlist cannot be friend of fanlist

		member* requestM = dynamic_cast<member*>(request);
		Fanlist *requestF = dynamic_cast<Fanlist*>(request);
		member* requestedM = dynamic_cast<member*>(requested);

		if (requestM && requestedM)
		{
			if (checkNameAlreadyExist(requestedM->getname(), requestM->getFriendlist(), TYPE_MEMBER) == INT_TRUE)
			{
				string msg = requestM->getname() + " is already " + requestedM->getname() + "'s friend\n";
				throw(msg);
			}
			else
			{
				*requestM += *requestedM;
				requestM->newfriendtorecentstatus(requestedM->getstatusarray());
				requestedM->newfriendtorecentstatus(requestM->getstatusarray());
				SUCCESS_COMMAND(requestM->getname() << " and " << requestedM->getname() << " is now friends!\n")
			}
		}
		else
		{
			if (checkNameAlreadyExist(requestedM->getname(), requestF->getFriendlist(), TYPE_MEMBER) == INT_TRUE)
				throw(requestedM->getname() + " is already " + requestF->getname() + "'s fan\n");
			*requestF += *requestedM;
			SUCCESS_COMMAND(requestedM->getname() << " is now " << requestF->getname() << "'s fan!\n")
		}
	}
}

void Facebook::ShowAllMembersAndFanlists() const
{
	vector<User*> temp;

	if (countMember == 0)
	{
		ERROR_COMMAND("There are no any members in the database.\n")
	}
	else
	{
		temp = MakeRightArray(userArray, TYPE_MEMBER);
		cout << "All Members:\n";
		for (int i = 0; i < countMember; i++)
		{
			cout << i + 1 << ". " << temp[i]->getname() << " ( Birthday: ";
			((member*)temp[i])->printDate();
			cout << " )\n";
		}
	}
	cout << endl;
	if (countFanpage == 0)
	{
		ERROR_COMMAND("There is no any fanlists in the database.\n")
	}
	else
	{
		temp = MakeRightArray(userArray, TYPE_FANLIST);
		cout << "All Fanlists:\n";
		for (int i = 0; i < countFanpage; i++)
			cout << i + 1 << ". " << temp[i]->getname() << endl;
	}
	cout << endl;
}

void Facebook::showRecentStatus() const
{
	member *target = nullptr;
	if (userArray.size() == 0 || countMember == 0)
		throw("There are no any members in the database.\n");
	else
	{
		showUsers(nullptr, TYPE_MEMBER, ((User**)&target));
		target->printrecentstatus();
	}
}