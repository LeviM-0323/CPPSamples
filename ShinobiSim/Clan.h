#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "KekkeiGenkai.h"

using namespace std;

class Clan {
private:
	string name = "none";
	vector<KekkeiGenkai> kekkeiGenkai;
	vector<string> notableMembers;

public:
	Clan() = default;
	
	Clan(const string& inName, const vector<KekkeiGenkai>& kekList = {}, const vector<string>& notabMems = {})
		: name(inName), kekkeiGenkai(kekList), notableMembers(notabMems) {}
	
	Clan(const string& inName,
		initializer_list<KekkeiGenkai> kekList,
		initializer_list<string> notabMems = {})
		: name(inName), kekkeiGenkai(kekList), notableMembers(notabMems) {
	}

	// Basic getters
	const string& GetName() const { return name; }
	const vector<KekkeiGenkai>& GetKekkeiGenkai() const { return kekkeiGenkai; }
	const vector<string>& GetNotableMembers() const { return notableMembers; }

	// Basic setters
	void SetName(const string& v) { name = v; }

	void AddKekkeiGenkai(const KekkeiGenkai& kg) {
		auto it = find_if(kekkeiGenkai.begin(), kekkeiGenkai.end(),
			[&](const KekkeiGenkai& e) { return e.EqualsByName(kg.GetName()); });
		if (it == kekkeiGenkai.end()) kekkeiGenkai.push_back(kg);
		else *it = kg; // replace with updated metadata
	}

	bool RemoveKekkeiGenkaiByName(const string& kgName) {
		auto it = remove_if(kekkeiGenkai.begin(), kekkeiGenkai.end(),
			[&](const KekkeiGenkai& e) { return e.EqualsByName(kgName); });
		if (it == kekkeiGenkai.end()) return false;
		kekkeiGenkai.erase(it, kekkeiGenkai.end());
		return true;
	}

	void AddNotableMember(const string& m) {
		if (find(notableMembers.begin(), notableMembers.end(), m) == notableMembers.end())
			notableMembers.push_back(m);
	}
	bool RemoveNotableMember(const string& m) {
		auto it = remove(notableMembers.begin(), notableMembers.end(), m);
		if (it == notableMembers.end()) return false;
		notableMembers.erase(it, notableMembers.end());
		return true;
	}

	// Small helper for debug/printing
	void PrintSummary(ostream& os = cout) const {
		os << "Clan: " << name << "\n";
		if (!kekkeiGenkai.empty()) {
			os << "  Kekkei Genkai: ";
			for (size_t i = 0; i < kekkeiGenkai.size(); ++i) {
				if (i) os << ", ";
				os << kekkeiGenkai[i].GetName();
			}
			os << "\n";
		}
		if (!notableMembers.empty()) {
			os << "  Notable Members: ";
			for (size_t i = 0; i < notableMembers.size(); ++i) {
				if (i) os << ", ";
				os << notableMembers[i];
			}
			os << "\n";
		}
	}
};