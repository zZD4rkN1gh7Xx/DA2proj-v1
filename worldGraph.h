//
// Created by Administrador on 15/05/2024.
//



/**
    *@file worldGraph.h
    *@brief Header file for the worldGraph class an extention of graph.h
*/

#ifndef DAPROJ2_V2_WORLDGRAPH_H
#define DAPROJ2_V2_WORLDGRAPH_H

#include "Graph.h"
#include "place.h"
#include "connection.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <unordered_map>

class WorldGraph :public Graph<Place>
{
    private:
        std::vector<shared_ptr<Vertex<Place>>> vertex_set;
        std::unordered_map<int, std::vector<Connection>> adj_list;
        unordered_map<int, Place> place_map;

    public:
        WorldGraph();
        void add_place(Place place);
        void add_connection(Connection& connection, int status);
        Place get_place(int id);
        Edge<Place> get_connection(int id_A, int id_B);
        void set_all_unvisited();
        bool are_all_visited();
        vector<Edge<Place>> sort_edges();
        Connection get_min_edge();
        std::vector<int> random_path();

};

template bool Graph<Place>::addVertex(Place &in);

#endif //DAPROJ2_V2_WORLDGRAPH_H
