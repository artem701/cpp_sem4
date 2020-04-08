
#include <iostream>
#include <windows.h>
#include <functional>
#include "product.h"
#include "data.h"


typedef Data<Product>::Predicate Predicate;
typedef Data<Product> Products;

/* ��������� ������ ���� Data<Product> � ����� Data<Product>, ������� ����� ������ � ����������, ������������� �������������.
 * ���������� ��������� ������ ������� */
template <typename ret_t> ret_t action_by_choice(Products& data, std::function<ret_t(Products&, Predicate)> f)
{
	cout << " �������� �������� ������:\n"
		<< " \t1 - �� ������ ������\n"
		<< " \t2 - �� ���� ������\n"
		<< " \t3 - �� ���� �����������\n"
		<< " \t4 - ���c�������� �� ������ " << Date::get_today() << "\n"
		<< "\n \t0 - ��������� � ����\n\n> ";

	char line[256];
	cin.getline(line, 256);

	char cmd = line[0];
	int buffer;
	Date date;

	switch (cmd)
	{
	case '1':
		cout << " ������� ����� ������: ";
		cin >> buffer; cin.getline(line, 256);
		return f(data, [buffer](const Product& item) { return item.storageID == buffer; });
		break;
	case '2':
		cout << " ������� ��� ������: ";
		cin >> buffer; cin.getline(line, 256);
		return f(data, [buffer](const Product& item) { return item.productID == buffer; });
		break;
	case '3':
		cout << " ������� ���� �����������: ";
		cin >> date; cin.getline(line, 256);
		return f(data, [date](const Product& item) { return item.date.compare(date) == 0; });
		break;
	case '4':
		return f(data, [buffer](const Product& item) { return (item.date + item.shelf).compare(Date::get_today()) < 0; });
		break;
	default:
		cout << " ��� ������ ��������\n";
	}

	return ret_t();
}

void menu()
{
	Products data;

	while (true)
	{
		cout
			<< " 1 - �������� �������\n"
			<< " 2 - ��������� ��������� �� �����\n"
			<< " 3 - ���������� ���������� ����������\n"
			<< " 4 - ��������� ��������� � ����\n"
			<< " 5 - ���������� �������� �� ��������\n"
			<< " 6 - ������� �������� �� �������� � ����\n"
			<< " 7 - ������� �������� �� ��������\n"
				/* ��������������� ���������� � ���������� */
				/* ����� ������ -> ����� ������ */
			<< " 8 - ����������\n" 
			<< " 0 - �����\n\n";

		cout << "> ";

		char line[256];
		cin.getline(line, 256);

		char cmd = line[0];

		char fname[256];
		Product el;
		Products subdata;

		switch (cmd)
		{
		case '1':
			el.console_input();
			data.add(el);
			break;
		case '2':
			cout << "������� ��� �����: ";
			cin.getline(fname, 256);
			data.fill(fname);
			break;
		case '3':
			if (data.count() == 0)
				cout << "\n��������� ����\n";
			else
			{
				cout << "\n���������� ����������:\n\n";
				data.print();
			}
			break;
		case '4':
			cout << "������� ��� �����: ";
			cin.getline(fname, 256);
			data.print(fname);
			break;
		case '5':
			subdata = action_by_choice<Products>(data, &Products::select);
			if (subdata.count() == 0)
				cout << "�� ��������� �������� ������ �� �������";
			else
				subdata.print();
			break;
		case '6':
			cout << "������� ��� �����: ";
			cin.getline(fname, 256);
			subdata = action_by_choice<Products>(data, &Products::select);
			subdata.print(fname);
			break;
		case '7':
			action_by_choice<void>(data, &Products::remove_if);
			break;
		case '8':
			data.sort([](const Product& a, const Product& b) 
			{
				if (a.storageID < b.storageID)
					return true;
				if (a.storageID > b.storageID)
					return false;

				return a.productID < b.productID;
			});
			break;

		case '0':
			return;
		}
		cout << "\n";
	}
}

int main()
{
	setlocale(0, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	menu();

	return 0;
}