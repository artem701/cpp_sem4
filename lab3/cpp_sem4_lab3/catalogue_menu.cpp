
#include "menus.h"
#include "utils.h"

void catalogue_menu(StorageCatalogue& catalogue)
{
	while (true)
	{
		cout
			<< " 1 - ������� ������ �������\n"
			<< " 2 - �������� ������ �����\n"
			<< " 3 - ������� �����\n"
			<< " 4 - ������� � ������\n"
			<< " 5 - ��������� �������\n"
			<< "\n"
			<< " 0 - �����\n"
			<< "\n"
			<< "\n"
			<< "> ";

		switch (get_cmd())
		{
		case '1':
			catalogue.storages.print();
			break;
		case '2':
		{
			int id;
			cout << "������� id ������ (0 ����� �����): ";
			input(id);
			if (id > 0)
			{
				// �������� ������������ id
				// ��� ������ �������� �� ���� ������ ������� ���������������
				while (-1 != catalogue.storages.indexof_binary(
					[id](auto s)
				{
					return id - s.id;
				}))
				{
					cout << "����� � ����� id ��� ����������. ��������� ����: ";
					input(id);
				}
				cout << "������� �����������: ";
				static char comment_str[256];
				cin.getline(comment_str, 256);
				string comment(comment_str);
				catalogue.storages.add({ id, comment });
				save(catalogue);
			}
			break;
		}
		case '3':
		{
			int id;
			cout << "������� id ���������� ������ (0 ����� �����): ";
			input(id);
			if (id > 0)
			{

				catalogue.storages.remove_if(
					[id](auto s)
				{
					return s.id == id;
				});
				catalogue.products.remove_if(
					[id](auto p)
				{
					return p.storageID == id;
				});
				save(catalogue);
			}
			break;
		}
		case '4':
		{
			int id;
			cout << "������� id ������ (0 ����� �����): ";
			input(id);
			if (id > 0)
			{
				if (-1 == catalogue.storages.indexof_binary(
					[id](auto s)
				{
					return id - s.id;
				}))
				{
					cout << "���������� ������ �� ����������\n";
				}
				else {
					storage_menu(catalogue, id);
				}
			}
			break;
		}
		case '5':
		{
			string fname = get_fname();
			if (fname == "tmp")
			{
				cout << "������������ ���\n";
			}
			else 
			{
				save(catalogue, fname);
			}
			break;
		}
		case '0':
			return;
		default:
			cout << "����������� �������\n";
		}
	}
}