//
// Created by jogos on 5/15/2024.
//

/**
    *@file fileReaderToy.h
    *@brief Header file for FileReaderToy class
*/

#ifndef FILEREADER_H
#define FILEREADER_H
#include "Graph.h"
#include "worldGraph.h"

class FileReaderToy {

    public:
        static void add_all_toy(const std::string &filename , WorldGraph &OurGraph);
        static void add_all_tourism(const std::string &filename , WorldGraph &OurGraph);
        static void add_all_places_coordinates(const std::string &filename , WorldGraph &OurGraph, int places);
        static void add_all_connections_coordinates(const std::string &filename , WorldGraph &OurGraph,int status);

};



#endif //FILEREADER_H
