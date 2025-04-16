/*
Author: Levi McLean (LeviM_0323)
File: MortgageCalculator.cpp
Created: April 8th, 2025
Purpose: Main run logic
*/

/*
Master TODO list:
	[] Handle all possible errors
	[] Finalize formatting
	[] Validate user input (numbers aren't negative, downpayment meets a certain % of house price,
	   loan term maximum of 35 years, etc.)
	[] Fix Scientific notation in house price
	[] Github publication
*/

#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include "memEntry.hpp"

using namespace std; 

double monthlyPayment = 0.0, housePrice = 0.0, downPayment = 0.0, loanAmount = 0.0, interestRate = 0.0;
int loanYears = 0, numPayments = 0, frequencyChoice, menuChoice;
vector<memEntry> memEntries; //vector of previous calculations to print later

static void printMenu() {
	cout << R"(
___  ___           _                           _____       _            _       _             
|  \/  |          | |                         /  __ \     | |          | |     | |            
| .  . | ___  _ __| |_ __ _  __ _  __ _  ___  | /  \/ __ _| | ___ _   _| | __ _| |_ ___  _ __ 
| |\/| |/ _ \| '__| __/ _` |/ _` |/ _` |/ _ \ | |    / _` | |/ __| | | | |/ _` | __/ _ \| '__|
| |  | | (_) | |  | || (_| | (_| | (_| |  __/ | \__/| (_| | | (__| |_| | | (_| | || (_) | |   
\_|  |_/\___/|_|   \__\__, |\__,_|\__, |\___|  \____/\__,_|_|\___|\__,_|_|\__,_|\__\___/|_|   
                       __/ |       __/ |                                                      
                      |___/       |___/                                                       
		)" << endl;
	cout << "1. Calculate Mortgage" << endl;
	cout << "2. View Memory Entries" << endl;
	cout << "3. Clear Memory Entries" << endl;
	cout << "0. Save and quit" << endl;
	cout << "Select an option: ";
}

static double calcPayment() {
	cout << "Enter house price: $";
	cin >> housePrice;
	cout << endl << "Enter downpayment: $";
	cin >> downPayment;
	loanAmount = housePrice - downPayment;
	cout << endl << "Enter interest rate: ";
	cin >> interestRate;
	cout << endl << "Enter loan term (years): "; //handling monthly payments only for now
	cin >> loanYears;
	cout << endl << "(1) Monthly Payments (2) Bi-weekly Payments (3) Weekly Payments: ";
	cin >> frequencyChoice;

	switch (frequencyChoice) {
	case 1:
		numPayments = loanYears * 12;
		break;
	case 2:
		numPayments = loanYears * 26; // 26 bi-weekly payments a year
		break;
	case 3:
		numPayments = loanYears * 52;
		break;
	default:
		cout << "Invalid option, try again...";
		break;
	}

	double monthlyInterestRate = interestRate / 12 / 100; //convert yearly interest rate to rate per pay period
	double monthlyPayment = (loanAmount * monthlyInterestRate * pow(1 + monthlyInterestRate, numPayments)) / (pow(1 + monthlyInterestRate, numPayments) - 1);
	cout << endl << "Your monthly payment is: $" << monthlyPayment;

	//make new memory entry and push it to vector of memory entries
	memEntry newEntry = memEntry(monthlyPayment, housePrice, downPayment, loanAmount, interestRate, loanYears, numPayments, frequencyChoice);
	memEntries.push_back(newEntry);
	cout << endl << endl; // make it look nice, ok?

	return monthlyPayment;
}

static void printMemory() {
	for (int i = 0; i < memEntries.size(); i++) {
		cout << "Memory Entry #" << i << endl;
		memEntries.at(i).print();
	}
}

static void clearMemory() {
	memEntries.clear();
	cout << "All memory entries cleared, hope it wasn't important (~_^)";
}

static void saveData(const vector<memEntry>& memEntries) {
	ofstream outFile("data.txt");
	outFile << memEntries.size() << endl;
	for (const memEntry& mem : memEntries) {
		outFile << mem.getMonthlyPayment() << " " << mem.getHousePrice() << " " << mem.getDownPayment() << " " << mem.getLoanAmount() << " " << mem.getInterestRate() << " " << mem.getLoanYears() << " " << mem.getNumPayments() << " " << mem.getFrequencyChoice() << endl;
	}
	outFile.close();
}

static void loadData(vector<memEntry>& memEntries) {
	ifstream inFile("data.txt");

	if (!inFile) {
		cout << "No previous data found. Starting fresh..." << endl;
		return;
	}

	size_t memSize;
	inFile >> memSize; //number of entries

	for (size_t i = 0; i < memSize; i++) {
		double monthlyPayment, housePrice, downPayment, loanAmount, interestRate;
		int loanYears, numPayments, frequencyChoice;

		inFile >> monthlyPayment >> housePrice >> downPayment >> loanAmount >> interestRate >> loanYears >> numPayments >> frequencyChoice;
		
		memEntry newEntry(monthlyPayment, housePrice, downPayment, loanAmount, interestRate, loanYears, numPayments, frequencyChoice);
		memEntries.push_back(newEntry);
	}
}

int main() {
	loadData(memEntries);
	while (true) {
		printMenu();
		cin >> menuChoice;
		switch (menuChoice) {
		case 1:
			//calculate and print payment
			calcPayment();
			break;
		case 2:
			printMemory();
			break;
		case 3:
			clearMemory();
		case 0:
			saveData(memEntries);
			exit(1);
		default:
			cout << "Invalid choice, try again..." << endl;
		}
	}
}