#pragma once

const int STATUS_TEXT = 1, STATUS_PIC = 2, STATUS_PIC_WTEXT = 4, STATUS_VID = 3, STATUS_VID_WTEXT = 5;

#include "Date.h"
#include "Services.h"

//don't create new variable type of status
class status
{
protected:
	status() {}
	string postername;
	Date *date;
public:
	status(const status& status);
	status(const Date& date, const string postername);
	virtual ~status();
	const string getName()								const	{ return postername; }
	virtual void printstatus()							const;
	void setdate(const Date &date)								{ *(this->date) = date; }
	const Date getDate()								const	{ return *date; }
	Date *getDateForFile()								const	{ return date; }
	virtual string getText() const { return ""; }
	virtual bool operator==(const status&compare);
	virtual bool operator!=(const status&compare);
};

class statusText : virtual public status
{
protected:
	string text;
public: // there is no need for virtual dtor because we have a method with virtual
	statusText(const statusText &cpy);
	statusText(const Date & date, const string postername, string text) : status(date, postername) { this->text = text; }
	void settext(string txt);
	string getText()								const	{ return text; }
	virtual void printstatus() const override; 
	bool operator==(const statusText&compare);
	bool operator!=(const statusText&compare);
};

class statusPicture : virtual public status
{
public:
	statusPicture(const Date& date,const string postername) : status(date, postername) {}
	~statusPicture() {}
	virtual void printstatus() const override;
	//virtual string getText() const { return ""; }
};

class statusPictureWithText : public statusPicture, public statusText
{
public:
	statusPictureWithText(const statusText &baseText) : status(baseText.getDate(), baseText.getName()),
		statusText(baseText), statusPicture(baseText.getDate(), baseText.getName()) {}
	~statusPictureWithText() {}
	void printstatus() const override;
	virtual string getText() const { return statusText::getText(); }
};

class statusVideo : virtual public status
{
public:
	statusVideo(const Date& date, const string postername) : status(date, postername) {}
	~statusVideo() {}
	virtual void printstatus() const override;
	//virtual string getText() const { return ""; }
};

class statusVideoWithText : public statusVideo, public statusText
{
public:
	statusVideoWithText(const statusText &baseText) : status(baseText.getDate(), baseText.getName()),
		statusText(baseText), statusVideo(baseText.getDate(), baseText.getName()) {}
	~statusVideoWithText() {}
	void printstatus() const override;
	virtual string getText() const { return statusText::getText(); }
};