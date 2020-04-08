#include "product.h"

istream & operator>>(istream & is, Product & p)
{
	if (&is == &cin)
	{
		p.console_input();
		return cin;
	}
	is.getline(p.name, 256);
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
	cout << "Наименование товара: ";	cin.getline(name, 256);
	cout << "ID товара: ";				cin >> productID;
	cout << "ID склада: ";				cin >> storageID;
	cout << "Дата поступления: ";		cin >> date;
	cout << "Срок хранения: ";			cin >> shelf;
	cout << "Количество: ";				cin >> count;
	cout << "Цена: ";					cin >> price;
	getchar(); // \n 
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
