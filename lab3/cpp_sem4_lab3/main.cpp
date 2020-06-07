
#include <iostream>
#include <windows.h>
#include <functional>
#include <string>

#include "menus.h"

/* Дубровских А. Р.
 * 2 курс, 9 группа
 *
 * Задача №2 (Склады/продукты)
 */

using namespace std;

int main()
{
	setlocale(0, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	start_menu();

	return 0;
}