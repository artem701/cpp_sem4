
#include "product.h"

#include "utils.h"

#include <string>

using namespace std;

istream & operator>>(istream & is, Product & p)
{
	if (&is == &cin)
	{
		p.console_input();
		return cin;
	}
	static char line[256];
	is.getline(line, 256);
	p.name = string(line);
	is >> p.productID;
	is >> p.storageID;
	is >> p.date;
	is >> p.shelf;
	is >> p.count;	
	is >> p.price;
	
	while (!is.eof() && (is.get() != '\n'))
		;

	return is;
}

ostream & operator<<(ostream & os, const Product & p)
{
	if (&os == &cout)
	{
		p.console_output();
		return os;
	}
	os << p.name << "\n";
	os << p.productID << " ";
	os << p.storageID << " ";
	os << p.date << " ";
	os << p.shelf << " ";
	os << p.count << " ";
	os << p.price << "\n";

	return os;
}

void Product::console_input()
{
	static char line[256];

	cout << "Наименование товара: ";
	cin.getline(line, 256);
	name = string(line);
	cout << "ID товара: ";				input(productID);
	cout << "Дата поступления: ";		input(date);
	cout << "Срок хранения: ";			input(shelf);
	cout << "Количество: ";				input(count);
	cout << "Цена: ";					input(price);
}

void Product::console_output() const
{
	cout << "Наименование товара: " << name << "\n";
	cout << "ID товара: " << productID << "\n";
	cout << "ID склада: " << storageID << "\n";
	cout << "Дата поступления: " << date << "\n";
	cout << "Срок хранения: " << shelf << "\n";
	cout << "Количество: " << count << "\n";
	cout << "Цена: " << price << "\n\n";
}
