#pragma once
#include <fstream>
#include <iostream>

using namespace std;

#include "Facebook.h"

#define STRLEN_MINUS_ONE(x)	strlen(x) 

//READ_UNTIL is for ignoring all unnecessary words and ':'...
#define READ_UNTIL(file,delimiting) {	char key = file.get();\
										while((key = file.get()) != delimiting) {}\
									}

User* findFriend(vector<User*>&friendlist, string&tempFriendName, bool type);
void progressBar(double current, double max);
void printLogo(bool firstTime);

const int LOADING_SPEED = 35;

class FileManager
{
private:
	ofstream facebook_write;
	ifstream facebook_read;
public:
	void writeTofile(vector<User*>&userArray);
	vector<User*> readFromFile(int &countMember, int &countFanpage);
};