
#include "menus.h"
#include "utils.h"

static Predicate get_criteria()
{
	cout << " Выберите критерий поиска:\n"
		<< "\ta - все\n"
		<< " \t1 - по коду товара\n"
		<< " \t2 - поступил не ранее\n"
		<< " \t3 - поступил не позднее\n"
		<< " \t4 - в количестве не менее\n"
		<< " \t5 - в количестве не более\n"
		<< " \t6 - цена не менее\n"
		<< " \t7 - цена не более\n"
		<< " \t8 - срок хранения не менее\n"
		<< " \t9 - срок хранения не более\n"
		<< " \t0 - проcроченные на момент " << Date::get_today() << "\n"
		<< "\n\tr - вернуться в меню"
		<< "\n\n> ";

	while (true)
	{
		char c = get_cmd();
		if (c > '0' && c <= '9')
		{
			cout << "Введите параметр: ";
		}

		switch (c)
		{
		case 'a':
			return [](const Product& p) {return true; };
		case '1':
		{
			int id;
			input(id);
			return [id](const Product& p) {return p.productID == id; };
		}
		case '2':
		{
			Date date;
			input(date);
			return [date](const Product& p) {return p.date.compare(date) >= 0; };
		}
		case '3':
		{
			Date date;
			input(date);
			return [date](const Product& p) {return p.date.compare(date) <= 0; };
		}
		case '4':
		{
			int num;
			input(num);
			return [num](const Product& p) {return p.count >= num; };
		}
		case '5':
		{
			int num;
			input(num);
			return [num](const Product& p) {return p.count <= num; };
		}
		case '6':
		{
			int price;
			input(price);
			return [price](const Product& p) {return p.price >= price; };
		}
		case '7':
		{
			int price;
			input(price);
			return [price](const Product& p) {return p.price <= price; };
		}
		case '8':
		{
			int shelf;
			input(shelf);
			return [shelf](const Product& p) {return p.shelf >= shelf; };
		}
		case '9':
		{
			int shelf;
			input(shelf);
			return [shelf](const Product& p) {return p.shelf <= shelf; };
		}
		case '0':
		{
			return [](const Product& p) {return (p.date + p.shelf).compare(Date::get_today()) < 0; };
		}
		case 'r':
			return [](const Product& p) {return false; };
		default:
			cout << "Нет такого критерия. Повторте ввод\n";
			break;
		}
	}
}

void storage_menu(StorageCatalogue& catalogue, int id)
{
	// Выбираем продукты с этого склада
	Products storage = catalogue.products.select(
		[id](const Product& p)
	{
		return p.storageID == id;
	});

	while (true)
	{
		cout
			<< " 1 - добавить элемент\n"
			<< " 2 - напечатать содержимое склада\n"
			<< " 3 - напечатать элементы по критерию\n"
			<< " 4 - вывести элементы по критерию в файл\n"
			<< " 5 - удалить элементы по критерию\n"
			<< " 6 - перенести элементы по критерию на другой склад\n"
			<< " 7 - сводка по складу\n\n"
			<< " 0 - назад\n\n";

		cout << "> ";

		switch (get_cmd())
		{
		case '1':
		{
			Product el;
			cin >> el;
			while (-1 != storage.indexof_binary(
				[el](auto e)
			{
				return el.productID - e.productID;
			}))
			{
				cout << "Продукт с таким ID уже имеется на складе. Ввести другой ID? В противном случае элемент будет перезаписан (y/n): ";
				if (check_yn())
				{
					input(el.productID);
				}
				else 
				{
					// Удаление продукта с таким же ID
					catalogue.products.remove_if(
						[el, id](auto p)
					{
						return p.storageID == id && p.productID == el.productID;
					});
					storage.remove_if(
						[el](auto p)
					{
						return p.productID == el.productID;
					});
				}
			}
			el.storageID = id;
			storage.add(el);
			storage.sort([](auto a, auto b)
			{
				return a.productID < b.productID;
			});
			catalogue.products.add(el);
			save(catalogue);
			break;
		}
		case '2':
			storage.print();
			break;
		case '3':
			storage.select(get_criteria()).print();
			break;
		case '4':
			storage.select(get_criteria()).print(get_fname());
			break;
		case '5':
		{
			Predicate p = get_criteria();
			storage.remove_if(p);
			catalogue.products.remove_if(
				[p, id](const Product& product)
			{
				return product.storageID == id && p(product);
			});
			save(catalogue);
			break;
		}
		case '6':
		{
			cout << "Введите ID склада, на который нужно переместить товары (0 - назад): ";
			int new_id;
			input(new_id);

			if (-1 == catalogue.storages.indexof_binary(
				[new_id](const Storage& s)
			{
				return new_id - s.id;
			}))
			{
				cout << "Склада с таким ID нет. Создать? (y/n)";
				if (!check_yn())
				{
					new_id = 0;
				}
				else
				{
					Storage s;
					input(s);
					catalogue.storages.add(s);
				}
			}

			if (new_id > 0)
			{
				// Получение критерия переноса
				Predicate p = get_criteria();
				// Выбор элементов
				Products selected = storage.select(p);
				// Удаление со старого склада
				storage.remove_if(p);
				// Перемещение
				catalogue.products.forEach(
					[p, id, new_id](Product& product)
				{
					if (product.storageID == id && p(product))
					{
						product.storageID = new_id;
					}
				});

				save(catalogue);
			}
			break;
		}
		case '7':
		{
			int types = storage.count();
			unsigned long overall_price = 0;
			storage.forEach(
				[&overall_price](const Product& p)
			{
				cout << "Всего " << p.count << " единиц товара '" << p.name << "'\n";
				overall_price += p.price * p.count;
			});
			cout << "Различных видов товаров:      " << types << "\n"
				 << "Общая стоимость всех товаров: " << overall_price << "\n\n";
			break;
		}
		case '0':
			return;
		default:
			cout << "Неизвестная команда\n";
			break;
		}
	}
}