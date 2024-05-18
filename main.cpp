//
// Created by Administrador on 15/05/2024.
//

#include <iostream>
#include <iomanip>
#include "FileReaderToy.h"
#include "Tarefas.h"
#include "worldGraph.h"


int main(void)
{
    std::cout<< "HI there :D" << std::endl;

    WorldGraph current_graph = WorldGraph();


    //files/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv
    //../files/Toy-Graphs/Toy-Graphs/tourism.csv
    //FileReaderToy::add_all_toy("D:\\FEUP 2ano\\2 semestre\\Desenho de algoritmos\\DAProj2_v2\\DA2proj-v1\\files\\Toy-Graphs\\Toy-Graphs\\shipping.csv", current_graph);
    FileReaderToy::add_all_places_coordinates("D:\\FEUP 2ano\\2 semestre\\Desenho de algoritmos\\DAProj2_v2\\DA2proj-v1\\files\\Extra_Fully_Connected_Graphs\\Extra_Fully_Connected_Graphs\\nodes.csv", current_graph);
    FileReaderToy::add_all_connections_coordinates("D:\\FEUP 2ano\\2 semestre\\Desenho de algoritmos\\DAProj2_v2\\DA2proj-v1\\files\\Extra_Fully_Connected_Graphs\\Extra_Fully_Connected_Graphs\\edges_25.csv", current_graph);
    //FileReaderToy::add_all_toy("D:\\FEUP 2ano\\2 semestre\\Desenho de algoritmos\\DAProj2_v2\\DA2proj-v1\\files\\Toy-Graphs\\Toy-Graphs\\stadiums.csv", current_graph);



    //std::vector<int> a = tsp_triangular_aprox(current_graph);

    //
    /*std::vector<int> a = tsp_simulated_annealing(current_graph, 1000, 0.995, 1000);

    for(auto b : a)
    {
       std::cout << b << "->" ;
    }

    std::cout << calculate_total_distance(current_graph,a);*/
    //std::cout << std::endl;
    /*vector<Place> result = tspBacktrack(current_graph);
    for (auto a : result) {
        cout << a.get_id() << " - ";
    }*/

    for(auto a : current_graph.getVertexSet()) {
        std::cout << a->getInfo().get_id() << " " << std::setprecision(15)  << a->getInfo().get_longitude() << " " << std::setprecision(15) << a->getInfo().get_longitude()
                  << std::endl;
    }
}
