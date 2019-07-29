#include <iostream>
using namespace std;

#include "Status.h"

bool status::operator==(const status&compare)
{
	return (typeid(*this) == typeid(compare));
}

bool status::operator!=(const status & compare)
{
	return !(*this == compare);
}

status::~status()
{
	delete date;
}

void status::printstatus() const
{
	cout << "\n------------------------------------\n";
	cout << "Publisher's name : " << postername << endl;
	cout << "Publish date: ";
	date->showdate();
	cout << " Time:";
	date->showtime();
	cout << endl;
}

status::status(const status & status)
{
	this->postername = status.getName();
	this->date = new Date(status.getDate());
}

status::status(const Date &date,const string postername)
{
	this->date = new Date(date);
	this->postername = postername;
}

status *newStatus(const string posterName)
{
	char arr[5][50] = { "[1] Text","[2] Picture","[3] Video","[4] Picture with text","[5] Video with text" };
	string postText;
	int j = 0, type, phSize = BASE_SIZE;
	time_t now = time(0);
	struct tm tm = *localtime(&now);
	status *newone = nullptr;

	Date current(tm.tm_mday, tm.tm_mon + MONCONV, tm.tm_year + YEARCONV, tm.tm_hour, tm.tm_min);
	type = smallMenu(arr, 5,MENU_PAGE_ADD_STATUS);

	cin.ignore();

	switch (type)
	{
	case STATUS_TEXT:
		cout << "Enter your post text (ends with enter):\n";
		getline(cin, postText);
		if (postText == "")
		{
			cout << "Why to choose text type if you didn't enter any text?\nPlease enter at least one word.\n";
			getline(cin, postText);
		}
		newone = new statusText(current, posterName, postText);
		break;
	case STATUS_PIC:
		newone = new statusPicture(current, posterName);
		cout << "And now you can import picture from your computer";
		break;
	case STATUS_VID:
		newone = new statusVideo(current, posterName);
		cout << "And now you can import picture from your computer";
		break;
	case STATUS_PIC_WTEXT:
		cout << "Enter your post text (ends with enter):\n";
		getline(cin, postText);
		if (postText == "")
		{
			cout << "Why to choose text type if you didn't enter any text?\nPlease enter at least one word.\n";
			getline(cin, postText);
		}
		newone = new statusPictureWithText(statusText(current, posterName, postText));
		break;
	case STATUS_VID_WTEXT:
		cout << "Enter your post text (ends with enter):\n";
		getline(cin, postText);
		if (postText == "")
		{
			cout << "Why to choose text type if you didn't enter any text?\nPlease enter at least one word.\n";
			getline(cin, postText);
		}
		newone = new statusVideoWithText(statusText(current, posterName, postText));
		break;
	default:
		break;
	}
	SUCCESS_COMMAND( "\nStatus Added successfully\n")
	return newone;
}

statusText::statusText(const statusText & cpy)
{
	postername = cpy.getName();
	text = cpy.getText();
	date = new Date(cpy.getDate());
}

void statusText::settext(string posttext)
{
	text = posttext;
}

void statusText::printstatus() const
{
	status::printstatus();
	cout << text << endl;
}

bool statusText::operator==(const statusText & compare)
{
	if (((status)*this) == compare)
		return !(text == compare.getText());
	return false;
}

bool statusText::operator!=(const statusText & compare)
{
	return !(*this == compare);
}

void statusPicture::printstatus() const
{
	status::printstatus();
	printPictureASCII();
}

void statusPictureWithText::printstatus() const
{
	statusPicture::printstatus();
	cout << text << endl;
}

void statusVideo::printstatus() const
{
	status::printstatus();
	printVideoASCII();
}

void statusVideoWithText::printstatus() const
{
	statusVideo::printstatus();
	cout << text << endl;
}
