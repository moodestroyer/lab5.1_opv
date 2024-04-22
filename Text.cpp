
#include <iostream>﻿
#include <fstream>
#include <string>
#include <omp.h>
#include <unordered_map>
#include <sstream>
#include <algorithm>


std::ifstream file("C:/Users/User/Downloads/open.txt");

int main() {

	setlocale(LC_ALL, "RU");

	std::unordered_map<std::string, int> mp;

	int num_threads = omp_get_max_threads();
	std::string line;
	int total_lines = 0;

	if (file.is_open()) {
		while (std::getline(file, line)) {
			total_lines++;
		}
	}
	int size_of_part = total_lines / num_threads;

#pragma omp parallel
	{

		int num_current_thread = omp_get_thread_num();
		int start = num_current_thread * size_of_part;
		int end = start + size_of_part;
		file.clear();
		file.seekg(start);

		for (int i = start; i < end; i++) {
			std::getline(file, line);
			std::string temp;
			std::istringstream str(line);
			while (str >> temp) {
#pragma omp critical
				{
					mp[temp]++;
				}
			}
		}
	}

	std::vector<std::pair<std::string, int>> wordVector(mp.begin(), mp.end());
	sort(wordVector.begin(), wordVector.end(),
		[](const auto& a, const auto& b) {
			return a.second > b.second;
		});

	int countToShow = std::min(10, static_cast<int>(wordVector.size()));
	for (int i = 0; i < countToShow; ++i) {
		std::cout << wordVector[i].first << " количество: " << wordVector[i].second << " " << std::endl;
	}
	//for (const auto& pair : mp) {
		//std::cout << pair.first << ": " << pair.second << std::endl;
	//}
	return 0;
}
