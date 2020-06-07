#pragma once

#include <iostream>
#include <string>

using namespace std;

struct Storage
{
public:

	void console_input();
	void console_output() const;

	int id;
	string comment;
};

istream& operator >>(istream& is, Storage& p);
ostream& operator <<(ostream& os, const Storage& p);