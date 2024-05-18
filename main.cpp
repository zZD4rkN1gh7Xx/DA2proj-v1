//
// Created by Administrador on 15/05/2024.
//

#include <iostream>
#include <iomanip>
#include "Menu.h"




int main(void)
{
    std::cout<< "HI there :D" << std::endl;

    WorldGraph current_graph = WorldGraph();




    Menu menu = Menu();
    menu.DisplayOptions();
    menu.MainMenu();
}