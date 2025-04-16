/*
Author: Levi McLean (LeviM_0323)
File: FakeGambling.cpp
Created: April 11th, 2025
Purpose: Just a fun project made to replicate casino slot machines
*/


#include <iostream>
#include <random>
#include <iomanip>
#include <thread>
#include <string>
#include <chrono>
#include <sstream>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

using namespace std;

string formatCurrency(double value) {
	ostringstream oss;
	oss << fixed << setprecision(2) << value;
	return oss.str();
}

int getScreenWidth() {
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		return csbi.srWindow.Right - csbi.srWindow.Left + 1;
	}
#else
	struct winsize w;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
		return w.ws_col;
	}
#endif
	return 80;
}

void centerText(const string& text) {
	int width = getScreenWidth();
	int padding = (width - text.length()) / 2;
	if (padding > 0) {
		cout << string(padding, ' ') << text;
	}
	else {
		cout << text;
	}
}

#ifdef _WIN32
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
#else
void setColor(int color) {
    cout << "\033[" << color << "m";
}
#endif

void resetColor() {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to default (white text on black background)
#else
    cout << "\033[0m"; // Reset all attributes (foreground, background, and styles)
#endif
}

void uselessLoadingScreen(int loops) {
	const string frames[] = { "[|]", "[/]", "[-]", "[\\]" };
	for (int i = 0; i < loops * 4; i++) {
		system("cls");
		centerText("Loading " + frames[i % 4] + "\n");
		this_thread::sleep_for(chrono::milliseconds(100));
	}
    system("cls");
}

string getSymbol(int num) {
	const string symbols[] = { "&", "X", "/", "7", "O", "#", "*" };
	return symbols[num - 1];
}

int getSymbolColor(int num) {
    const int colors[] = { 4, 2, 6, 1, 5, 3, 12 }; // Red, Green, Yellow, Blue, Magenta, Cyan, Bright Red
    return colors[num - 1];
}

void displayGrid(const vector<vector<int>>& grid) {
    centerText("+---+---+---+\n");
    for (const auto& row : grid) {
        string line = " |";
        for (int num : row) {
            setColor(getSymbolColor(num));
            line += getSymbol(num) + " ";
            resetColor();
            line += " |";
        }
        centerText(line + "\n");
        centerText("+---+---+---+\n");
    }
}

void spinAnimation(vector<vector<int>>& grid, mt19937& gen, uniform_int_distribution<int>& dist) {
    for (int frame = 0; frame < 10; frame++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                grid[i][j] = dist(gen);
            }
        }
        system("cls");
        centerText("Spinning...\n");
        displayGrid(grid);
        this_thread::sleep_for(chrono::milliseconds(150));
    }
}

bool checkWin(const vector<vector<int>>& grid, double bet, double& payout) {
    for (int i = 0; i < 3; i++) {
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) {
            payout = bet * 3; // Row match
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) {
            payout = bet * 3; // Column match
            return true;
        }
    }

    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
        payout = bet * 5; // Diagonal match
        return true;
    }
    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) {
        payout = bet * 5; // Diagonal match
        return true;
    }

    if (grid[0][0] == grid[0][2] && grid[0][0] == grid[2][0] && grid[0][0] == grid[2][2]) {
        payout = bet * 10; // Corners match
        return true;
    }

    return false; 
}

void mainMenu(double& balance, double& sessionNet) {
    while (true) {
        system("cls"); // Clear the screen
        setColor(3);
        centerText("Welcome to the Fake Gambling Game!\n");
        resetColor();
        centerText("---------------------Main Menu---------------------\n");
        centerText("1. Go to the Casino\n");
        centerText("2. Exit\n");
        centerText("---------------------------------------------------\n");
        centerText("Please select an option: ");

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            // Go to the casino
            return; // Exit the menu and return to the casino
        case 2:
            // Exit the game
            setColor(4);
            centerText("Thank you for playing! Goodbye!\n");
            resetColor();
            exit(0);
        default:
            setColor(4);
            centerText("Invalid choice. Please try again.\n");
            resetColor();
            this_thread::sleep_for(chrono::seconds(2)); // Pause before re-displaying the menu
        }
    }
}

int main() {
    double bet, payout, balance = 500.00, sessionNet = 0.00;

    while (true) {
        //mainMenu(balance, sessionNet); not quite ready for the main menu
        //cout << endl;

        if (balance == 0) {
            setColor(4);
            centerText("Balance has reached $0, go to the bank to get more money\n");
            resetColor();
            exit(1);
        }
        setColor(3);
        centerText("Welcome to the Fake Casino!\n");
        centerText("Currently the only game we have is slots\n");
        resetColor();
        centerText("---------------------Payouts-----------------------\n");
        centerText(" - Row or Column Match: 3:1\n");
        centerText(" - Diagonal Match: 5:1\n");
        centerText(" - Corners Match: 10:1\n");
        centerText("---------------------------------------------------\n");

        string balanceStr = "Balance: $" + formatCurrency(balance);
        string sessionStr = "Session: ";
        if (sessionNet > 0) {
            sessionStr += "+$" + formatCurrency(sessionNet);
        }
        else if (sessionNet < 0) {
            sessionStr += "-$" + formatCurrency(-sessionNet); // Avoid double negative
        }
        else {
            sessionStr += "$0.00";
        }

        // Center the formatted strings
        setColor(2);
        centerText(balanceStr + "\n");
        resetColor();
        if (sessionNet > 0) {
            setColor(2);
        }
        else if (sessionNet < 0) {
            setColor(4);
        }
        else {
            resetColor();
        }
        centerText(sessionStr + "\n");
        resetColor();

        centerText("Please enter your bet (minimum $0.10, maximum $20): ");

        do {
            cin >> bet;

            if (bet < 0.1 || bet > 20) {
                setColor(4);
                centerText("Bet must be greater than $0.10 and less than $20, please try again: ");
                resetColor();
            }
            if (balance < bet) {
                setColor(4);
                centerText("Bet larger than account balance, please try again: ");
                resetColor();
            }
        } while (bet < 0.1 || bet > 20 || balance < bet);

        balance -= bet;
        random_device randomDev;
        mt19937 gen(randomDev());
        uniform_int_distribution<int> dist(1, 7);

        vector<vector<int>> grid(3, vector<int>(3));

        spinAnimation(grid, gen, dist);
        system("cls");
        displayGrid(grid);

        if (checkWin(grid, bet, payout)) {
            balance += payout;
            sessionNet -= bet;
            sessionNet += payout;
            setColor(2);
            centerText("Congratulations! You won $" + formatCurrency(payout) + "!\n");
            resetColor();
        }
        else {
            sessionNet -= bet;
            setColor(4);
            centerText("Sorry, you lost. Better luck next time...\n");
            resetColor();
        }
        cout << endl;
    }
    return 0;
}