
#include "menus.h"
#include "utils.h"

void start_menu()
{
	if (file_exists("tmp_storages.txt") && file_exists("tmp_products.txt"))
	{
		cout << "������������ ���������� ������? (y/n)\n";

		if (check_yn())
		{
			StorageCatalogue sc;
			sc.fromDisk("tmp");
			catalogue_menu(sc);
		}
	}

	while (true)
	{
		cout
			<< " 1 - ������� ������� �������\n"
			<< " 2 - ������� ������������ ������� ������\n"
			<< "\n"
			<< " 0 - �����\n"
			<< "\n"
			<< "\n"
			<< "> ";

		StorageCatalogue sc;

		switch (get_cmd())
		{
		case '1':
			catalogue_menu(sc);
			break;
		case '2':
		{
			string fname = get_fname();
			if (!file_exists(fname + "_storages.txt") || !file_exists(fname + "_products.txt"))
			{
				cout << "������� �� ������\n";
				break;
			}
			sc.fromDisk(fname);
			catalogue_menu(sc);
			break;
		}
		case '0':
			return;
		default:
			cout << "����������� �������\n";
		}
	}
}