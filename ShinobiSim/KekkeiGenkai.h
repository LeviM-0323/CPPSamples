#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class KekkeiGenkai {
private:
	string name = "unknown";
	string description = "No description.";

public:
	KekkeiGenkai() = default;
	KekkeiGenkai(const string& inName, const string& inDescription = "")
		: name(inName), description(inDescription) {
	};

	// Getters
	const string& GetName() const { return name; }
	const string& GetDescription() const { return description; }

	// Setters
	void SetName(const string& v) { name = v; }
	void SetDescription(const string& v) { description = v; }

	// Convenience
	bool EqualsByName(const string& other) const { return name == other; }

	void PrintSummary(ostream& os = cout) const {
		os << "Kekkei Genkai: " << name;
		if (!description.empty()) os << " - " << description;
		os << "\n";
	}
};