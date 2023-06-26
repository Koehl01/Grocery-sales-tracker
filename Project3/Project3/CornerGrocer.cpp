/*
* Author: Chris Koehl
* Date: 6/25/23
* Assignment: Project 3
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <map>

using namespace std;

#include "Groceries.h"

//function descriptions
void OpenFile(ifstream &inFS);
void CreateDatFile(ofstream &outFS, Groceries &groceries);
void AddAllGroceries(ifstream &inFS, Groceries &groceries);
void DisplayWelcome();
void DisplayMainMenu();
void GetMenuSelection(char &menuSelection);
void HandleOptionOne(Groceries& groceries);
void HandleOptionTwo(Groceries& groceries);
void HandleOptionThree(Groceries& groceries);
void ToLower(string &stringToLower);
void DisplayFarewell();

int main() {
	//local variables
	ifstream inFS;
	ofstream outFS;
	//custom groceries class handling groceries map
	Groceries groceries;
	char menuSelection = 0;

	//inital file read and dat file creation
	OpenFile(inFS);
	AddAllGroceries(inFS, groceries);
	CreateDatFile(outFS, groceries);

	DisplayWelcome();

	//main program loop while user doesnt choose to exit
	while (menuSelection != '4') {
		DisplayMainMenu();
		GetMenuSelection(menuSelection);
		switch (menuSelection){
			case '1': HandleOptionOne(groceries);
				break;
			case '2': HandleOptionTwo(groceries);
				break;
			case '3': HandleOptionThree(groceries);
				break;
			default:
				break;
		}
	}

	DisplayFarewell();

	return 0;
}

//Function definitions

//Opens InputFile.txt
void OpenFile(ifstream &inFS) {
	//opens file and prints error if not
	inFS.open("InputFile.txt");
	if (!inFS.is_open()) {
		cout << "Could not open file InputFile.txt" << endl;
	}
}

//Adds all inputFile items to the groceries map
void AddAllGroceries(ifstream &inFS, Groceries &groceries) {
	string groceryItem;
	while (!inFS.fail()) {
		inFS >> groceryItem;
		ToLower(groceryItem);
		groceries.AddToMap(groceryItem);
	}
}

//Using groceries map to create a backup dat file
void CreateDatFile(ofstream& outFS, Groceries& groceries) {
	outFS.open("Frequency.dat");
	if (!outFS.is_open()) {
		cout << "Could not open file Frequency.dat" << endl;
	}
	for (auto groceryItem : groceries.GetAllGroceries()) {
		outFS << groceryItem.first << " " << groceryItem.second << endl;
	}
}

//Display a welcome message to the user
void DisplayWelcome() {
	cout << "Hello and welcome the Corner Grocer Produce Lookup tool" << endl;
	cout << "*******************************************************" << endl;
	cout << endl;
}

//Main program menu
void DisplayMainMenu() {
	cout << "----------SELECT AN OPTION------------" << endl;
	cout << endl;
	cout << "1) Find amount sold by item name." << endl;
	cout << "2) List all items purchased." << endl;
	cout << "3) Display sales chart." << endl;
	cout << "4) Exit program." << endl;
	cout << endl;
	cout << "Selection: ";
}

//Uses a while loop to verify user input
void GetMenuSelection(char &menuSelection) {
	cin >> menuSelection;
	while (menuSelection != '1' && menuSelection != '2' && menuSelection != '3' && menuSelection != '4') {
		cout << endl;
		cout << "      [ERROR: Invalid Selection]" << endl;
		cout << endl;

		cin.clear();
		cin.ignore(100, '\n');

		DisplayMainMenu();
		cin >> menuSelection;
	}
	cout << endl;
}

//Also uses a while loop in case the user wants to look for multiple items before returning to main menu.
//For ease of use all items have been converted to lower case.
void HandleOptionOne(Groceries& groceries) {
	string groceryItem;
	char continueSelection = 'Y';
	while (toupper(continueSelection) != 'N') {
		cout << "Please enter the item you wish to look up." << endl;
		cout << endl;
		cin >> groceryItem;
		try {
			cout << "Item: " << groceryItem << endl;
			ToLower(groceryItem);
			cout << "Quantity Sold: " << groceries.GetAmountByName(groceryItem) << endl;
		}
		catch (exception e) {
			cout << "That item has not been sold." << endl;
		}

		cout << "Would you like to look up another item (Y/N): ";
		cin >> continueSelection;
		while (toupper(continueSelection) != 'Y' && toupper(continueSelection) != 'N') {
			cout << endl;
			cout << "      [ERROR: Invalid Selection]" << endl;
			cout << endl;

			cin.clear();
			cin.ignore(100, '\n');

			cout << "Would you like to look up another item (Y/N): ";
			cin >> continueSelection;
		}
	}
}

//dispays a formatted output of the groceries map consisting of the name and quatity sold
void HandleOptionTwo(Groceries &groceries) {
	cout << "     ITEM       AMT SOLD" << endl;
	cout << "  =======================" << endl;
	for (auto groceryItem : groceries.GetAllGroceries()) {
		cout << "  || " << setw(15) << left << groceryItem.first << setw(3) << left << groceryItem.second << "||" << endl;
	}
	cout << "  =======================" << endl;
	cout << endl;
}

//displays the same information but in a barchart format.
void HandleOptionThree(Groceries &groceries) {
	int graphHeight = 10;
	string graphString = "";

	for (int i = graphHeight; i >= 0; i--) {
		string row = "";
		for (auto groceryItem : groceries.GetAllGroceries()) {
			if (groceryItem.second > i) {
				row += "|%%|";
			}
			else if (groceryItem.second < i) {
				row += "....";
			}
			else {
				row += " __ ";
			}
		}

		cout << setw(2) << i << "|." << row << endl;
	}
	cout << "------------------------------------------------------------------------------------" << endl;
	
	int i = 0;
	while (i < 12) {
		cout << "    ";
		for (auto groceryItem : groceries.GetAllGroceries()) {	
			try {
				cout << " " << groceryItem.first.at(i) << "  ";
			}
			catch (exception e) {
				cout << "    ";
			}

		}
		cout << endl;
		i++;
	}

}

//helper function to convert input to lowercase for easier useability
void ToLower(string &stringToLower) {

	for (int i = 0; i < stringToLower.length(); i++) {
		stringToLower[i] = tolower(stringToLower[i]);
	}
	
}

//farewell message to users upon exit
void DisplayFarewell() {
	cout << "*********************************************************" << endl;
	cout << "Thank you for using the Corner Grocer Produce Lookup tool" << endl;
	cout << "                       Goodbye!";

}
