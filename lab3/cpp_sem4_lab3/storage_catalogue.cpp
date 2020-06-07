#include "storage_catalogue.h"

void StorageCatalogue::toDisk(string path) const
{
	storages.print(path + "_storages.txt");
	products.print(path + "_products.txt");
}

void StorageCatalogue::fromDisk(string path)
{
	storages.fill(path + "_storages.txt");
	products.fill(path + "_products.txt");
}
