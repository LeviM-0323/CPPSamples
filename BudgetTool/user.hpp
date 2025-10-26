#include <iostream>  
#include <string>  
#include <iomanip>  
#include <chrono>
#include <fstream>

using namespace std;  

class User {  
private:  
	string name;  
	chrono::time_point<chrono::system_clock> lastLogin;
public:
	User() : name(""), lastLogin(chrono::system_clock::now()) {}
	User(string n) : name(n) {
		lastLogin = chrono::system_clock::now();
	}

	string getName() const { return name; }
	chrono::time_point<chrono::system_clock> getLastLogin() const { return lastLogin; }

	void updateLastLogin() { lastLogin = chrono::system_clock::now(); }

    void saveToFile(const string& filename) const {
        ofstream out(filename);
        out << name << endl;
        out << chrono::system_clock::to_time_t(lastLogin) << endl;
    }

    bool loadFromFile(const string& filename) {
        ifstream in(filename);
        if (!in) return false;
        getline(in, name);
        time_t t;
        in >> t;
        lastLogin = chrono::system_clock::from_time_t(t);
        return true;
    }
};