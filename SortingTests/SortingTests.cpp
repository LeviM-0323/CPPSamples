/*
Author: Levi McLean (LeviM_0323)
File: SortingTests.cpp
Created: April 8th, 2025
Purpose: This project will test the speeds of different sorting algorithms on a Vector in C++. The sorting algoritms that 
		 will be tested are: the c++ std::sort() function, Bubble sort, Insertion sort, Merge sort and Quick sort
*/

/*
Master TODO list:
	[] Finalize formatting
	[] Store history of past tests (items sorted, total duration, items per microseconds)
	[] Github publication
*/

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <chrono>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

using namespace std;

static long long stdSort(vector<int>& vec) {
	auto start = chrono::high_resolution_clock::now();
	sort(vec.begin(), vec.end());
	auto end = chrono::high_resolution_clock::now();
	for (const auto& i : vec) {
		cout << i << " ";
	}
	cout << endl;
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

static long long bubbleSort(vector<int>& vec) {
	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < vec.size() - 1; i++) {
		for (int j = 0; j < vec.size() - i - 1; j++) {
			if (vec[j] > vec[j + 1]) {
				int temp = vec[j];
				vec[j] = vec[j + 1];
				vec[j + 1] = temp;
			}
		}
	}
	auto end = chrono::high_resolution_clock::now();
	for (const auto& i : vec) {
		cout << i << " ";
	}
	cout << endl;
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

static long long insertionSort(vector<int>& vec) {
	auto start = chrono::high_resolution_clock::now();
	for (int i = 1; i < vec.size(); i++) {
		int key = vec[i];
		int j = i - 1;

		while (j >= 0 && vec[j] > key) {
			vec[j + 1] = vec[j];
			j--;
		}
		vec[j + 1] = key;
	}
	auto end = chrono::high_resolution_clock::now();
	for (const auto& i : vec) {
		cout << i << " ";
	}
	cout << endl;
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

static void merge(vector<int>& vec, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	vector<int> leftArr(n1);
	vector<int> rightArr(n2);

	for (int i = 0; i < n1; i++) {
		leftArr[i] = vec[left + i];
	}
	for (int i = 0; i < n2; i++) {
		rightArr[i] = vec[mid + 1 + i];
	}

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (leftArr[i] <= rightArr[j]) {
			vec[k] = leftArr[i];
			i++;
		}
		else {
			vec[k] = rightArr[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		vec[k] = leftArr[i];
		i++;
		k++;
	}

	while (j < n2) {
		vec[k] = rightArr[j];
		j++;
		k++;
	}
}

static void mergeSortHelper(vector<int>& vec, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;

		mergeSortHelper(vec, left, mid);
		mergeSortHelper(vec, mid + 1, right);

		merge(vec, left, mid, right);
	}
}

static long long mergeSort(vector<int>& vec) {
	auto start = chrono::high_resolution_clock::now();
	mergeSortHelper(vec, 0, vec.size() - 1);
	auto end = chrono::high_resolution_clock::now();
	for (const auto& i : vec) {
		cout << i << " ";
	}
	cout << endl;
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

static int partition(vector<int>& vec, int low, int high) {
	int pivot = vec[high];
	int i = low - 1;

	for (int j = low; j < high; j++) {
		if (vec[j] < pivot) {
			i++;
			swap(vec[i], vec[j]);
		}
	}
	swap(vec[i + 1], vec[high]);
	return i + 1;
}

static void quickSortHelper(vector<int>& vec, int low, int high) {
	if (low < high) {
		int pi = partition(vec, low, high);
		quickSortHelper(vec, low, pi - 1);
		quickSortHelper(vec, pi + 1, high);
	}
}
static long long quickSort(vector<int>& vec) {
	auto start = chrono::high_resolution_clock::now();
	quickSortHelper(vec, 0, vec.size() - 1);
	auto end = chrono::high_resolution_clock::now();
	for (const auto& i : vec) {
		cout << i << " ";
	}
	cout << endl;
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

int getScreenWidth() {
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		return csbi.srWindow.Right - csbi.srWindow.Left + 1;
	}
#else
	struct winsize w;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
		return w.ws_col;
	}
#endif
	return 80;
}

void centerText(const string& text) {
	int width = getScreenWidth();
	int padding = (width - text.length()) / 2;
	if (padding > 0) {
		cout << string(padding, ' ') << text;
	}
	else {
		cout << text;
	}
}
 
int main() {
	int option, numSorts;

	while (true) {
		centerText("============================================\n");
		centerText("|   Sorting Algorithm Performance Tester   |\n");
		centerText("============================================\n");

		do {
			centerText("How many items should be sorted? (Enter a positive number): ");
			cin >> numSorts;

			if (numSorts <= 0) {
				centerText("Error: Please enter a positive number greater than 0");
			}
		} while (numSorts <= 0);

		//fill random values
		random_device randomDev; //full disclosure, I have no clue how this random engine thing works
		mt19937 mersenneEng{ randomDev() };
		uniform_int_distribution<int> dist{ 1 , 99 };

		auto gen = [&]() {
			return dist(mersenneEng);
			};

		vector<int> testVec(numSorts);
		generate(testVec.begin(), testVec.end(), gen);

		cout << "\nUnsorted Vector: ";
		for (const auto& i : testVec) {
			cout << i << " ";
		}
		cout << "\n" << endl;

		centerText("============================================\n");
		centerText("|   1. std::sort()                         |\n");
		centerText("|   2. Bubble sort                         |\n");
		centerText("|   3. Insertion sort                      |\n");
		centerText("|   4. Merge sort                          |\n");
		centerText("|   5. Quick sort                          |\n");
		centerText("|   0. Exit                                |\n");
		centerText("============================================\n");

		centerText("Select a sorting algorithm: ");
		cin >> option;

		switch (option) {
		case 1: {
			cout << "std::sort() took " << stdSort(testVec) << " microseconds. " << endl;
			break;
		}
		case 2:
			cout << "bubble sort took " << bubbleSort(testVec) << " microseconds. " << endl;
			break;
		case 3:
			cout << "Insertion sort took " << insertionSort(testVec) << " microseconds. " << endl;
			break;
		case 4:
			cout << "Merge sort took " << mergeSort(testVec) << " microseconds. " << endl;
			break;
		case 5:
			cout << "Quick sort took " << quickSort(testVec) << " microseconds. " << endl;
			break;
		case 0:
			centerText("Saving and exiting...");
			exit(0);
		default:
			centerText("Invalid option, try again...");
		}
		centerText("=========================================================================================\n");
	}
}