/**
 * @file budgetItem.hpp
 * @brief Defines the budgetItem class for representing income and expense items in the budget tool.
 *
 * The budgetItem class encapsulates the properties and behaviors of a single budget entry,
 * including its name, amount, type (income or expense), and frequency. It provides methods
 * for setting and retrieving these properties, as well as for calculating the monthly value
 * based on frequency and printing item details.
 *
 * @author Levi McLean (LeviM0323 on Github)
 * @date June 23rd, 2025
 */

#include <iostream>
#include <string>
#include <iomanip>

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
		cout << "|----| " << name << " ";
		cout << "|-----| $" << amount << " ";

		if (frequency == 1) {
			cout << "|-----| Weekly ";
		}
		else if (frequency == 2) {
			cout << "|-----| Bi-weekly ";
		}
		else if (frequency == 3) {
			cout << "|-----| Monthly ";
		}
		else {
			cout << "|-----| Yearly ";
		}

		if (expense == 0) {
			cout << "|-----| Income |----|";
		}
		else {
			cout << "|------| Expense |----|";
		}
		cout << endl;
	}

	/**
	* @brief Prints the details of the budget item to the standard output with alignment.
	* @param index The index of the item in the budget list (default: -1).
	*/
	void printItem(int index = -1) const {
		cout << "| " << setw(2) << (index >= 0 ? to_string(index) : "")
			 << "| " << setw(18) << left << name
			 << "| $" << setw(9) << right << fixed << setprecision(2) << amount << left
			 << "| " << setw(10);

		switch (frequency) {
			case 1: cout << "Weekly"; break;
			case 2: cout << "Bi-weekly"; break;
			case 3: cout << "Monthly"; break;
			case 4: cout << "Yearly"; break;
			default: cout << "Unknown"; break;
		}

		cout << "| " << setw(8) << (expense ? "Expense" : "Income") << "|" << endl;
	}
};