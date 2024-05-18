//
// Created by jogos on 5/18/2024.
//

#ifndef MENU_H
#define MENU_H
#include <worldGraph.h>

/**
    *@file menu.h
    *@brief Header file for the Menu class
*/

class Menu {
    WorldGraph current_graph;

    public:
    Menu();
    void DisplayAlgorithm(WorldGraph graph);
    void MainMenu();
    void Menu2();
    void LoadGraph(const std::string &filename);
    void LoadFullGraph(int edges);
    void LoadRealGraph(int graphNumber);
    void DisplayOptions();
    static void DisplayOptionsMore();
    bool ToMain();

};




#endif //MENU_H
