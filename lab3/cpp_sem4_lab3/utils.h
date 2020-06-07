#pragma once

#include "storage_catalogue.h"

#include <string>
#include <windows.h>

using namespace std;

typedef Data<Product>::Predicate Predicate;
typedef Data<Product> Products;

template<typename T>
inline void input(T& var)
{
	static char line[256];
	while (!(cin >> var))
	{
		// Отбрасываем оставшуюся часть строки
		cin.clear();
		cin.getline(line, 256);
		cout << "Введено неверно, повторите ввод: ";
	}
	// Пропуск оставшихся символов
	cin.getline(line, 256);
}

char get_cmd();

string get_fname();

bool file_exists(string fname);

void save(StorageCatalogue & sc, string path = "tmp");

bool check_yn();
