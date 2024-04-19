#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <sstream>


void generateInput(const std::string& filename, int Nmax, int numSets) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error creating file\n";
        return;
    }
    file << Nmax << " " << numSets << "\n";
    for (int i = 0; i < numSets; ++i) {
        int setSize = rand() % Nmax;
        file << setSize << " ";
        std::set<int> subset;
        while (subset.size() < setSize) {
            int elem = rand() % Nmax + 1;
            subset.insert(elem);
        }
        for (int elem : subset) {
            file << elem << " ";
        }
        file << "\n";
    }
    file.close();
}


std::pair< std::vector<std::vector<int>>,int> getSetsFromFile(std::string filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Unable to open file " << filename << std::endl;
		return std::make_pair(std::vector<std::vector<int>>(),0);
	}
	int Nmax, countOfSets;
	file >> Nmax >> countOfSets;
	std::vector<std::vector<int>> sets = std::vector<std::vector<int>>();
    sets.reserve(countOfSets);
	for (int i = 0;i < countOfSets;i++) {
		int elemCount;
		file >> elemCount;
		std::vector<int> seti;
		for (int j = 0; j < elemCount;j++) {
			int x;
			file >> x;
			seti.push_back(x);
		}
		sets.push_back(seti);
	}

	file.close();
    return std::make_pair( sets,Nmax );
}

std::vector<int> task1(std::string filename) {
    auto pair = getSetsFromFile(filename);
    std::vector<std::vector<int>> sets = pair.first;
    int Nmax = pair.second;
    std::vector<int> S = std::vector<int>();
    for (int i = 1; i <= Nmax;i++) {
        S.push_back(i);
    }
    std::vector<int> resInds = std::vector<int>();
    
    while (!S.empty())
    {
        int ind = -1;
        size_t mxLength = 0;
        for (int k = 0; k < sets.size();k++) {
            std::vector<int> v_intersection;
            std::set_intersection(S.begin(), S.end(), sets[k].begin(), sets[k].end(), std::back_inserter(v_intersection));
            if (v_intersection.size() > mxLength) {
                mxLength = v_intersection.size();
                ind = k;
            }
        }

        std::vector<int> diff;
        std::set_difference(S.begin(), S.end(), sets[ind].begin(), sets[ind].end(), std::back_inserter(diff));
        
        S = diff;
        resInds.push_back(ind+1);
    }

    return resInds;
}


std::vector<std::string> task15(std::string str, unsigned int n) {
    std::vector<std::string> result;
    std::istringstream iss(str);

    std::string word;
    std::string line;

    while (iss >> word) {
        if (line.empty()) {
            line += word;
        }
        else
        {
            if (line.size() + word.size() < n) {
                line += " " + word;
            }
            else {
                
                int spacesBetweenWordsCount = std::count(line.begin(), line.end(), ' ');
                
                int additionalSpaces = n - line.size();
                int additionalSpacesPerWord = additionalSpaces / spacesBetweenWordsCount;
                int extraSpaces = additionalSpaces % spacesBetweenWordsCount;

                std::string alignedLine;
                int ind = 0;
                int endInd;
                while ((endInd = line.find(' ', ind)) != std::string::npos) {
                    alignedLine += line.substr(ind, endInd - ind+1);
                    int countOfSpaces = additionalSpacesPerWord + (extraSpaces-- > 0 ? 1 : 0);
                    alignedLine.append(countOfSpaces, ' ');
                    ind = endInd + 1;
                }
                alignedLine += line.substr(ind);
                result.push_back(alignedLine);

                line = word;
            }
        }
    }
    if (!line.empty()) {
        result.push_back(line);
    }

    return result;
}