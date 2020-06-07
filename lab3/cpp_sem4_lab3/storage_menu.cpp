
#include "menus.h"
#include "utils.h"

static Predicate get_criteria()
{
	cout << " �������� �������� ������:\n"
		<< "\ta - ���\n"
		<< " \t1 - �� ���� ������\n"
		<< " \t2 - �������� �� �����\n"
		<< " \t3 - �������� �� �������\n"
		<< " \t4 - � ���������� �� �����\n"
		<< " \t5 - � ���������� �� �����\n"
		<< " \t6 - ���� �� �����\n"
		<< " \t7 - ���� �� �����\n"
		<< " \t8 - ���� �������� �� �����\n"
		<< " \t9 - ���� �������� �� �����\n"
		<< " \t0 - ���c�������� �� ������ " << Date::get_today() << "\n"
		<< "\n\tr - ��������� � ����"
		<< "\n\n> ";

	while (true)
	{
		char c = get_cmd();
		if (c > '0' && c <= '9')
		{
			cout << "������� ��������: ";
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
			cout << "��� ������ ��������. �������� ����\n";
			break;
		}
	}
}

void storage_menu(StorageCatalogue& catalogue, int id)
{
	// �������� �������� � ����� ������
	Products storage = catalogue.products.select(
		[id](const Product& p)
	{
		return p.storageID == id;
	});

	while (true)
	{
		cout
			<< " 1 - �������� �������\n"
			<< " 2 - ���������� ���������� ������\n"
			<< " 3 - ���������� �������� �� ��������\n"
			<< " 4 - ������� �������� �� �������� � ����\n"
			<< " 5 - ������� �������� �� ��������\n"
			<< " 6 - ��������� �������� �� �������� �� ������ �����\n"
			<< " 7 - ������ �� ������\n\n"
			<< " 0 - �����\n\n";

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
				cout << "������� � ����� ID ��� ������� �� ������. ������ ������ ID? � ��������� ������ ������� ����� ����������� (y/n): ";
				if (check_yn())
				{
					input(el.productID);
				}
				else 
				{
					// �������� �������� � ����� �� ID
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
			cout << "������� ID ������, �� ������� ����� ����������� ������ (0 - �����): ";
			int new_id;
			input(new_id);

			if (-1 == catalogue.storages.indexof_binary(
				[new_id](const Storage& s)
			{
				return new_id - s.id;
			}))
			{
				cout << "������ � ����� ID ���. �������? (y/n)";
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
				// ��������� �������� ��������
				Predicate p = get_criteria();
				// ����� ���������
				Products selected = storage.select(p);
				// �������� �� ������� ������
				storage.remove_if(p);
				// �����������
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
				cout << "����� " << p.count << " ������ ������ '" << p.name << "'\n";
				overall_price += p.price * p.count;
			});
			cout << "��������� ����� �������:      " << types << "\n"
				 << "����� ��������� ���� �������: " << overall_price << "\n\n";
			break;
		}
		case '0':
			return;
		default:
			cout << "����������� �������\n";
			break;
		}
	}
}