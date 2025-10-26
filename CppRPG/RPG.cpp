#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <thread>
#include "entity.hpp"

int main() {
	string name;
	int currentLevel = 1;
	int killsToProgress = 2 + (currentLevel - 1) * (currentLevel - 1);
	Entity testEnenmy("Test Enemy", "enemy");
	Entity player("Player", "player");

	do {
		cout << "Player health: " << player.getCurrentHealth() << endl;
		cout << "Enemy Health: " << testEnenmy.getCurrentHealth() << endl;
		cout << endl;

		player.attack(testEnenmy);
	} while (testEnenmy.getCurrentHealth() >= 0);
	/*cout << "Create your character!" << endl;
	cout << "Character name: ";
	getline(cin, name);
	Entity player(name, "player");
	cout << endl;
	cout << "You will start as a level 1, your stats are as follows: " << endl;
	player.printStats();
	cout << "The goal is to reach the tower at level 10, you will fight enemies along the way. Your character will NOT save accross runs." << endl;*/
}