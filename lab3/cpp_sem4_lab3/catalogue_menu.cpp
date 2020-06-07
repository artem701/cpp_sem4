
#include "menus.h"
#include "utils.h"

void catalogue_menu(StorageCatalogue& catalogue)
{
	while (true)
	{
		cout
			<< " 1 - вывести список складов\n"
			<< " 2 - добавить пустой склад\n"
			<< " 3 - удалить склад\n"
			<< " 4 - перейти к складу\n"
			<< " 5 - сохранить каталог\n"
			<< "\n"
			<< " 0 - назад\n"
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
			cout << "Введите id склада (0 чтобы выйти): ";
			input(id);
			if (id > 0)
			{
				// Проверка уникальности id
				// При записи каталога на диск номера складов упорядочиваются
				while (-1 != catalogue.storages.indexof_binary(
					[id](auto s)
				{
					return id - s.id;
				}))
				{
					cout << "Склад с таким id уже существует. Повторите ввод: ";
					input(id);
				}
				cout << "Введите комментарий: ";
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
			cout << "Введите id удаляемого склада (0 чтобы выйти): ";
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
			cout << "Введите id склада (0 чтобы выйти): ";
			input(id);
			if (id > 0)
			{
				if (-1 == catalogue.storages.indexof_binary(
					[id](auto s)
				{
					return id - s.id;
				}))
				{
					cout << "Выбранного склада не существует\n";
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
				cout << "Недопустимое имя\n";
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
			cout << "Неизвестная команда\n";
		}
	}
}