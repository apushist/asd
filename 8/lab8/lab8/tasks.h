#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <random>


void generateData(const std::string& filename, int Nmax, int numSets) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error creating file\n";
        return;
    }

    file << Nmax << " " << numSets << "\n";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, Nmax);

    for (int i = 0; i < numSets; ++i) {
        int setSize = dist(gen);
        file << setSize << " ";
        std::set<int> subset;
        for (int j = 0; j < setSize; ++j) {
            int elem = dist(gen);
            subset.insert(elem);
            file << elem << " ";
        }
        file << "\n";
    }

    file.close();
}


void task1(std::string filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Unable to open file " << filename << std::endl;
		return;
	}
	int Nmax, countOfSets;
	file >> Nmax >> countOfSets;
	std::vector<std::set<int>> sets = std::vector<std::set<int>>(countOfSets);
	for (int i = 0;i < countOfSets;i++) {
		int elemCount;
		file >> elemCount;
		std::set<int> seti;
		for (int j = 0; j < elemCount;j++) {
			int x;
			file >> x;
			seti.insert(x);
		}
		sets.push_back(seti);
	}


	file.close();
}
