#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Village {
private:
	string name = "unknown";
	string country = "unknown";
	string leader = "unknown";
	string alignment = "neutral";
	int population = 0;
public:

	Village() = default;

	Village(const string& inName, const string& inCountry, const string& inAlignment, string inLeader, int inPopulation)
		: name(inName), country(inCountry), alignment(inAlignment), leader(inLeader), population(max(0, inPopulation)) {
	};

	~Village() = default;

	// Basic getters
	const string& GetName() const { return name; }
	const string& GetCountry() const { return country; }
	const string& GetLeader() const { return leader; }
	const string& GetAlignment() const { return alignment; }
	int GetPopulation() const { return population; }

	// Basic setters
	void SetName(const string& v) { name = v; }
	void SetCountry(const string& v) { country = v; }
	void SetLeader(const string& v) { leader = v; }
	void SetAlignment(const string& v) { alignment = v; }
	void SetPopulation(int v) { population = max(0, v); }

	// Tools
	bool EqualsByName(const string& other) const { return name == other; }

	void PrintSummary(ostream& os = cout) const {
		os << "Village: " << name << "\n";
		os << "  Country: " << country << "\n";
		os << "  Leader: " << leader << "\n";
		os << "  Alignment: " << alignment << "\n";
		os << "  Population: " << population << "\n";
	}
};