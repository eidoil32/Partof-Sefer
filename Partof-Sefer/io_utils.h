#pragma once
#include "config.h"
#include "Color.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "io_utils.h"
#include <cstring>

void gotoxy(int x, int y);
void setTextColor(Color);
void hideCursor();
void clear_screen();
void ShowConsoleCursor(bool showFlag);

#ifndef WINDOWS	
int _getch(void);
int _kbhit(void);
void Sleep(unsigned long);
#else
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#endif