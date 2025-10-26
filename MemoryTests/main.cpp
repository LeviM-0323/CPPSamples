#include <iostream>
#include <vector>
#include <memory> // For smart pointers

using namespace std;

void check(int a[]) {
	cout << "In func sizeof(a): " << sizeof(a) << '\n';
}

// Demonstrate a memory leak (intentional)
void leakMemory() {
	int* leaked = new int[10]; // Not deleted
	cout << "Leaked array address: " << static_cast<void*>(leaked) << "\n";
	// No delete[] leaked; // Memory leak
}

int main() {
	vector<int> v(50);
	int x = 42;
	int stackVar = 5;
	int* heapVar = new int(6);
	int a[3] = { 1, 2, 3 };
	int* q = a;
	int* p = &x;
	int* y = new int(10);
	delete y; // make dangling pointer
	y = nullptr; // Best practice: avoid dangling pointer
	int* dyn = new int[100];
	void* z = &x;
	cout << "Address (as void*): " << static_cast<void*>(z) << '\n';
	cout << "Address (as int*): " << p << '\n';
	cout << "Value via pointer: " << *p << '\n';
	
	int arr[100];
	cout << "In main() sizeof(arr): " << sizeof(arr) << '\n';
	check(arr);
	cout << "Elements: " << (sizeof(arr) / sizeof(arr[0])) << '\n';
	cout << "sizeof(dyn) (pointer): " << sizeof(dyn) << '\n';
	cout << "bytes we allocated manually: " << 100 * sizeof(int) << '\n';
	delete[] dyn;

	uintptr_t p0 = reinterpret_cast<uintptr_t>(q);
	uintptr_t p1 = reinterpret_cast<uintptr_t>(q + 1);
	cout << "p0: " << p0 << '\n';
	cout << "p1: " << p1 << '\n';
	cout << "p1 - p0: " << (p1 - p0) << " bytes (should also be sizeof(int))" << '\n';

	cout << "Stack addr: " << static_cast<void*>(&stackVar) << '\n';
	cout << "Heap addr: " << static_cast<void*>(heapVar) << '\n';
	delete heapVar;

	cout << "Vector bytes allocated: " << v.capacity() * sizeof(int) << '\n';

	// Advanced: Smart pointers
	{
		unique_ptr<int> smartInt(new int(77));
		cout << "unique_ptr<int> address: " << smartInt.get() << ", value: " << *smartInt << '\n';
		// No need to delete, automatic cleanup
	}
	{
		shared_ptr<int> sharedA = make_shared<int>(88);
		shared_ptr<int> sharedB = sharedA;
		cout << "shared_ptr<int> address: " << sharedA.get() << ", value: " << *sharedA << ", use_count: " << sharedA.use_count() << '\n';
		cout << "shared_ptr<int> (copy) address: " << sharedB.get() << ", use_count: " << sharedB.use_count() << '\n';
	}

	// Intentional memory leak demo
	leakMemory();
	cout << "(Intentional) Memory leak function called. Use tools to detect leaks.\n";

	// Dangling pointer demo
	int* dangling = new int(123);
	delete dangling;
	cout << "Dangling pointer address: " << dangling << " (value is undefined!)\n";
	dangling = nullptr; // Best practice
}