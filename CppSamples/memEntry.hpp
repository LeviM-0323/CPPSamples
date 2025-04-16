/*
Author: Levi McLean (LeviM_0323)
File: memEntry.hpp
Created: April 8th, 2025
Purpose: Class for a Memory Entry object
*/

#include <iostream>

using namespace std;

class memEntry {
private:
	double monthlyPayment = 0.0, housePrice = 0.0, downPayment = 0.0, loanAmount = 0.0, interestRate = 0.0;
	int loanYears = 0, numPayments = 0, frequencyChoice;
public:
	memEntry(double mp, double hp, double dp, double la, double ir, int ly, int np, int fc) : monthlyPayment(mp), housePrice(hp), 
		downPayment(dp), loanAmount(la), interestRate(ir), loanYears(ly), numPayments(np), frequencyChoice(fc) {} //since I'll only ever use all private variables to initialize, this it the only intializer I need
	
	//getters
	double getMonthlyPayment() const {
		return monthlyPayment;
	}

	double getHousePrice() const {
		return housePrice;
	}

	double getDownPayment() const {
		return downPayment;
	}

	double getLoanAmount() const {
		return loanAmount;
	}

	double getInterestRate() const {
		return interestRate;
	}

	int getLoanYears() const {
		return loanYears;
	}

	int getNumPayments() const {
		return numPayments;
	}

	int getFrequencyChoice() const {
		return frequencyChoice;
	}

	//print method
	void print() {
		cout << "House Price: $" << housePrice << endl;
		cout << "Downpayment: $" << downPayment << endl;
		cout << "Loan Amount: $" << loanAmount << endl;
		cout << "Interest Rate: " << interestRate << "%" << endl;
		cout << "Loan Term: " << loanYears << " years" << endl;
		cout << "Loan Frequency: " << frequencyChoice << endl;
		cout << "Monthly Payment: $" << monthlyPayment << endl << endl;
	}
};