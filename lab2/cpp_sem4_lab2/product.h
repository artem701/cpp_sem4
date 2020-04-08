#pragma once

#include "mydate.h"

struct Product
{
public:

	void console_input();
	void console_output() const;

	Date date;
	int storageID, productID, shelf, count, price;
	char name[128];
};

istream& operator >>(istream& is, Product& p);
ostream& operator <<(ostream& os, const Product& p);