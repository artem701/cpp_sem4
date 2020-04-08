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
	cout << "������������ ������: ";	cin.getline(name, 256);
	cout << "ID ������: ";				cin >> productID;
	cout << "ID ������: ";				cin >> storageID;
	cout << "���� �����������: ";		cin >> date;
	cout << "���� ��������: ";			cin >> shelf;
	cout << "����������: ";				cin >> count;
	cout << "����: ";					cin >> price;
	getchar(); // \n 
}

void Product::console_output() const
{
	cout << "������������ ������: " << name << "\n";
	cout << "ID ������: " << productID << "\n";
	cout << "ID ������: " << storageID << "\n";
	cout << "���� �����������: " << date << "\n";
	cout << "���� ��������: " << shelf << "\n";
	cout << "����������: " << count << "\n";
	cout << "����: " << price << "\n\n";
}
