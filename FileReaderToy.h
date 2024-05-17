//
// Created by jogos on 5/15/2024.
//

#ifndef FILEREADER_H
#define FILEREADER_H
#include "Graph.h"
#include "worldGraph.h"

class FileReaderToy {

    public:
        static void add_all_toy(const std::string &filename , WorldGraph &OurGraph);
        static void add_all_tourism(const std::string &filename , WorldGraph &OurGraph);
        static void add_all_places_coordinates(const std::string &filename , WorldGraph &OurGraph);
        static void add_all_connections_coordinates(const std::string &filename , WorldGraph &OurGraph);
};



#endif //FILEREADER_H
