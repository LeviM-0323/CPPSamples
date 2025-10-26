#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum class JutsuGrade { // Rank of a Jutsu
	E,
	D,
	C,
	B,
	A,
	S
};

enum class JutsuType {
	Ninjutsu,
	Genjutsu,
	Taijutsu
};

enum class JutsuEffectType {
	Damage,
	Heal,
	Buff,
	Debuff,
	Utility
};

inline const char* JutsuGradeToString(JutsuGrade g) {
	switch (g) {
	case JutsuGrade::E: return "E";
	case JutsuGrade::D: return "D";
	case JutsuGrade::C: return "C";
	case JutsuGrade::B: return "B";
	case JutsuGrade::A: return "A";
	case JutsuGrade::S: return "S";
	default: return "?";
	}
}

inline const char* JutsuEffectTypeToString(JutsuEffectType t) {
	switch (t) {
	case JutsuEffectType::Damage: return "Damage";
	case JutsuEffectType::Heal: return "Heal";
	case JutsuEffectType::Buff: return "Buff";
	case JutsuEffectType::Debuff: return "Debuff";
	case JutsuEffectType::Utility: return "Utility";
	default: return "?";
	}
}

inline const char* JutsuTypeToString(JutsuType t) {
	switch (t) {
	case JutsuType::Ninjutsu: return "Ninjutsu";
	case JutsuType::Genjutsu: return "Genjutsu";
	case JutsuType::Taijutsu: return "Taijutsu";
	default: return "?";
	}
}

class Jutsu {
private:
	string name = "unknown";
	int chakraCost = 0;
	JutsuGrade grade = JutsuGrade::E; // Refer to Rank enum
	JutsuType type = JutsuType::Ninjutsu;
	JutsuEffectType effectType = JutsuEffectType::Damage;

	double basePower = 0.0;
	string element = "";
	string targetStat = "";
	int effectDuration = 0;
	int cooldown = 0;

public:
	Jutsu() = default;

	Jutsu(const string& inName, int inChakraCost, JutsuGrade inGrade, JutsuType inType, JutsuEffectType inEffect, double inBasePower = 10.0, const string& inTargetStat = "", int inDuration = 0)
		: name(inName), chakraCost(inChakraCost), grade(inGrade), type(inType), effectType(inEffect), basePower(inBasePower), targetStat(inTargetStat), effectDuration(inDuration) {
	};

	~Jutsu() = default;

	// Basic getters
	const string& getName() const { return name; }
	int getChakraCost() const { return chakraCost; }
	JutsuGrade getGrade() const { return grade; }
	JutsuType getType() const { return type; }
	JutsuEffectType GetEffectType() const { return effectType; }
	double GetBasePower() const { return basePower; }
	const string& GetElement() const { return element; }
	const string& GetTargetStat() const { return targetStat; }
	int GetEffectDuration() const { return effectDuration; }
	int GetCooldown() const { return cooldown; }

	// Basic setters
	void setName(const string& v) { name = v; }
	void setChakraCost(int v) { chakraCost = v; }
	void setGrade(JutsuGrade g) { grade = g; }
	void setType(JutsuType t) { type = t; }
	void SetEffectType(JutsuEffectType t) { effectType = t; }
	void SetBasePower(double p) { basePower = p; }
	void SetElement(const string& e) { element = e; }
	void SetTargetStat(const string& s) { targetStat = s; }
	void SetEffectDuration(int d) { effectDuration = d; }
	void SetCooldown(int c) { cooldown = c; }

	void PrintSummary(ostream& os = cout) const {
		os << "Jutsu: " << name << ", Chakra Cost: " << chakraCost
			<< ", Grade: " << JutsuGradeToString(grade)
			<< ", Effect: " << JutsuEffectTypeToString(effectType)
			<< ", Power: " << basePower;
		if (!targetStat.empty()) os << ", TargetStat: " << targetStat;
		os << "\n";
	}

	bool EqualsByName(const string& otherName) const {
		return name == otherName;
	}
};