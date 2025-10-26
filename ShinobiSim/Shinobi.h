#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "Jutsu.h"
#include "Village.h"
#include "Clan.h"
#include "KekkeiGenkai.h"

using namespace std;

enum class Rank {
	Academy,
	Genin,
	Chunin,
	Jonin,
	Anbu,
	Kage,
	Missing
};

struct Stats {
	int ninjutsu = 10;
	int taijutsu = 10;
	int genjutsu = 10;
	int defense = 10;
	int speed = 10;
	int chakraControl = 10;
};

class Shinobi {
private:
	string name = "unknown";
	int level = 1;
	int maxChakra = 100;
	int currentChakra = 100;
	float chakraEfficiency = 0.1f; // fraction of max chakra recovered per turn, extra chakra used in jutsus
	Rank rank = Rank::Academy; // Refer to Rank enum
	Village village;
	vector<Jutsu> knownJutsus; // Jutsus known by the Shinobi
	Clan clan;

	int maxHealth = 100;
	int currentHealth = 100;
	Stats stats;

public:
	Shinobi() = default;

	Shinobi(const string& inName, int inLevel = 1, int inMaxChakra = 100, 
			float inChakraEfficiency = 0.1f, Rank inRank = Rank::Academy, 
			const Village& inVillage = Village(), const Clan& inClan = Clan())
		: name(inName), level(max(1, inLevel)), maxChakra(max(1, inMaxChakra)), 
		chakraEfficiency(inChakraEfficiency), rank(inRank), village(inVillage), 
		clan(inClan) {
		currentChakra = maxChakra;
		currentHealth = maxHealth;
	};
	
	~Shinobi() = default;

	// Basic getters
	const string& GetName() const { return name; }
	int GetLevel() const { return level; }
	int GetMaxChakra() const { return maxChakra; }
	int GetCurrentChakra() const { return currentChakra; }
	float GetChakraEfficiency() const { return chakraEfficiency; }
	Rank GetRank() const { return rank; }
	const Village& GetVillage() const { return village; }
	const Clan& GetClan() const { return clan; }
	const Stats& GetStats() const { return stats; }
	int GetHealt() const { return currentHealth; }
	int GetMaxHealth() const { return maxHealth; }

	// Basic setters (keep simple validation)
	void SetName(const string& v) { name = v; }
	void SetLevel(int v) { level = max(1, v); }
	void SetMaxChakra(int v) { maxChakra = max(1, v); if (currentChakra > maxChakra) currentChakra = maxChakra; }
	void SetChakraEfficiency(float v) { chakraEfficiency = v; }
	void SetRank(Rank r) { rank = r; }
	void setVillage(const Village& v) { village = v; }
	void SetClan(const Clan& c) { clan = c; }
	void SetStats(const Stats& s) { stats = s; }
	void SetMaxHealth(int h) { maxHealth = max(1, h); if (currentHealth > maxHealth) currentHealth = maxHealth; }

	bool UseChakra(int amount) {
		if (amount <= 0) return true;
		if (currentChakra < amount) return false;
		currentChakra -= amount;
		return true;
	}

	// Recover a fixed amount of chakra
	void RecoverChakra(int amount) {
		if (amount <= 0) return;
		currentChakra = min(maxChakra, currentChakra + amount);
	}

	// Recover via efficiency (e.g., per turn recovery)
	void RecoverChakraByEfficiency() {
		int recover = static_cast<int>(maxChakra * chakraEfficiency);
		if (recover <= 0) recover = 1;
		RecoverChakra(recover);
	}

	// Simple leveling: increase level and scale chakra slightly
	void LevelUp(int inc = 1) {
		if (inc <= 0) return;
		level += inc;
		// scale max chakra modestly per level
		maxChakra += 10 * inc;
		currentChakra = maxChakra;
		stats.ninjutsu += 2 * inc;
		stats.taijutsu += 1 * inc;
		stats.defense += 1 * inc;
		maxHealth += 5 * inc;
		currentHealth = maxHealth;
	}

	void LearnJutsu(const Jutsu& j) {
		auto it = find_if(knownJutsus.begin(), knownJutsus.end(),
			[&](const Jutsu& existing) { return existing.EqualsByName(j.getName()); });
		if (it != knownJutsus.end()) {
			*it = j;
		}
		else {
			knownJutsus.push_back(j);
		}
	}

	const Jutsu* FindJutsu(const string& jutsuName) const {
		auto it = find_if(knownJutsus.begin(), knownJutsus.end(),
			[&](const Jutsu& existing) { return existing.EqualsByName(jutsuName); });
		if (it == knownJutsus.end()) return nullptr;
		return &*it; // black magic
	}

	bool UseJutsu(const string& jutsuName) {
		const Jutsu* j = FindJutsu(jutsuName);
		if (!j) return false;
		if (!UseChakra(j->getChakraCost())) return false;
		// For now, using a jutsu only deducts chakra. Effects / cooldowns go later.
		return true;
	}

	bool UseJutsuOnTarget(Shinobi& target, const string& jutsuName) {
		const Jutsu* j = FindJutsu(jutsuName);
		if (!j) return false;
		// Check chakra first
		if (!UseChakra(j->getChakraCost())) return false;

		// Compute effect
		switch (j->GetEffectType()) {
		case JutsuEffectType::Damage: {
			// Simple damage formula
			double atk = static_cast<double>(stats.ninjutsu);
			double def = static_cast<double>(max(1, target.stats.defense));
			double raw = j->GetBasePower() * (atk / def) * (1.0 + (level - 1) * 0.02);
			int damage = max(1, static_cast<int>(std::round(raw)));
			target.currentHealth = max(0, target.currentHealth - damage);
			return true;
		}
		case JutsuEffectType::Heal: {
			double heal = j->GetBasePower() * (static_cast<double>(stats.chakraControl) / 10.0);
			int amount = max(1, static_cast<int>(std::round(heal)));
			target.currentHealth = min(target.maxHealth, target.currentHealth + amount);
			return true;
		}
		case JutsuEffectType::Buff: {
			// Immediate simple buff: increase a named stat by basePower (rounded)
			const string& stat = j->GetTargetStat();
			int change = max(1, static_cast<int>(std::round(j->GetBasePower())));
			if (stat == "Ninjutsu") target.stats.ninjutsu += change;
			else if (stat == "Taijutsu") target.stats.taijutsu += change;
			else if (stat == "Defense") target.stats.defense += change;
			else if (stat == "Speed") target.stats.speed += change;
			else if (stat == "ChakraControl") target.stats.chakraControl += change;
			return true;
		}
		case JutsuEffectType::Debuff: {
			const string& stat = j->GetTargetStat();
			int change = max(1, static_cast<int>(std::round(j->GetBasePower())));
			if (stat == "Ninjutsu") target.stats.ninjutsu = max(1, target.stats.ninjutsu - change);
			else if (stat == "Taijutsu") target.stats.taijutsu = max(1, target.stats.taijutsu - change);
			else if (stat == "Defense") target.stats.defense = max(1, target.stats.defense - change);
			else if (stat == "Speed") target.stats.speed = max(1, target.stats.speed - change);
			else if (stat == "ChakraControl") target.stats.chakraControl = max(1, target.stats.chakraControl - change);
			return true;
		}
		default:
			return true;
		}
	}

	void PrintKnownJutsus(ostream& os = cout) const {
		if (knownJutsus.empty()) {
			os << "No known jutsu.\n";
			return;
		}
		os << "Known Jutsu:\n";
		for (const auto& j : knownJutsus) j.PrintSummary(os);
	}

	// Print a compact summary
	void PrintSummary(ostream& os = cout) const {
		os << "Name: " << name << "\n";
		os << "Village: " << village.GetName() << "\n";
		if (clan.GetName() != "none") {
			os << "Clan: ";
			clan.PrintSummary(os);
		}
		os << "Rank: ";
		switch (rank) {
		case Rank::Academy: os << "Academy"; break;
		case Rank::Genin: os << "Genin"; break;
		case Rank::Chunin: os << "Chunin"; break;
		case Rank::Jonin: os << "Jonin"; break;
		case Rank::Anbu: os << "Anbu"; break;
		case Rank::Kage: os << "Kage"; break;
		case Rank::Missing: os << "Missing"; break;
		}
		os << "  Level: " << level << "\n";
		os << "Health: " << currentHealth << " / " << maxHealth << "\n";
		os << "Chakra: " << currentChakra << " / " << maxChakra << "  (Efficiency: " << chakraEfficiency << ")\n";
		os << "Stats: Ninjutsu=" << stats.ninjutsu << " Taijutsu=" << stats.taijutsu << " Defense=" << stats.defense << " Speed=" << stats.speed << " ChakraControl=" << stats.chakraControl << "\n";
		PrintKnownJutsus(os);
	}
};
