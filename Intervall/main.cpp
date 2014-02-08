//
//  main.cpp
//  popup-v1-help
//
//  Created by Mathias Lindblom on 2014-01-27.
//  Copyright (c) 2014 Mathias Lindblom. All rights reserved.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <set>
#include <stdexcept>

#include "IntervallCoverage.h"

int main(int argc, const char * argv[]) {
    std::string line;
    while(std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::vector<std::string> firstLine{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
        double start = std::stof(firstLine[0]);
    	double end = std::stof(firstLine[1]);
//        Intervall<double> mainIntervall(start, end);
        Intervall<StringNumber> mainIntervall(firstLine[0], firstLine[1]);
        
        std::getline(std::cin, line);
        unsigned int n = std::stoi(line);
        
//        std::vector<Intervall<double>> intervalls;
        std::vector<Intervall<StringNumber>> intervalls;
        
        for(int i = 0; i < n; i++) {
            std::getline(std::cin, line);
            std::istringstream iss(line);
            std::vector<std::string> inputIntervall{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
//            intervalls.push_back(Intervall<double>(std::stod(inputIntervall[0]), std::stod(inputIntervall[1])));
            intervalls.push_back(Intervall<StringNumber>(inputIntervall[0], inputIntervall[1]));
        }
        
        std::vector<unsigned int> intervallIndexes;
        minimalCoverage(mainIntervall, intervalls.begin(), intervalls.end(), back_inserter(intervallIndexes));
        if(minimalCoverageResult == MIN_COV_FAILED) {
                std::cout << "impossible" << std::endl;
        } else {
            std::cout << intervallIndexes.size() << std::endl;
            for(int i = 0; i < intervallIndexes.size(); i++) {
                unsigned int index = intervallIndexes[i];
                if(i == 0) {
                    std::cout << index;
                } else {
                    std::cout << " " << index;
                }
            }
            if(intervallIndexes.size() < 1) {
                throw new std::invalid_argument("Strange");
            }
            std::cout << std::endl;
        }
    }
}
