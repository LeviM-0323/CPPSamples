#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;
int main() {
	// Simple stuff
	string food = "Pizza";
	string* foodPtr = &food;
	string& foodRef = food;
	cout << setw(25) << "What's Coded | Result" << endl;
	cout << setw(19) << "string food; | " << food << endl;
	cout << setw(19) << "&food; | " << &food << endl; // same as foodPtr
	cout << setw(19) << "string* foodPtr; | " << foodPtr << endl; // same as &food
	cout << setw(19) << "string& foodRef; | " << foodRef << endl;
	
	// Dangling pointer example
	int* arrayTest = new int[100];
	cout << "Array allocated at: " << &arrayTest << endl;
	delete[] arrayTest;
	cout << "Array deallocated: " << &arrayTest << endl; // Still in memory, but not used or accessed. VERY tiny dangling pointer
	cout << "Size of pointer in bytes: " << sizeof(arrayTest) << endl; // Size of pointer, not the array
	arrayTest = nullptr; // Fix memory leak
	cout << "Pointer set to nullptr: " << &arrayTest << endl;
	return 0;
}