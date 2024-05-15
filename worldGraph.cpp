//
// Created by Administrador on 15/05/2024.
//

#include "worldGraph.h"

WorldGraph::WorldGraph() {

}

void WorldGraph::add_place(Place& place)
{
    addVertex(place);
}

void WorldGraph::add_connection(Connection& connection)
{
    addEdge(get_place(connection.get_id_A()), get_place(connection.get_id_B()), connection.get_distance());
}

Place WorldGraph::get_place(int id)
{
    for(auto& a : getVertexSet())
    {
        if(a->getInfo().get_id() == id)
            return a->getInfo();
    }
}

Edge<Place> WorldGraph::get_connection(int id_A, int id_B)
{
    auto a = findVertex(get_place(id_A));

    for(auto k : a->getAdj())
    {
        if(k.getDest()->getInfo().get_id() == id_B)
            return k;
    }
}

