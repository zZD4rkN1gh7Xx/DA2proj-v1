//
// Created by jogos on 5/15/2024.
//

#ifndef FILEREADER_H
#define FILEREADER_H
#include "Graph.h"


class FileReaderToy {

    public:
        static void add_edges(const std::string &filename , Graph<int> &OurGraph);
        static void add_nodes(const std::string &filename, Graph<int> &OurGraph);
};



#endif //FILEREADER_H
