#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Item {
private:
	string name, type;
	int value, plusHit, damage, weight, quantity;
public:

	Item() = default;

	Item(const string& name, const string& type, int value, int plusHit, int damage, 
		int weight, int quantity)
		: name(name), type(type), value(value), plusHit(plusHit), damage(damage), 
		weight(weight), quantity(quantity)
	{}

	~Item() = default;

	// Getters
	string getName() const { return name; }
	string getType() const { return type; }

	int getValue() const { return value; }
	int getPlusHit() const { return plusHit; }
	int getDamage() const { return damage; }
	int getWeight() const { return weight; }
	int getQuantity() const { return quantity; }

	//Setters
	void setName(const string& value) { name = value; }
	void setType(const string& value) { type = value; }
	void setValue(int value) { this->value = value; }
	void setPlusHit(int value) { plusHit = value; }
	void setDamage(int value) { damage = value; }
	void setWeight(int value) { weight = value; }
	void setQuantity(int value) { quantity = value; }

};