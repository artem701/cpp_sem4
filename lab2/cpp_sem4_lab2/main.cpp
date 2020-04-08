
#include <iostream>
#include <windows.h>
#include <functional>
#include "product.h"
#include "data.h"

/* Дубровских А. Р.
 * 2 курс, 9 группа
 *
 * Задача №2
 */



typedef Data<Product>::Predicate Predicate;
typedef Data<Product> Products;

/* Принимает объект типа Data<Product> и метод Data<Product>, который будет вызван с критериями, определенными пользователем.
 * Возвращает результат вызова функции */
template <typename ret_t> ret_t action_by_choice(Products& data, std::function<ret_t(Products&, Predicate)> f)
{
	cout << " Выберите критерий поиска:\n"
		<< " \t1 - по номеру склада\n"
		<< " \t2 - по коду товара\n"
		<< " \t3 - по дате поступления\n"
		<< " \t4 - проcроченные на момент " << Date::get_today() << "\n"
		<< "\n \t0 - вернуться в меню\n\n> ";

	char line[256];
	cin.getline(line, 256);

	char cmd = line[0];
	int buffer;
	Date date;

	switch (cmd)
	{
	case '1':
		cout << " Введите номер склада: ";
		cin >> buffer; cin.getline(line, 256);
		return f(data, [buffer](const Product& item) { return item.storageID == buffer; });
		break;
	case '2':
		cout << " Введите код товара: ";
		cin >> buffer; cin.getline(line, 256);
		return f(data, [buffer](const Product& item) { return item.productID == buffer; });
		break;
	case '3':
		cout << " Введите дату поступления: ";
		cin >> date; cin.getline(line, 256);
		return f(data, [date](const Product& item) { return item.date.compare(date) == 0; });
		break;
	case '4':
		return f(data, [buffer](const Product& item) { return (item.date + item.shelf).compare(Date::get_today()) < 0; });
		break;
	default:
		cout << " Нет такого критерия\n";
	}

	return ret_t();
}

void menu()
{
	Products data;

	while (true)
	{
		cout
			<< " 1 - добавить элемент\n"
			<< " 2 - заполнить контейнер из файла\n"
			<< " 3 - напечатать содержимое контейнера\n"
			<< " 4 - сохранить контейнер в файл\n"
			<< " 5 - напечатать элементы по критерию\n"
			<< " 6 - вывести элементы по критерию в файл\n"
			<< " 7 - удалить элементы по критерию\n"
				/* подразумевается сортировка в приоритете */
				/* номер склада -> номер товара */
			<< " 8 - сортировка\n" 
			<< " 0 - выход\n\n";

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
			cout << "Введите имя файла: ";
			cin.getline(fname, 256);
			data.fill(fname);
			break;
		case '3':
			if (data.count() == 0)
				cout << "\nКонтейнер пуст\n";
			else
			{
				cout << "\nСодержимое контейнера:\n\n";
				data.print();
			}
			break;
		case '4':
			cout << "Введите имя файла: ";
			cin.getline(fname, 256);
			data.print(fname);
			break;
		case '5':
			subdata = action_by_choice<Products>(data, &Products::select);
			if (subdata.count() == 0)
				cout << "По хпдпнному критерию ничего не найдено";
			else
				subdata.print();
			break;
		case '6':
			cout << "Введите имя файла: ";
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