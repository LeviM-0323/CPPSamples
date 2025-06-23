/**
 * @file BudgetTool.cpp
 * @brief Main source file for the Budget Tool application.
 *
 * This application allows users to manage a list of budget items, including both income and expenses.
 * Users can add new items, view all items with totals, and adjust existing items (name, amount, type, frequency).
 * The application provides a simple text-based menu for user interaction.
 *
 * @author Levi McLean (LeviM0323 on GitHub)
 * @date June 23rd, 2025
 */

#include "budgetItem.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>

int menuOption;
vector<budgetItem> budgetList;

/**
 * @brief Prints the main menu and gets the user's menu option.
 */
void printMenu() {
	cout << "1. Add income/expense item\n";
	cout << "2. View income/expenses\n";
	cout << "3. Adjust income/expense item\n";
	cout << "4. Generate random items\n";
	cout << "5. Clear budget items\n";
	cout << "6. Sort items\n";
	cout << "0. Exit\n";
	cout << "Select an option: ";
	cin >> menuOption;
	system("cls");
}

/**
 * @brief Adds a new budget item (income or expense) to the budget list.
 *
 * Prompts the user for item name, amount, type (income or expense), and frequency.
 * Performs basic error checking for type and frequency.
 */
void addItem() {
	budgetItem newItem;
	string itemName;
	double itemAmount;
	int itemExpense;
	int itemFrequency;

	cout << "------------------------Adding Item------------------------\n";
	cout << "Item name: ";
	getline(cin, itemName);
	newItem.setName(itemName);

	cout << "Item amount: $";
	cin >> itemAmount;
	newItem.setAmount(itemAmount);

	cout << "Is the item income? (1 for yes, 0 for no): ";
	cin >> itemExpense;
	if (itemExpense == 0) {
		newItem.setExpense();
	}
	else if (itemExpense == 1) {
		newItem.setIncome();
	}
	else {
		cout << "Incorrect value, assuming expense...";
		newItem.setExpense();
	}

	cout << "Item frequency (1 for weekly, 2 for bi-weekly, 3 for monthly, 4 for yearly): ";
	cin >> itemFrequency;
	if (itemFrequency == 1) {
		newItem.setFrequency(1);
		newItem.calculateMonthlyValue(1);
	}
	else if (itemFrequency == 2) {
		newItem.setFrequency(2);
		newItem.calculateMonthlyValue(2);
	}
	else if (itemFrequency == 3) {
		newItem.setFrequency(3);
	}
	else if (itemFrequency == 4) {
		newItem.setFrequency(4);
		newItem.calculateMonthlyValue(4);
	}
	else {
		cout << "Incorrect value, assuming monthly...";
		newItem.setFrequency(3);
	}

	cout << endl;
	budgetList.push_back(newItem);
}

/**
 * @brief Displays all budget items and shows totals for income, expenses, and remaining budget.
 *
 * Iterates through the budget list, prints each item, and calculates totals.
 */
void viewItems() {
	cout << "------------------------Viewing Items------------------------\n";
	double totalIncome = 0.00, totalExpenses = 0.00, remainingMonthly = 0.00;
	for (int i = 0; i < budgetList.size(); i++) {
		budgetItem currentItem = budgetList.at(i);
		cout << "Item #" << i << endl;
		currentItem.printItem();

		if (currentItem.isExpense()) {
			totalExpenses += currentItem.getAmount();
		}
		else {
			totalIncome += currentItem.getAmount();
		}
		remainingMonthly = totalIncome - totalExpenses;
	}

	cout << "Total income: $" << totalIncome << endl;
	cout << "Total expenses: $" << totalExpenses << endl;
	cout << "Remaining Monthly: $" << remainingMonthly << endl;
	cout << "Budget used %" << totalExpenses / totalIncome * 100 << endl << endl;
}

/**
 * @brief Allows the user to adjust an existing budget item's name, amount, type, or frequency.
 *
 * Prompts the user to select an item and what to change. Performs error checking for type and frequency.
 */
void adjustItem() {
	int itemToAdjust, thingToAdjust;
	string newName;
	double newAmount;
	int newFrequency;

	viewItems();
	cout << "Enter item # to adjust: ";
	cin >> itemToAdjust;
	cout << "What to change? (1 for name, 2 for amount, 3 for item type (expense/income), 4 for frequency: ";
	cin >> thingToAdjust;

	if (thingToAdjust == 1) {
		cout << "Enter new name: ";
		getline(cin, newName);
		budgetList.at(itemToAdjust).setName(newName);
	}
	else if (thingToAdjust == 2) {
		cout << "Enter new amount: $";
		cin >> newAmount;
		budgetList.at(itemToAdjust).setAmount(newAmount);
	}
	else if (thingToAdjust == 3) {
		int expenseInput;
		cout << "Is the item income? (1 for yes, 0 for no): ";
		cin >> expenseInput;
		if (expenseInput == 0) {
			budgetList.at(itemToAdjust).setExpense();
		}
		else if (expenseInput == 1) {
			budgetList.at(itemToAdjust).setIncome();
		}
		else {
			cout << "Incorrect value, ignoring change...";
		}
	} 
	else if (thingToAdjust == 4) {
		cout << "Enter new frequency (1 for weekly, 2 for bi-weekly, 3 for monthly, 4 for yearly): ";
		cin >> newFrequency;
		if (newFrequency == 1) {
			budgetList.at(itemToAdjust).setFrequency(1);
			budgetList.at(itemToAdjust).calculateMonthlyValue(1);
		}
		else if (newFrequency == 2) {
			budgetList.at(itemToAdjust).setFrequency(2);
			budgetList.at(itemToAdjust).calculateMonthlyValue(2);
		}
		else if (newFrequency == 3) {
			budgetList.at(itemToAdjust).setFrequency(3);
		}
		else if (newFrequency == 4) {
			budgetList.at(itemToAdjust).setFrequency(4);
			budgetList.at(itemToAdjust).calculateMonthlyValue(4);
		}
		else {
			cout << "Incorrect value, assuming monthly..." << endl;
			budgetList.at(itemToAdjust).setFrequency(3);
		}
	}
	cout << endl;
}

/**
 * @brief Generates a number of random budget items and adds them to the budget list.
 *
 * Prompts the user for the number of items to generate. Each item will have a random name,
 * amount, type (income or expense), and frequency.
 */
void randomItems() {
	cout << "------------------------Generating Items------------------------\n";
	int numItems;
	cout << "How many random items? ";
	cin >> numItems;

	string expenseNames[] = { "Rent", "Groceries", "Utilities", "Insurance", "Dining", "Phone", "Car", "Weed" };
	string incomeNames[] = { "Salary", "Bonus", "Gift", "Loan" };
	int expenseNamesCount = sizeof(expenseNames) / sizeof(expenseNames[0]);
	int incomeNamesCount = sizeof(incomeNames) / sizeof(incomeNames[0]);

	srand(static_cast<unsigned int>(time(0)));
	
	for (int i = 0; i < numItems; i++) {
		string name;
		double amount = (rand() % 2000) + (rand() % 100) / 100.0 + 1.0;
		bool isExpense = rand() % 2;
		int frequency = (rand() % 4) + 1;

		if (isExpense == 0) {
			name = incomeNames[rand() % incomeNamesCount];
		}
		else {
			name = expenseNames[rand() % expenseNamesCount];
		}

		budgetItem item(name, amount, isExpense, frequency);

		if (frequency == 1 || frequency == 2 || frequency == 4) {
			item.calculateMonthlyValue(frequency);
		}

		budgetList.push_back(item);
	}

	cout << numItems << " random items added.\n\n";
}

/**
 * @brief Clears the vector of budget items
 *
 * Prompts the user to confirm, then deletes all items in the vector, IRREVERSIBLE
 */
void clearList() {
	string confirmString;
	cout << "------------------------Deleting Items------------------------\n";
	cout << "Type 'confirm' to continue: ";
	getline(cin, confirmString);
	if (confirmString == "confirm") {
		cout << budgetList.size() << " items removed." << endl << endl;
		budgetList.clear();
	}
	else {
		cout << "Incorrect input, not deleted." << endl << endl;
	}
}

/**
 * @brief Sort the vector by user provided token
 *
 * Prompts user for token to sort by, then sorts the vector by that token
 */
void sortItems() {
	int sortOption;
	cout << "------------------------Sorting Items------------------------\n";
	cout << "What to sort by? (1 for name, 2 for amount, 3 for type, 4 for frequency): ";
	cin >> sortOption;

	if (sortOption == 1) {
		sort(budgetList.begin(), budgetList.end(), 
			[](const budgetItem& a, const budgetItem& b) {
				return a.getName() < b.getName();
			});
	}
	else if (sortOption == 2) {
		sort(budgetList.begin(), budgetList.end(),
			[](const budgetItem& a, const budgetItem& b) {
				return a.getAmount() < b.getAmount();
			});
	}
	else if (sortOption == 3) {
		sort(budgetList.begin(), budgetList.end(),
			[](const budgetItem& a, const budgetItem& b) {
				return a.isExpense() < b.isExpense();
			});
	}
	else if (sortOption == 4) {
		sort(budgetList.begin(), budgetList.end(),
			[](const budgetItem& a, const budgetItem& b) {
				return a.getFrequency() < b.getFrequency();
			});
	}
	else {
		cout << "Incorrect option, no sorting completed\n";
	}
	cout << endl;
}

/**
 * @brief Saves items to a text file
 *
 * Saves each item in vector to a text file for easy loaing later
 */
void saveItems() {
	ofstream outFile("data.txt");
	outFile << budgetList.size() << endl;
	for (const budgetItem& item : budgetList) {
		outFile << item.getName() << " " << item.getAmount() << " " << item.isExpense() << " " << item.getFrequency() << endl;
	}
	outFile.close();
}

/**
 * @brief Load the data from the text file upon launch
 *
 * Loads data from a text file and makes entries with the corresponding data, then pushes entries to a vector
 */
void loadItems() {
	ifstream inFile("data.txt");

	if (!inFile) {
		cout << "No previous data found. Starting fresh..." << endl;
		return;
	}

	size_t memSize;
	inFile >> memSize; //number of entries

	for (size_t i = 0; i < memSize; i++) {
		double amount;
		string name;
		int expense;
		int frequency;

		inFile >> name >> amount >> expense >> frequency;

		budgetItem newItem(name, amount, expense, frequency);
		budgetList.push_back(newItem);
	}
}

/**
 * @brief Main entry point for the budget tool application.
 *
 * Handles the main menu loop and user interaction.
 * @return int Returns 0 on successful execution, 1 on error.
 */
int main() {
	cout << R"(

                    ___          _____          ___           ___                                            ___           ___                   
     _____         /__/\        /  /::\        /  /\         /  /\          ___                  ___        /  /\         /  /\                  
    /  /::\        \  \:\      /  /:/\:\      /  /:/_       /  /:/_        /  /\                /  /\      /  /::\       /  /::\                 
   /  /:/\:\        \  \:\    /  /:/  \:\    /  /:/ /\     /  /:/ /\      /  /:/               /  /:/     /  /:/\:\     /  /:/\:\    ___     ___ 
  /  /:/~/::\   ___  \  \:\  /__/:/ \__\:|  /  /:/_/::\   /  /:/ /:/_    /  /:/               /  /:/     /  /:/  \:\   /  /:/  \:\  /__/\   /  /\
 /__/:/ /:/\:| /__/\  \__\:\ \  \:\ /  /:/ /__/:/__\/\:\ /__/:/ /:/ /\  /  /::\              /  /::\    /__/:/ \__\:\ /__/:/ \__\:\ \  \:\ /  /:/
 \  \:\/:/~/:/ \  \:\ /  /:/  \  \:\  /:/  \  \:\ /~~/:/ \  \:\/:/ /:/ /__/:/\:\            /__/:/\:\   \  \:\ /  /:/ \  \:\ /  /:/  \  \:\  /:/ 
  \  \::/ /:/   \  \:\  /:/    \  \:\/:/    \  \:\  /:/   \  \::/ /:/  \__\/  \:\           \__\/  \:\   \  \:\  /:/   \  \:\  /:/    \  \:\/:/  
   \  \:\/:/     \  \:\/:/      \  \::/      \  \:\/:/     \  \:\/:/        \  \:\               \  \:\   \  \:\/:/     \  \:\/:/      \  \::/   
    \  \::/       \  \::/        \__\/        \  \::/       \  \::/          \__\/                \__\/    \  \::/       \  \::/        \__\/    
     \__\/         \__\/                       \__\/         \__\/                                          \__\/         \__\/                  

)";

	loadItems();
	printMenu();

	while (true) {
		switch (menuOption) {
		case 0:
			saveItems();
			exit(1);
			break;
		case 1:
			addItem();
			printMenu();
			break;
		case 2:
			viewItems();
			printMenu();
			break;
		case 3:
			adjustItem();
			printMenu();
			break;
		case 4:
			randomItems();
			printMenu();
			break;
		case 5:
			clearList();
			printMenu();
			break;
		case 6:
			sortItems();
			printMenu();
			break;
		//case 7:
		//	break;
		//case 8:
		//	break;
		//case 9:
		//	break;
		default:
			printMenu();
			break;
		}
	}
	return 0;
}