#ifndef GROCERIES_H
#define GROCERIES_H

class Groceries {
	public:

		void AddToMap(string groceryItem);
		int GetAmountByName(string groceryItem);
		map<string, int> GetAllGroceries();
	private:
		map<string, int> groceriesMap;

};
#endif // !GROCERIES_H

