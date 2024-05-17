//
// Created by Administrador on 15/05/2024.
//

#include "worldGraph.h"

WorldGraph::WorldGraph() {

}

void WorldGraph::add_place(Place place)
{
    addVertex(place);
}

void WorldGraph::add_connection(Connection& connection)
{
    addEdge(get_place(connection.get_id_A()), get_place(connection.get_id_B()), connection.get_distance());
}

Place WorldGraph::get_place(Place id)
{
    if(id == -1)
    {
        throw std::invalid_argument("Invalid place ID: -1");
    }

    for(auto a : getVertexSet())
    {
        if(a->getInfo().get_id() == id.get_id())
            return a->getInfo();
    }

    // If the place with the given ID is not found, you might want to throw an exception or return a default value.
    throw std::invalid_argument("Place with the given ID not found");
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

void WorldGraph::set_all_unvisited()
{
    for(auto& place : getVertexSet())
    {
        place->setVisited(false);
    }
}

bool WorldGraph::are_all_visited()
{
    for(auto a : getVertexSet())
    {
        if(!a->isVisited())
        {
            return false;
        }
    }

    return true;
}
vector<Edge<Place>> WorldGraph::sort_edges()
{
    vector<Edge<Place>> weight_vector;

    for(auto& place : getVertexSet())
    {
        for(auto& connection : place->getAdj())
        {
            weight_vector.push_back(connection);
        }
    }

    std::sort(weight_vector.begin(), weight_vector.end(), [](Edge<Place> a, Edge<Place> b) {
        return a.getWeight() < b.getWeight();
    });

    return weight_vector;
}

Connection WorldGraph::get_min_edge()
{
    // Initialize min_distance_connection with a large weight
    Connection min_distance_connection(-1, -1, std::numeric_limits<double>::max());

    for(auto place : getVertexSet())
    {

        if(place->isVisited())
        {
            for(auto connection : place->getAdj())
            {

                if(connection.getDest() && !connection.getDest()->isVisited() && connection.getWeight() < min_distance_connection.get_distance())
                {

                    min_distance_connection = Connection(place->getInfo().get_id(), connection.getDest()->getInfo().get_id(), connection.getWeight());
                }
            }
        }
    }


    return min_distance_connection;
}



