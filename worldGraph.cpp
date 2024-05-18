//
// Created by Administrador on 15/05/2024.
//

/**
    *@file worldGraph.cpp
    *@brief Implementation of the worldGraph class methods
*/

#include "worldGraph.h"

#include <cmath>

#include <complex>


WorldGraph::WorldGraph() {

}

void WorldGraph::add_place(Place place)
{
    addVertex(place);
    vertex_set.push_back(std::make_shared<Vertex<Place>>(place));
    place_map[place.get_id()] = place;
}

void WorldGraph::add_connection(Connection& connection, int status)
{
    Place placeA = get_place(connection.get_id_A());
    Place placeB = get_place(connection.get_id_B());
    double dist = connection.get_distance();

    #pragma omp critical
    {
        addEdge(placeA, placeB, dist);
        if (status == 0) {
            addEdge(placeB, placeA, dist);
        }
    }
}

Place WorldGraph::get_place(int id)
{
    auto it = place_map.find(id);
    if (it != place_map.end()) {
        return it->second;
    }

    throw std::invalid_argument("Place with the given ID not found");
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

std::vector<int> WorldGraph::random_path()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<int> random_path;

    int num_places = getNumVertex();

    int start_vertex = 0;

    random_path.push_back(start_vertex);

    findVertex(get_place(start_vertex))->setVisited(true);

    while (random_path.size() < num_places)
    {
        int next_place = std::rand() % num_places;
        if (!findVertex(get_place(next_place))->isVisited())
        {
            random_path.push_back(next_place);
            findVertex(get_place(next_place))->setVisited(true);
        }
    }

    random_path.push_back(0);

    return random_path;
}

double toRadianss(double degrees) {
    return degrees * M_PI / 180.0;
}

double haversinee(Place place_A, Place place_B) {

    double  lat_A = toRadianss(place_A.get_latitude());
    double lon_A= toRadianss(place_A.get_longitude());
    double  lat_B = toRadianss(place_B.get_latitude());
    double  lon_B = toRadianss(place_B.get_longitude());


    double dlat = lat_B - lat_A;
    double dlon = lon_B - lon_A;
    double a = std::sin(dlat / 2) * std::sin(dlat / 2) + std::cos(lat_A) * std::cos(lat_B) * std::sin(dlon / 2) * std::sin(dlon / 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    double distance = 6371.0 * c;

    return distance;
}


Edge<Place> WorldGraph::get_connection(int id_A, int id_B)
{
    auto a = findVertex(get_place(id_A));

    for(auto k : a->getAdj())
    {
        if(k.getDest()->getInfo().get_id() == id_B)
            return k;
    }
    Connection new_con = Connection(id_A, id_B, haversinee(get_place(id_A), get_place(id_B)));
    add_connection(new_con, 0);
    return get_connection(id_A, id_B);
}




