#include <iostream>
#include "Shinobi.h"

using namespace std;

int main() {
	Clan uchiha(
		"Uchiha Clan",
		{ KekkeiGenkai("Sharingan", "An eye-based Kekkei Genkai that grants various abilities."),
		  KekkeiGenkai("Mangekyou Sharingan", "Advanced Sharingan form") },
		{ "Sasuke Uchiha", "Itachi Uchiha" }
	);

	cout << "Creating Shinobi Naruto Uzumaki...\n";
	Shinobi naruto("Naruto Uzumaki", 10, 200, 0.2f, Rank::Genin, Village("Hidden Leaf Village", "Fire Country", "Neutral", "Lady Tsunade", 12751));
	naruto.LearnJutsu(Jutsu("Shadow Clone Jutsu", 20, JutsuGrade::B, JutsuType::Ninjutsu, JutsuEffectType::Utility, 0));
	naruto.LearnJutsu(Jutsu("Rasengan", 25, JutsuGrade::A, JutsuType::Ninjutsu, JutsuEffectType::Damage, 30.0));
	naruto.PrintSummary();
	cout << endl;

	cout << "Creating Shinobi Sasuke Uchiha...\n";
	Shinobi sasuke("Sasuke Uchiha", 12, 180, 0.15f, Rank::Genin, Village("Hidden Leaf Village", "Fire Country", "Neutral", "Lady Tsunade", 12751), uchiha);
	sasuke.LearnJutsu(Jutsu("Chidori", 30, JutsuGrade::A, JutsuType::Ninjutsu, JutsuEffectType::Damage, 35.0));
	sasuke.LearnJutsu(Jutsu("Fireball Jutsu", 15, JutsuGrade::B, JutsuType::Ninjutsu, JutsuEffectType::Damage, 12.0));
	sasuke.PrintSummary();
	cout << endl;

	cout << "Naruto uses Rasengan on Sasuke...\n";
	if (naruto.UseJutsuOnTarget(sasuke, "Rasengan")) {
		cout << "Rasengan used successfully!\n";
	}
	else {
		cout << "Failed to use Rasengan.\n";
	}
	cout << "Sasuke after attack:\n";
	sasuke.PrintSummary();
	cout << endl;

	cout << "Sasuke retaliates with Chidori...\n";
	if (sasuke.UseJutsuOnTarget(naruto, "Chidori")) cout << "Chidori applied.\n";
	else cout << "Failed to use Chidori.\n";
	cout << "Naruto after attack:\n";
	naruto.PrintSummary();
	cout << endl;

	return 0;
}