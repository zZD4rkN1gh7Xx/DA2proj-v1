//
// Created by Administrador on 15/05/2024.
//

#include "worldGraph.h"



void WorldGraph::add_place(Place& new_place)
{
    addVertex(new_place);
}
void add_connection(Connection& connection);
Place get_place(int id);
Connection get_connection(int id_A, int id_B);