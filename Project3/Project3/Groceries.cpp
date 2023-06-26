#include <iostream>
#include <string>
#include <map>
using namespace std;

#include "Groceries.h"

void Groceries::AddToMap(string groceryItem) {
	if (groceriesMap.count(groceryItem) == 0) {
		groceriesMap.emplace(groceryItem, 1);
	}
	else {
		groceriesMap.at(groceryItem) = groceriesMap.at(groceryItem) + 1;
	}
}

int Groceries::GetAmountByName(string groceryItem) {
	return groceriesMap.at(groceryItem);
}

map<string, int> Groceries::GetAllGroceries() {
	return groceriesMap;
}