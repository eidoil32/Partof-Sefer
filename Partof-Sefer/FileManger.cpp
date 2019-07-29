#include "FileManger.h"

void createBoarder()
{
	ShowConsoleCursor(false);
	printLogo(false);
	gotoxy(20, 10);
	for (int i = 0; i < 5; i++)
	{
		gotoxy(20, 10+i);
		cout << "#";
	}
	for (int i = 0; i < 5; i++)
	{
		gotoxy(61, 10 + i);
		cout << "#";
	}
	gotoxy(20, 10);
	for (int i = 0; i < 42; i++)
		cout << "#";
	gotoxy(20, 15);
	for (int i = 0; i < 42; i++)
		cout << "#";
	gotoxy(32, 13);
	cout << "Loading Progress";
}

void freeAllCurrentDataBase(vector<User*>&userArray)
{
	auto itr = userArray.begin(), itrEnd = userArray.end();
	for (; itr != itrEnd; ++itr)
		delete *itr;
}

void Database(vector<User*>&userArray, int &countMember, int &countFanpage)
{
	FileManager database;
	int choose;
	char ch;

	char arr[5][50] = { "[1] Save data", "[2] Load data" , "[3] Return to main menu" };
	choose = smallMenu(arr, 3, MENU_PAGE_SAVE_OR_LOAD_DATABASE);
	if (choose == 1)
	{
		cout << "You will now save all current data, Old data will delete forever!\nYou approve to save data? Y\\N\n";
		ch = getch();
		if (ch != YES_UPPERCASE && ch != YES_LOWERCASE)
			throw("Save command canceled!\n");
		else
		{
			try {
				database.writeTofile(userArray);
			}
			catch (const char * msg)
			{
				ERROR_COMMAND(msg)
			}
			gotoxy(29, 17);
			SUCCESS_COMMAND("Save finish successfuly!\n")
			gotoxy(22, 18);
		}
	}
	else if (choose == 2) //load data
	{
		cout << "You will now load new data to system, all current data will delete forever!\nYou approve to load data? Y\\N\n";
		ch = getch();
		if (ch != YES_UPPERCASE && ch != YES_LOWERCASE)
		{
			ERROR_COMMAND("Load command canceled!\n")
		}
		else
		{
			gotoxy(29, 17);
			try {
				freeAllCurrentDataBase(userArray);
				userArray = database.readFromFile(countMember, countFanpage);
			}
			catch (const char *msg)
			{
				throw(msg);
			}
			catch (...)
			{
				throw("Oops.. Something wired happend..We do not know what happened, so we take you back to the main menu!");
			}
			gotoxy(22, 18);
		}

	}
}

void FileManager::writeTofile(vector<User*>&userArray)
{
	ifstream temp;
	temp.open("facebook_db.ftxt");
	double maxSize, currentPlace = 0;
	Date *tempDate;
	char ch;
	
	if (!temp.good())
	{
		temp.close();
		ERROR_COMMAND("File doesn't Exist!\n")
		cout << "Do you want to create new file? Y \\ N\n";
		ch = getch();
		if (ch != YES_UPPERCASE && ch != YES_LOWERCASE)
			throw("Save file canceled!\n");
	}
	facebook_write.open("facebook_db.ftxt");
	if (!facebook_write)
		throw("Can't open/write to file!");

	createBoarder();
	maxSize = userArray.size()*2;

	int userArraySize = userArray.size();
	auto itr = userArray.begin(), itrEnd = userArray.end();
	vector<User*>::const_iterator Fitr, FitrEnd;
	vector<status*>::const_iterator Sitr, SitrEnd;

	facebook_write << "Total User:" << userArraySize << endl;
	for (; itr != itrEnd; ++itr, currentPlace++)
	{
		facebook_write << "User type:" << typeid(**itr).name() << endl;
		facebook_write << "User name:" << (*itr)->getname() << endl;
		if (TYPEID_CHECK(**itr, member))
		{
			tempDate = ((member*)(*itr))->getBirthdate();
			facebook_write << tempDate->getDay() << "\\" << tempDate->getMonth() << "\\" << tempDate->getYear() << endl;
		}
		facebook_write << "Total status:" << (*itr)->getstatusarray().size() << endl;
		Sitr = (*itr)->getstatusarray().begin();
		SitrEnd = (*itr)->getstatusarray().end();
		for (; Sitr != SitrEnd; ++Sitr)
		{
			facebook_write << "Status type:" << typeid(**Sitr).name() << endl;
			tempDate = (*Sitr)->getDateForFile();
			facebook_write << "Status publish date:" << tempDate->getDay() << "\\" << tempDate->getMonth() << "\\" << tempDate->getYear()
				<< "Time:" << tempDate->getHour() << ":" << tempDate->getMin() << endl;
			if (TYPEID_CHECK(**Sitr, statusText) || TYPEID_CHECK(**Sitr, statusPictureWithText) || TYPEID_CHECK(**Sitr, statusVideoWithText))
			{ //cannot convert from status to statusText, we don't know why... :(
				facebook_write << "Status text:"<< (*Sitr)->getText() << endl;
			}
		}
		progressBar(currentPlace, maxSize);
	}

	itr = userArray.begin();
	for (; itr != itrEnd; ++itr, currentPlace++)
	{
		facebook_write << "User name:" << (*itr)->getname() << endl;
		facebook_write << "User Type:" << typeid(**itr).name() << endl;
		facebook_write << "Total Friends:" << (*itr)->getFriendlist().size() << endl;
		facebook_write << "Friends:" << endl;
		Fitr = (*itr)->getFriendlist().begin();
		FitrEnd = (*itr)->getFriendlist().end();
		for (; Fitr != FitrEnd; ++Fitr)
		{
			facebook_write << "Friend type:" << typeid(**Fitr).name() << endl;
			facebook_write << "Friend name:" << (*Fitr)->getname() << endl;
		}
		progressBar(currentPlace, maxSize);
	}
	progressBar(maxSize, maxSize);
	facebook_write.close();
	cout << endl;
}

vector<User*> FileManager::readFromFile(int &countMember, int &countFanpage)
{
	vector<User*> temp;
	status *tempStatus;
	User *tempUser, *tempFriend;
	Date *tempDate;
	int tempDay, tempMonth, tempYear, tempHour, tempMin, tempNumOfStatus, tempNumOfFriends;
	string tempText, userType, statusType, tempName, tempFriendName;
	int userArraySize;
	auto itr = temp.begin();
	vector<User*>::iterator Fitr;
	vector<status*>::iterator Sitr;
	bool type;
	char buffer[100];
	double maxSize;

	countMember = 0;
	countFanpage = 0;

	facebook_read.open("facebook_db.ftxt");
	if (!facebook_read)
		throw("Can't open/read from file!\n");

	createBoarder();
	facebook_read.seekg(0, facebook_read.end);
	maxSize = (double)facebook_read.tellg();
	facebook_read.seekg(0, facebook_read.beg);

	READ_UNTIL(facebook_read, ':');
	facebook_read >> userArraySize;
	temp.reserve(userArraySize);
	for (int i = 0; i < userArraySize; i++)
	{
		READ_UNTIL(facebook_read, ':');
		getline(facebook_read, userType, '\n');
		READ_UNTIL(facebook_read, ':');
		getline(facebook_read, tempName, '\n');
		if (userType == typeid(member).name())
		{
			countMember++;
			facebook_read >> tempDay;
			facebook_read.ignore(1,'\\');
			facebook_read >> tempMonth;
			facebook_read.ignore(1, '\\');
			facebook_read >> tempYear;
			facebook_read.ignore(1, '\\');
			tempDate = new Date(tempDay,tempMonth,tempYear);
			tempUser = new member(tempName,*tempDate);
		}
		else
		{
			countFanpage++;
			tempUser = new Fanlist(tempName);
		}
		READ_UNTIL(facebook_read, ':');
		facebook_read >> tempNumOfStatus;
		tempUser->getstatusarray().reserve(tempNumOfStatus);
		for (int j = 0; j < tempNumOfStatus; j++)
		{
			READ_UNTIL(facebook_read, ':');
			getline(facebook_read, statusType, '\n');
			READ_UNTIL(facebook_read, ':');
			facebook_read >> tempDay;
			facebook_read.read(buffer, STRLEN_MINUS_ONE("\\"));
			facebook_read >> tempMonth;
			facebook_read.read(buffer, STRLEN_MINUS_ONE("\\"));
			facebook_read >> tempYear;
			READ_UNTIL(facebook_read, ':');
			facebook_read >> tempHour;
			facebook_read.ignore(1, ':');
			facebook_read >> tempMin;
			tempDate = new Date(tempDay, tempMonth, tempYear, tempHour, tempMin);
			if (statusType == typeid(statusText).name())
			{
				READ_UNTIL(facebook_read, ':');
				getline(facebook_read, tempText, '\n');
				tempStatus = new statusText(*tempDate, tempName, tempText);
			}
			else if (statusType == typeid(statusVideoWithText).name())
			{
				READ_UNTIL(facebook_read, ':');
				getline(facebook_read, tempText, '\n');
				tempStatus = new statusVideoWithText(statusText(*tempDate, tempName, tempText));
			}
			else if (statusType == typeid(statusPictureWithText).name())
			{
				READ_UNTIL(facebook_read, ':');
				getline(facebook_read, tempText, '\n');
				tempStatus = new statusPictureWithText(statusText(*tempDate, tempName, tempText));
			}
			else if (statusType == typeid(statusVideo).name())
				tempStatus = new statusVideo(*tempDate,tempName);
			else if (statusType == typeid(statusPicture).name())
				tempStatus = new statusPicture(*tempDate, tempName);

			tempUser->getstatusarray().push_back(tempStatus);
		}
		temp.push_back(tempUser);
		progressBar((double)facebook_read.tellg(), maxSize);
	}

	//after create all users, All friendships must be returned!
	itr = temp.begin();
	auto itrEnd = temp.end();
	for (; itr != itrEnd; ++itr)
	{
		READ_UNTIL(facebook_read, ':');
		getline(facebook_read, tempName, '\n');
		READ_UNTIL(facebook_read, ':');
		getline(facebook_read, userType, '\n');
		if (userType == typeid(member).name())
			type = TYPE_MEMBER;
		else
			type = TYPE_FANLIST;
		tempUser = findFriend(temp, tempName, type);
		READ_UNTIL(facebook_read, ':');
		facebook_read >> tempNumOfFriends;
		tempUser->getFriendlist().reserve(tempNumOfFriends);
		READ_UNTIL(facebook_read, ':');
		for (int i = 0; i < tempNumOfFriends; i++)
		{
			READ_UNTIL(facebook_read, ':');
			getline(facebook_read, userType, '\n');
			READ_UNTIL(facebook_read, ':');
			getline(facebook_read, tempFriendName, '\n');
			if (userType == typeid(member).name())
			{
				type = TYPE_MEMBER;
				tempUser->plusCountMember();
			}
			else
			{
				type = TYPE_FANLIST;
			}
			tempFriend = findFriend(temp, tempFriendName, type);
			if (TYPEID_CHECK(*tempFriend, *tempUser))
				((member*)tempUser)->newfriendtorecentstatus(tempFriend->getstatusarray());
			tempUser->getFriendlist().push_back(tempFriend);
		}
		progressBar((double)facebook_read.tellg(), maxSize);
	}
	progressBar(maxSize, maxSize);
	facebook_read.close();
	cout << endl;
	return temp;
}

User* findFriend(vector<User*>&friendlist, string&tempFriendName, bool type)
{
	auto itr = friendlist.begin(), itrEnd = friendlist.end();
	for(; itr != itrEnd; ++itr)
		if ((*itr)->getname() == tempFriendName)
		{
			if (!type && TYPEID_CHECK(**itr, member))
				return *itr;
			else if (type && TYPEID_CHECK(**itr, Fanlist))
				return *itr;
		}
	
	return *itrEnd; //have to find him!
}

void progressBar(double current, double max) // beautiful animation...
{
	gotoxy(25, 12);
	double val = (current / max) * 100;
	cout << (int)val << "% [";
	setTextColor(LIGHTGREEN);
	for (int i = 0; i < 25; i++)
	{
		if (i <= val / 4)
		{
			cout << (char)254;
		}
		else
			cout << " ";
	}
	setTextColor(WHITE);
	cout << "]";
	Sleep(LOADING_SPEED);
}