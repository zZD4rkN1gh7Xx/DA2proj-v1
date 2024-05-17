//
// Created by Administrador on 15/05/2024.
//

#ifndef DAPROJ2_V2_WORLDGRAPH_H
#define DAPROJ2_V2_WORLDGRAPH_H

#include "Graph.h"
#include "place.h"
#include "connection.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

class WorldGraph :public Graph<Place>
{
    public:
        WorldGraph();
        void add_place(Place place);
        void add_connection(Connection& connection);
        Place get_place(Place id);
        Edge<Place> get_connection(int id_A, int id_B);
        void set_all_unvisited();
        bool are_all_visited();
        vector<Edge<Place>> sort_edges();
        Connection get_min_edge();

};

template bool Graph<Place>::addVertex(Place &in);

#endif //DAPROJ2_V2_WORLDGRAPH_H
