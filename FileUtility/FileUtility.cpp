/*
Author: Levi McLean (LeviM_0323)
File: FileUtility.cpp
Created: May 22nd, 2025
Purpose: This project will act as a simple file utility in C++ ran from the command line
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <filesystem>
#include <chrono>
#include <ctime>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;
namespace fs = std::filesystem;

struct FileInfo {
	string name;
	string ext;
	uintmax_t size;
	string dateStr;
	fs::file_time_type date;
};

string format_file_time(fs::file_time_type ftime) {
	auto sctp = chrono::time_point_cast<chrono::system_clock::duration>(
		ftime - fs::file_time_type::clock::now()
		+ chrono::system_clock::now()
	);
	time_t cftime = chrono::system_clock::to_time_t(sctp);
	char buffer[20];
	struct tm timeinfo;
	localtime_s(&timeinfo, &cftime);
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", &timeinfo);
	return buffer;
}

vector<FileInfo> files;
vector<string> flags;

int main(int argc, char* argv[]) {
	fs::path filepath;
	for (int i = 1; i < argc; ++i) {
		string arg = argv[i];
		if (arg[0] == '-') {
			size_t pos = 1;
			while (pos < arg.size()) {
				if (arg.substr(pos, 2) == "Ss" || arg.substr(pos, 2) == "Sn" ||
					arg.substr(pos, 2) == "Se" || arg.substr(pos, 2) == "Sd" ||
					arg.substr(pos, 2) == "Kb" || arg.substr(pos, 2) == "Mb" ||
					arg.substr(pos, 2) == "Gb") {
					flags.push_back("-" + arg.substr(pos,2));
					pos += 2;
				}
				else if (arg[pos] == 'r' || arg[pos] == 'R') {
					flags.push_back("-r");
					pos += 1;
				}
				else {
					pos += 1;
				}
			}
		}
		else {
			filepath = arg;
		}
	}

	uintmax_t total_size = 0;

	cout << "\nPath: " << filepath.string() << endl;

	cout << left
		<< setw(50) << "File name"
		<< setw(20) << "File type"
		<< setw(20) << "File size"
		<< setw(20) << "Date modified"
		<< endl;
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;

	if (filesystem::is_directory(filepath)) {
		files.reserve(10000);
		try {
			for (const auto& entry : fs::recursive_directory_iterator(filepath, fs::directory_options::skip_permission_denied)) {
				if (entry.is_regular_file()) {
					std::error_code ec;
					uintmax_t size = entry.file_size(ec);
					if (ec) continue;
					auto ftime = entry.last_write_time(ec);
					if (ec) continue;
					files.push_back({
						entry.path().filename().string(),
						entry.path().has_extension() ? entry.path().extension().string() : "",
						size,
						format_file_time(ftime),
						ftime
						});
					total_size += size;
				}
			}
		}
		catch (const std::exception& e) {
			cerr << "Error while iterating directory: " << e.what() << endl;
		}
	}
	else if (fs::is_regular_file(filepath)) {
		std::error_code ec;
		uintmax_t size = fs::file_size(filepath, ec);
		if (!ec) {
			auto ftime = fs::last_write_time(filepath, ec);
			if (!ec) {
				files.push_back({
					filepath.filename().string(),
					filepath.has_extension() ? filepath.extension().string() : "",
					size,
					format_file_time(ftime),
					ftime
				});
				total_size += size;
			}
		}
	}
	else {
		cerr << "Error: The provided path is inaccessible or does not exist.\n";
	}

	double total_size_Kb = total_size / 1000.0;
	double total_size_Mb = total_size / 1000000.0;
	double total_size_Gb = total_size / 1000000000.0;

	//cout << "\n";
	//cout << "DEBUG: formatFlag=" << formatFlag << "\n";
	//cout << "DEBUG: total_size=" << total_size << "\n";
	//cout << "DEBUG: total_size_Mb=" << total_size_Mb << "\n";

	cout << fixed << setprecision(2);
	for (const auto& flag : flags) {
		if (flag == "-Ss") {
			sort(files.begin(), files.end(), [](const FileInfo& a, const FileInfo& b) { return a.size > b.size; });
		}
		else if (flag == "-Sn") {
			sort(files.begin(), files.end(), [](const FileInfo& a, const FileInfo& b) { return a.name > b.name; });
		}
		else if (flag == "-Se") {
			sort(files.begin(), files.end(), [](const FileInfo& a, const FileInfo& b) { return a.ext > b.ext; });
		}
		else if (flag == "-Sd") {
			sort(files.begin(), files.end(), [](const FileInfo& a, const FileInfo& b) { return a.date > b.date; });
		}
	}
	if (find(flags.begin(), flags.end(), "-r") != flags.end()) {
		reverse(files.begin(), files.end());
	}

	for (const auto& f : files) {
		cout << left
			<< setw(50) << f.name
			<< setw(20) << f.ext
			<< setw(20) << f.size
			<< setw(20) << f.dateStr
			<< endl;
	}

	if (find(flags.begin(), flags.end(), "-Gb") != flags.end()) {
		cout << filepath.string() << " Total Size: " << total_size_Gb << " GB" << endl;
	}
	else if (find(flags.begin(), flags.end(), "-Mb") != flags.end()) {
		cout << filepath.string() << " Total Size: " << total_size_Mb << " MB" << endl;
	}
	else if (find(flags.begin(), flags.end(), "-Kb") != flags.end()) {
		cout << filepath.string() << " Total Size: " << total_size_Kb << " KB" << endl;
	}
	else {
		cout << filepath.string() << " Total Size: " << total_size << " bytes" << endl;
	}

	return 0;
}
