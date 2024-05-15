//
// Created by Administrador on 15/05/2024.
//

#ifndef DAPROJ2_V2_WORLDGRAPH_H
#define DAPROJ2_V2_WORLDGRAPH_H

#include "Graph.h"
#include "place.h"
#include "connection.h"
#include <iostream>

class WorldGraph :public Graph<Place>
{
    public:
        WorldGraph();
        void add_place(Place& place);
        void add_connection(Connection& connection);
        Place get_place(int id);
        Connection get_connection(int id_A, int id_B);

};

template bool Graph<Place>::addVertex(Place &in);

#endif //DAPROJ2_V2_WORLDGRAPH_H
