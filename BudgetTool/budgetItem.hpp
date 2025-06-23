/**
 * @file budgetItem.hpp
 * @brief Defines the budgetItem class for representing income and expense items in the budget tool.
 *
 * The budgetItem class encapsulates the properties and behaviors of a single budget entry,
 * including its name, amount, type (income or expense), and frequency. It provides methods
 * for setting and retrieving these properties, as well as for calculating the monthly value
 * based on frequency and printing item details.
 *
 * @author Levi McLean (LeviM0323)
 * @date June 23rd, 2025
 */

#include <iostream>
#include <string>

using namespace std;

/**
 * @class budgetItem
 * @brief Represents a single budget item (income or expense).
 */
class budgetItem {
private:
	string name = "Undefined";   ///< Name of the budget item
	double amount = 0;           ///< Amount of the item (in dollars)
	bool expense = false;        ///< True if item is an expense, false if income
	int frequency = 0;           ///< Frequency code: 1=weekly, 2=bi-weekly, 3=monthly, 4=yearly

public:
/**
  * @brief Default constructor. Initializes with default values.
  */
	budgetItem() : name("Undefined"), amount(0), expense(false), frequency(0) {}

/**
  * @brief Parameterized constructor.
  * @param n Name of the item
  * @param a Amount of the item
  * @param e True if expense, false if income
  * @param f Frequency code (1=weekly, 2=bi-weekly, 3=monthly, 4=yearly)
  */
	budgetItem(string n, double a, bool e, int f) : name(n), amount(a), expense(e), frequency(f) {}

	/**
  * @brief Gets the name of the item.
  * @return The name string.
  */
	string getName() const { return name; }

/**
  * @brief Gets the amount of the item.
  * @return The amount as a double.
  */
	double getAmount() const { return amount; }

/**
  * @brief Checks if the item is an expense.
  * @return True if expense, false if income.
  */
	bool isExpense() const { return expense; }

/**
  * @brief Gets the frequency code of the item.
  * @return The frequency code (1=weekly, 2=bi-weekly, 3=monthly, 4=yearly).
  */
	int getFrequency() const { return frequency; }

/**
  * @brief Sets the name of the item.
  * @param n The new name.
  */
	void setName(string n) { name = n; }

/**
  * @brief Sets the amount of the item.
  * @param a The new amount.
  */
	void setAmount(double a) { amount = a; }

/**
  * @brief Marks the item as an expense.
  */
	void setExpense() { expense = true; }

/**
  * @brief Marks the item as income.
  */
	void setIncome() { expense = false; }

/**
  * @brief Sets the frequency code of the item.
  * @param f The frequency code (1=weekly, 2=bi-weekly, 3=monthly, 4=yearly).
  */
	void setFrequency(int f) { frequency = f; }

/**
  * @brief Converts the item's amount to a monthly value based on frequency.
  *        Modifies the amount in place.
  * @param f The frequency code (1=weekly, 2=bi-weekly, 3=monthly, 4=yearly).
  * @return The monthly value as a double.
  */
	double calculateMonthlyValue(int f) {
		if (f == 1) {
			amount *= 4.3;
		}
		else if (f == 2) {
			amount *= 2;
		}
		else if (f == 3) {
			return amount; // already monthly value
		}
		else {
			amount /= 12;
		}
		return amount;
	}

/**
  * @brief Prints the details of the budget item to the standard output.
  */
	void printItem() {
		cout << "Name: " << name << endl;
		cout << "Amount: $" << amount << endl;

		if (expense == 0) {
			cout << "Type: Income" << endl;
		}
		else {
			cout << "Type: Expense" << endl;
		}

		if (frequency == 1) {
			cout << "Frequency: weekly" << endl;
		}
		else if (frequency == 2) {
			cout << "Frequency: bi-weekly" << endl;
		}
		else if (frequency == 3) {
			cout << "Frequency: monthly" << endl;
		}
		else {
			cout << "Frequency: yearly" << endl;
		}

		cout << endl;
	}
};