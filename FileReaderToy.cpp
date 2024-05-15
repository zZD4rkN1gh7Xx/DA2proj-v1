//
// Created by jogos on 5/15/2024.
//

#include "FileReaderToy.h"

void FileReaderToy::add_edges(const std::string &filename , Graph<int> &OurGraph) {
    std::ifstream inputfile(filename);

    if(inputfile.is_open()) {
        std::string line;
        std::getline(inputfile,line);

        while(std::getline(inputfile,line) {
            
        }

    }
}
