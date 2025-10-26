#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <algorithm>
#include <vector>
#include "character.hpp"

using namespace std;

string playerName, characterName, race, characterClass, background, alignment;
vector<Character> characters;

static void viewCharacter(); //Function prototype to shut up compiler

static void clear() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

static int rollAbilityScore(mt19937_64& rng) {
	uniform_int_distribution<int> dist(1, 6);
	vector<int> rolls;
	for (int i = 0; i < 4; ++i) {
		rolls.push_back(dist(rng));
	}
	sort(rolls.begin(), rolls.end());
	return rolls[1] + rolls[2] + rolls[3];
}

static Character newCharacter() {
	clear();
	cout << "DnD 5e Character Creator" << endl;
	cout << "Enter player name: ";
	cin.ignore();
	getline(cin, playerName);
	cout << "Enter character name: ";
	getline(cin, characterName);
	cout << R"(+------------------| Races |------------------+
| Dwarf | Elf | Halfling | Human | Dragonborn | 
|  Gnome  | Half-Elf  | Half-Orc  |  Tielfing |
+---------------------------------------------+)";
	cout << endl;
	cout << "Choose a race: ";
	cin >> race;
	cout << R"(+-----------------------| Classes |----------------------+
| Barbarian | Bard |  Cleric | Druid | Fighter  |  Monk  |
| Paladin | Ranger | Rouge | Sorcerer | Warlock | Wizard |
+--------------------------------------------------------+)";
	cout << endl;
	cout << "Choose a class: ";
	cin >> characterClass;
	cout << R"(+------------------------| Backgrounds |--------------------------+
| Acolyte | Charlatan |  Criminal | Spy | Entertainer  |  Gladiator  |
| Folk Hero | Guild Artisan | Guild Merchant | Hermit | Noble | Knight |
| Outlander | Sage | Sailor | Pirate | Soldier | Urchin |
+-------------------------------------------------------------------+)";
	cout << endl;
	cout << "Choose a background: ";
	cin.ignore();
	getline(cin, background);
	cout << R"(+----------------------| Alignments |----------------------+
|  Lawful Good  | Neutral Good  |  Chaotic Good  |
| Lawful Neutral | True Neutral | Chaotic Neutral |
|  Lawful Evil  | Neutral Evil  |  Chaotic Evil  |
+----------------------------------------------------+)";
	cout << endl;
	cout << "Choose a background: ";
	getline(cin, alignment);

	Character newCharacter(playerName, characterName, race, characterClass, background, alignment);
	random_device rd;
	mt19937_64 rng(rd());
	vector<int> scores(6);
	char accept = 'n';
	do {
		cout << "\nRolling ability scores (4d6, drop lowest):" << endl;
		for (int i = 0; i < 6; ++i) {
			scores[i] = rollAbilityScore(rng);
		}
		cout << "Your rolled scores: ";
		for (int s : scores) cout << s << " ";
		cout << endl;
		cout << "Accept these scores? (y/n): ";
		cin >> accept;
	} while (accept != 'y' && accept != 'Y');

	newCharacter.setStr(scores[0]);
	newCharacter.setDex(scores[1]);
	newCharacter.setCon(scores[2]);
	newCharacter.setIntel(scores[3]);
	newCharacter.setWis(scores[4]);
	newCharacter.setCha(scores[5]);

	newCharacter.applyRaceAttributes();
	newCharacter.applyClassAttributes();
	newCharacter.applyBackgroundAttributes();
	newCharacter.applyLevelAttributes();
	newCharacter.addItem(Item("Longsword", "Weapon", 15, 5, 8, 3, 1));
	characters.push_back(newCharacter);
	return newCharacter;
}

static void menu() {
	clear();
	cout << "1. Create New Character" << endl;
	cout << "2. View Character Sheet" << endl;
	cout << "3. Combat Simulation (Not Implemented)" << endl;
	cout << "0. Exit" << endl;
	cout << "Choose an option: ";
	int choice;
	cin >> choice;
	switch (choice) {
	case 1:
		newCharacter();
		menu();
		break;
	case 2:
		viewCharacter();
		menu();
		break;
	case 3:
		cout << "Combat simulation is not implemented yet." << endl;
		menu();
		break;
	case 0:
		exit(0);
		break;
	default:
		cout << "Invalid choice." << endl;
		menu();
		break;
	}
}

static void viewCharacter() {
	clear();
	int index;
	if (characters.size() == 0) {
		cout << "No characters available. Create one first." << endl;
		cout << "Press Enter to return to menu...";
		cin.ignore();
		cin.get();
		menu();
	}
	for (int i = 0; i <= characters.size() - 1; ++i) {
		cout << "Character #" << i << " name: " << characters.at(i).getCharacterName();
	}
	cout << endl << "Enter character index to view (0 to " << characters.size() - 1 << "): ";
	cin >> index;
	clear();
	characters.at(index).display();
	cout << "\nPress Enter to return to menu...";
	cin.ignore();
	cin.get();
}

int main() {
	menu();
	return 0;
};