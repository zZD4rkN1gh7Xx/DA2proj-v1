//
// Created by jogos on 5/18/2024.
//

#ifndef MENU_H
#define MENU_H
#include <worldGraph.h>


class Menu {
    WorldGraph current_graph;

    public:
    Menu();
    static void DisplayAlgorithm(WorldGraph graph);
    void MainMenu();
    void Menu2();
    void LoadGraph(const std::string &filename);
    void LoadFullGraph(int edges);
    void LoadRealGraph(int graphNumber);
    static void DisplayOptions();
    static void DisplayOptionsMore();
    static bool ToMain();

};




#endif //MENU_H
