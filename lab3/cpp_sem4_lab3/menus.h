#pragma once

#include "data.h"
#include "product.h"
#include "storage_catalogue.h"

void start_menu();

void catalogue_menu(StorageCatalogue& catalogue);

void storage_menu(StorageCatalogue& catalogue, int id);