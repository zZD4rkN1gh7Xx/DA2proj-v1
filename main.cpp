//
// Created by Administrador on 15/05/2024.
//

#include <iostream>
#include "FileReaderToy.h"
#include "Tarefas.h"
#include "worldGraph.h"

int main(void)
{
    std::cout<< "HI there :D" << std::endl;

    WorldGraph current_graph = WorldGraph();

    FileReaderToy::add_all_toy("../files/Toy-Graphs/Toy-Graphs/stadiums.csv", current_graph);

    for(auto a : current_graph.getVertexSet())
    {
        std::cout << a->getInfo().get_id() << std::endl;

    }

    tspBacktrack(current_graph);
}
