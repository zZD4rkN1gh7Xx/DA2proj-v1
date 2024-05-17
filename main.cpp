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

    /*
    Place a = Place(1,-43.30181022730023,-23.011972156360795);
    Place b = Place(2,-43.21636554138819,-22.920250516077687);
    Place c = Place(3,-43.32304806953678,-23.006841073845603);
    Place d = Place(4,-43.33148035581998,-22.946701029022186);

    current_graph.add_place(a);
    current_graph.add_place(b);
    current_graph.add_place(c);
    current_graph.add_place(d);
     */

    //files/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv
    //../files/Toy-Graphs/Toy-Graphs/tourism.csv
    FileReaderToy::add_all_toy("D:\\FEUP 2ano\\2 semestre\\Desenho de algoritmos\\DAProj2_v2\\DA2proj-v1\\files\\Toy-Graphs\\Toy-Graphs\\shipping.csv", current_graph);
    //FileReaderToy::add_all_places_coordinates("D:\\FEUP 2ano\\2 semestre\\Desenho de algoritmos\\DAProj2_v2\\DA2proj-v1\\files\\Extra_Fully_Connected_Graphs\\Extra_Fully_Connected_Graphs\\nodes.csv", current_graph);
    //FileReaderToy::add_all_connections_coordinates("D:\\FEUP 2ano\\2 semestre\\Desenho de algoritmos\\DAProj2_v2\\DA2proj-v1\\files\\Extra_Fully_Connected_Graphs\\Extra_Fully_Connected_Graphs\\edges_25.csv", current_graph);
    //FileReaderToy::add_all_toy("D:\\FEUP 2ano\\2 semestre\\Desenho de algoritmos\\DAProj2_v2\\DA2proj-v1\\files\\Toy-Graphs\\Toy-Graphs\\stadiums.csv", current_graph);



    //std::vector<int> a = tsp_triangular_aprox(current_graph);

    std::vector<Place> a = tspBacktrack(current_graph);

    for(auto b : a)
    {
       std::cout << b.get_id() << "->" ;
    }

    //std::cout << std::endl;
    /*vector<Place> result = tspBacktrack(current_graph);
    for (auto a : result) {
        cout << a.get_id() << " - ";
    }*/

    /*for(auto a : current_graph.getVertexSet())
    {
        std::cout << a->getInfo().get_id() << " " << a->getInfo().get_longitude() << " " << a->getInfo().get_longitude() << std::endl;
    }*/


}
