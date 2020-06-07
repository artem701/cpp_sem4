#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "product.h"
#include "storage.h"
#include "data.h"

using namespace std;

struct StorageCatalogue
{
	// Доступные склады
	Data<Storage> storages;
	// Совокупность товаров
	Data<Product> products;

	void toDisk(string path) const;
	void fromDisk(string path);
};