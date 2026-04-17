#include <iostream>
#include <iomanip>
#include <string>
#include "item.hpp"

using namespace std;

class Character {
private:
	string characterName, playerName, race, characterClass, background, alignment;
	int str, dex, intel, wis, cha, con, mhp /*max hp*/, chp /*current hp*/, thp /*temp hp*/, ac, initiative, speed, xp, profbonus, inspiration, age, size, weight, level;
public:
	vector<Item> itemList;

	Character() : characterName(""), playerName(""), race(""), characterClass(""), background(""), alignment(""),
		str(0), dex(0), intel(0), wis(0), cha(0), con(0), mhp(0), chp(0), thp(0), ac(0), initiative(0), speed(0), xp(0), profbonus(0), inspiration(0), age(0), size(0), weight(0), level(1) {}

	Character(string characterName, string playerName, string race, string characterClass, string background, string alignment) : characterName(characterName), playerName(playerName), 
		race(race), characterClass(characterClass), background(background), alignment(alignment), str(0), dex(0), intel(0), wis(0), cha(0), con(0), mhp(0), chp(0), thp(0), ac(0), 
		initiative(0), speed(0), xp(0), profbonus(0), inspiration(0), age(0), size(0), weight(0), level(1) {}

	virtual ~Character() {}

	virtual void applyRaceAttributes() {
		std::random_device rd;
		std::mt19937 gen(rd());

		int minWeight = 0, maxWeight = 0;

		if (race == "Dwarf" || race == "Hill Dwarf" || race == "Mountain Dwarf") {
			con += 2;
			speed = 25;
			size = std::uniform_int_distribution<>(54, 64)(gen); // 4'6" to 5'4"
			age = std::uniform_int_distribution<>(50, 350)(gen);
			minWeight = 130; maxWeight = 170;
			if (race == "Hill Dwarf") wis += 1;
			if (race == "Mountain Dwarf") str += 2;
		}
		else if (race == "Elf" || race == "High Elf" || race == "Wood Elf" || race == "Dark Elf" || race == "Drow") {
			dex += 2;
			speed = (race == "Wood Elf") ? 35 : 30;
			size = std::uniform_int_distribution<>(54, 74)(gen); // 4'6" to 6'2"
			age = std::uniform_int_distribution<>(100, 750)(gen);
			minWeight = 90; maxWeight = 150;
			if (race == "High Elf") intel += 1;
			if (race == "Wood Elf") wis += 1;
			if (race == "Dark Elf" || race == "Drow") cha += 1;
		}
		else if (race == "Halfling" || race == "Lightfoot Halfling" || race == "Stout Halfling") {
			dex += 2;
			speed = 25;
			size = std::uniform_int_distribution<>(31, 37)(gen); // 2'7" to 3'1"
			age = std::uniform_int_distribution<>(20, 250)(gen);
			minWeight = 35; maxWeight = 45;
			if (race == "Lightfoot Halfling") cha += 1;
			if (race == "Stout Halfling") con += 1;
		}
		else if (race == "Human") {
			str += 1; dex += 1; con += 1; intel += 1; wis += 1; cha += 1;
			speed = 30;
			size = std::uniform_int_distribution<>(58, 78)(gen); // 4'10" to 6'6"
			age = std::uniform_int_distribution<>(18, 80)(gen);
			minWeight = 110; maxWeight = 250;
		}
		else if (race == "Dragonborn") {
			str += 2; cha += 1;
			speed = 30;
			size = std::uniform_int_distribution<>(72, 96)(gen); // 6'0" to 8'0"
			age = std::uniform_int_distribution<>(15, 80)(gen);
			minWeight = 220; maxWeight = 320;
		}
		else if (race == "Gnome" || race == "Forest Gnome" || race == "Rock Gnome") {
			intel += 2;
			speed = 25;
			size = std::uniform_int_distribution<>(35, 43)(gen); // 2'11" to 3'7"
			age = std::uniform_int_distribution<>(40, 500)(gen);
			minWeight = 40; maxWeight = 45;
			if (race == "Forest Gnome") dex += 1;
			if (race == "Rock Gnome") con += 1;
		}
		else if (race == "Half-Elf") {
			cha += 2;
			speed = 30;
			size = std::uniform_int_distribution<>(57, 74)(gen); // 4'9" to 6'2"
			age = std::uniform_int_distribution<>(20, 180)(gen);
			minWeight = 100; maxWeight = 180;
		}
		else if (race == "Half-Orc") {
			str += 2; con += 1;
			speed = 30;
			size = std::uniform_int_distribution<>(60, 84)(gen); // 5'0" to 7'0"
			age = std::uniform_int_distribution<>(14, 75)(gen);
			minWeight = 180; maxWeight = 250;
		}
		else if (race == "Tiefling") {
			cha += 2; intel += 1;
			speed = 30;
			size = std::uniform_int_distribution<>(57, 72)(gen); // 4'9" to 6'0"
			age = std::uniform_int_distribution<>(18, 100)(gen);
			minWeight = 110; maxWeight = 180;
		}

		// Class-based weight adjustment (martial classes heavier, arcane lighter)
		int classBonus = 0;
		if (characterClass == "Barbarian" || characterClass == "Fighter" || characterClass == "Paladin") {
			classBonus = 20;
		}
		else if (characterClass == "Monk" || characterClass == "Rogue" || characterClass == "Ranger") {
			classBonus = -10;
		}
		else if (characterClass == "Wizard" || characterClass == "Sorcerer") {
			classBonus = -20;
		}

		if (minWeight > 0 && maxWeight > 0) {
			weight = std::uniform_int_distribution<>(minWeight, maxWeight)(gen) + classBonus;
			// Clamp to min/max
			if (weight < minWeight) weight = minWeight;
			if (weight > maxWeight) weight = maxWeight;
		}
		else {
			weight = 0;
		}
	}

	virtual void applyClassAttributes() {
		if (characterClass == "Barbarian") {
			mhp = 12 + con; // d12 hit die
			chp = mhp;
			ac = 10 + dex + con; // Unarmored Defense
			speed = 40;
		}
		else if (characterClass == "Bard") {
			mhp = 8 + con; // d8 hit die
			chp = mhp;
			ac = 10 + dex;
			speed = 30;
		}
		else if (characterClass == "Cleric") {
			mhp = 8 + con; // d8 hit die
			chp = mhp;
			ac = 10 + dex;
			speed = 30;
		}
		else if (characterClass == "Druid") {
			mhp = 8 + con; // d8 hit die
			chp = mhp;
			ac = 10 + dex;
			speed = 30;
		}
		else if (characterClass == "Fighter") {
			mhp = 10 + con; // d10 hit die
			chp = mhp;
			ac = 10 + dex;
			speed = 30;
		}
		else if (characterClass == "Monk") {
			mhp = 8 + con; // d8 hit die
			chp = mhp;
			ac = 10 + dex + wis; // Unarmored Defense
			speed = 40;
		}
		else if (characterClass == "Paladin") {
			mhp = 10 + con; // d10 hit die
			chp = mhp;
			ac = 10 + dex;
			speed = 30;
		}
		else if (characterClass == "Ranger") {
			mhp = 10 + con; // d10 hit die
			chp = mhp;
			ac = 10 + dex;
			speed = 30;
		}
		else if (characterClass == "Rogue") {
			mhp = 8 + con; // d8 hit die
			chp = mhp;
			ac = 10 + dex;
			speed = 30;
		}
		else if (characterClass == "Sorcerer") {
			mhp = 6 + con; // d6 hit die
			chp = mhp;
			ac = 10 + dex;
			speed = 30;
		}
		else if (characterClass == "Warlock") {
			mhp = 8 + con; // d8 hit die
			chp = mhp;
			ac = 10 + dex;
			speed = 30;
		}
		else if (characterClass == "Wizard") {
			mhp = 6 + con; // d6 hit die
			chp = mhp;
			ac = 10 + dex;
			speed = 30;
		}
	}

	virtual void applyBackgroundAttributes() {
		if (background == "Acolyte") {
			wis += 1;
		}
		else if (background == "Charlatan") {
			cha += 1;
		}
		else if (background == "Criminal" || background == "Spy") {
			dex += 1;
		}
		else if (background == "Entertainer" || background == "Gladiator") {
			cha += 1;
		}
		else if (background == "Folk Hero") {
			con += 1;
		}
		else if (background == "Guild Artisan" || background == "Guild Merchant") {
			intel += 1;
		}
		else if (background == "Hermit") {
			wis += 1;
		}
		else if (background == "Noble" || background == "Knight") {
			cha += 1;
		}
		else if (background == "Outlander") {
			str += 1;
		}
		else if (background == "Sage") {
			intel += 1;
		}
		else if (background == "Sailor" || background == "Pirate") {
			dex += 1;
		}
		else if (background == "Soldier") {
			str += 1;
		}
		else if (background == "Urchin") {
			dex += 1;
		}
	}

	virtual void applyLevelAttributes() {
		initiative = (dex - 10) / 2;
		if (level >= 1 && level <= 4) {
			profbonus = 2;
		}
		else if (level >= 5 && level <= 8) {
			profbonus = 3;
		}
		else if (level >= 9 && level <= 12) {
			profbonus = 4;
		}
		else if (level >= 13 && level <= 16) {
			profbonus = 5;
		}
		else if (level >= 17 && level <= 20) {
			profbonus = 6;
		}
		else {
			profbonus = 2; // Default for out-of-range
		}
	}

	virtual void display() const {
		cout << "\n+------------------ Character Sheet ------------------+\n";
		cout << left << setw(15) << "Player:" << playerName << endl;
		cout << left << setw(15) << "Character:" << characterName << endl;
		cout << left << setw(15) << "Race:" << race << endl;
		cout << left << setw(15) << "Class:" << characterClass << endl;
		cout << left << setw(15) << "Background:" << background << endl;
		cout << left << setw(15) << "Alignment:" << alignment << endl;
		cout << left << setw(15) << "Age:" << age << endl;
		cout << left << setw(15) << "Size:" << size << endl;
		cout << left << setw(15) << "Weight:" << weight << endl;
		cout << "\n+------------------ Ability Scores -------------------+\n";
		cout << left << setw(8) << "STR" << setw(8) << "DEX" << setw(8) << "CON"
			<< setw(8) << "INT" << setw(8) << "WIS" << setw(8) << "CHA" << endl;
		cout << left << setw(8) << str << setw(8) << dex << setw(8) << con
			<< setw(8) << intel << setw(8) << wis << setw(8) << cha << endl;
		cout << "\n+------------------- Combat Info ---------------------+\n";
		cout << left << setw(15) << "Max HP:" << mhp << endl;
		cout << left << setw(15) << "Current HP:" << chp << endl;
		cout << left << setw(15) << "Temp HP:" << thp << endl;
		cout << left << setw(15) << "AC:" << ac << endl;
		cout << left << setw(15) << "Initiative:" << initiative << endl;
		cout << left << setw(15) << "Speed:" << speed << "ft" << endl;
		cout << "\n+------------------- Progression ---------------------+\n";
		cout << left << setw(15) << "XP:" << xp << endl;
		cout << left << setw(15) << "Prof. Bonus:" << "+" << profbonus << endl;
		cout << left << setw(15) << "Inspiration:" << inspiration << endl;
		cout << "\n+------------------- Inventory -----------------------+\n";
		for (size_t i = 0; i < itemList.size() - 1; ++i) {
			cout << left << setw(15) << itemList.at(i).getName() << ", +" << 
				itemList.at(i).getPlusHit() << " " << itemList.at(i).getDamage() << " " <<
				itemList.at(i).getWeight() << " " << itemList.at(i).getValue() << " " <<
				itemList.at(i).getQuantity();
		}
	}

	// Getters
	string getCharacterName() const { return characterName; }
	string getPlayerName() const { return playerName; }
	string getRace() const { return race; }
	string getCharacterClass() const { return characterClass; }
	string getBackground() const { return background; }
	string getAlignment() const { return alignment; }

	int getStr() const { return str; }
	int getWeight() const { return weight; }
	int getDex() const { return dex; }
	int getIntel() const { return intel; }
	int getWis() const { return wis; }
	int getCha() const { return cha; }
	int getCon() const { return con; }
	int getMhp() const { return mhp; }
	int getChp() const { return chp; }
	int getThp() const { return thp; }
	int getAc() const { return ac; }
	int getInitiative() const { return initiative; }
	int getSpeed() const { return speed; }
	int getXp() const { return xp; }
	int getProfbonus() const { return profbonus; }
	int getInspiration() const { return inspiration; }
	int getAge() const { return age; }
	int getSize() const { return size; }

	// Setters
	void setCharacterName(const string& value) { characterName = value; }
	void setPlayerName(const string& value) { playerName = value; }
	void setRace(const string& value) { race = value; }
	void setCharacterClass(const string& value) { characterClass = value; }
	void setBackground(const string& value) { background = value; }
	void setAlignment(const string& value) { alignment = value; }

	void setStr(int value) { str = value; }
	void setDex(int value) { dex = value; }
	void setIntel(int value) { intel = value; }
	void setWis(int value) { wis = value; }
	void setCha(int value) { cha = value; }
	void setCon(int value) { con = value; }
	void setMhp(int value) { mhp = value; }
	void setChp(int value) { chp = value; }
	void setThp(int value) { thp = value; }
	void setAc(int value) { ac = value; }
	void setInitiative(int value) { initiative = value; }
	void setSpeed(int value) { speed = value; }
	void setXp(int value) { xp = value; }
	void setProfbonus(int value) { profbonus = value; }
	void setInspiration(int value) { inspiration = value; }
	void setAge(int value) { age = value; }
	void setSize(int value) { size = value; }
	void setWeight(int value) { weight = value; }

	void addItem(const Item& item) { itemList.push_back(item); }
	void removeLastItem() { if (!itemList.empty()) itemList.pop_back(); }
	const vector<Item>& getItems() const { return itemList; }
};