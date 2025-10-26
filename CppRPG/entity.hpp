#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Entity {
private:
	int level = 1;
	string type = "unknown";
	string name = "unknown";
	double maxHealth = 100;
	double currentHealth = maxHealth;
	double damage = 10;
	double xp = 0;
	double posX = 150;
	double posY = 150;
public:

	//default constructor
	Entity() = default;

	//"quick create" constructor
	Entity(string name, string type) 
		: name(name), type(type)
	{
	}

	//all fields constructor
	Entity(int level, double health, double damage, double xp, double posX, double posY, string type, string name)
		: level(level), maxHealth(health), damage(damage), xp(xp), posX(posX), posY(posY), type(type), name(name)
	{
	}

	//getters
	int getLevel() {
		return level;
	}

	double getMaxHealth() {
		return maxHealth;
	}

	double getCurrentHealth() {
		return currentHealth;
	}

	double getDamage() {
		return damage;
	}

	double getXP() {
		return xp;
	}

	double getPosX() {
		return posX;
	}

	double getPosY() {
		return posY;
	}

	void getType() {
		cout << type;
	}

	void getName() {
		cout << name;
	}
	
	//setters
	void setLevel(int l) {
		level = l;
	}

	void setMaxHealth(double h) {
		maxHealth = h;
	}

	void setCurrentHealt(double c) {
		currentHealth = c;
	}

	void setDamage(double d) {
		damage = d;
	}

	void setXP(double x) {
		xp = x;
	}

	void setPosX(double x) {
		posX = x;
	}

	void setPosY(double y) {
		posY = y;
	}

	void setType(string t) {
		type = t;
	}

	void setName(string n) {
		name = n;
	}

	//operators
	bool operator==(const Entity& other) const
	{
		return level == other.level || maxHealth == other.maxHealth || damage == other.damage || xp == other.xp || posX == other.posX || posY == other.posY;
	}

	//helper methods
	void printStats() {
		cout << "Entity name: " << name << endl;
		cout << "Entity type: " << type << endl;
		cout << "Level: " << level << endl;
		cout << "Health: " << currentHealth << "/" << maxHealth << endl;
		cout << "Damage: " << damage << endl;
		cout << "Xp: " << xp << endl;
		cout << "Position: " << posX << "," << posY << endl << endl;
	}

	void attack(Entity& other) {
		other.currentHealth -= damage;
	}
};