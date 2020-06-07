#pragma once

#include "mydate.h"
#include <string>

struct Product
{
public:

	void console_input();
	void console_output() const;

	Date date;
	unsigned int storageID, productID, shelf, count, price;
	std::string name;
};

istream& operator >>(istream& is, Product& p);
ostream& operator <<(ostream& os, const Product& p);