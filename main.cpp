//
// Created by Administrador on 15/05/2024.
//

#include <iostream>
#include <iomanip>
#include "FileReaderToy.h"
#include "Menu.h"
#include "worldGraph.h"


int main(void)
{
    std::cout<< "HI there :D" << std::endl;

    WorldGraph current_graph = WorldGraph();


    //files/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv
    //../files/Toy-Graphs/Toy-Graphs/tourism.csv
    //FileReaderToy::add_all_toy("D:\\FEUP 2ano\\2 semestre\\Desenho de algoritmos\\DAProj2_v2\\DA2proj-v1\\files\\Toy-Graphs\\Toy-Graphs\\shipping.csv", current_graph);
    FileReaderToy::add_all_places_coordinates("../files/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", current_graph);
    FileReaderToy::add_all_connections_coordinates("../files/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_25.csv", current_graph,0);
    //FileReaderToy::add_all_toy("D:\\FEUP 2ano\\2 semestre\\Desenho de algoritmos\\DAProj2_v2\\DA2proj-v1\\files\\Toy-Graphs\\Toy-Graphs\\stadiums.csv", current_graph);


    Menu menu = Menu();
    menu.DisplayOptions();
    menu.MainMenu();
}