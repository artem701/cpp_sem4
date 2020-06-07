
#include "utils.h"


#include "storage_catalogue.h"

#include <string>
#include <io.h>

using namespace std;

// Возврашает выбранную пользователем команду
char get_cmd()
{
	static char line[256];
	cin.getline(line, 256);

	return line[0];
}

string get_fname()
{
	string fname;
	cout << "Введите имя: ";
	input(fname);
	return fname;
}

bool file_exists(string fname)
{
	static char str[256];
	fname.copy(str, 256);

	return _access(str, 0) != -1;
}

void save(StorageCatalogue& sc, string path)
{
	sc.storages.sort([](auto a, auto b)
	{
		return a.id < b.id;
	});
	sc.products.sort([](auto a, auto b)
	{
		return a.productID < b.productID;
	});
	sc.toDisk(path);
}

bool check_yn()
{
	bool not_ok = true;
	bool choice = true;
	do
	{
		switch (get_cmd())
		{
		case '1':
		case 'y':
		case 'Y':
		case 'д':
		case 'Д':
			choice = true;
			not_ok = false;
			break;
		case '0':
		case 'n':
		case 'N':
		case 'н':
		case 'Н':
			choice = false;
			not_ok = false;
			break;
		default:
			cout << "Ошибка, повторите ввод: ";
			break;
		}
	} while (not_ok);

	return choice;
}