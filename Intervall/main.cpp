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

int main(int argc, const char * argv[])
{
    while(true){
        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::vector<std::string> firstLine{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
        unsigned int n = std::stoi(firstLine[0]);
    	unsigned int m = std::stoi(firstLine[1]);
        
        if(n == 0 && m == 0) {
            return 0;
        }
        
        unsigned int cd;
        unsigned int highestVal;
        bool cds[1000001] = {false};
        for(unsigned int i = 0; i < n; i++) {
            std::getline(std::cin, line);
            cd = std::stoi(line);
            cds[cd] = true;
            if(i == n - 1) {
                highestVal = cd;
            }
        }
    
        unsigned int found = 0;
        for(unsigned int i = 0; i < m; i++) {
            
            std::getline(std::cin, line);
            if(cd > highestVal) {
                continue;
            }

            cd = std::stoi(line);
            
            if(cds[cd]) {
                found++;
            }
        }
    
        std::cout << found << std::endl;
    }
}
