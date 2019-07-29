#pragma once

class User;
class member;
class Fanlist;
class status;

#include "Facebook.h"

void printPictureASCII();
void printVideoASCII();

int checkNameAlreadyExist(string name, vector<User*> arr, bool flag);
vector<User*> MakeRightArray(vector<User*>arr, bool flag);

int cinInt();