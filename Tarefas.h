#ifndef TAREFAS_H
#define TAREFAS_H

#include <cstdint>
#include <climits>
#include <vector>
#include <queue>
#include <utility>
#include <unordered_map>
#include <complex>
#include <cmath>
#include <omp.h>
#include "worldGraph.h"


void backtrack(WorldGraph& graph, Place place, std::vector<Place>& path, double weight, double& min_weight, int count, std::vector<Place>& min_path) {
    if ((count == graph.getNumVertex() + 1) && place.get_id() == 0) {
        if (weight < min_weight) {
            min_weight = weight;
            min_path = path;
        }
        return;
    }

    for (const auto& p : graph.findVertex(place)->getAdj()) {
        if (!p.getDest()->isVisited()) {
            p.getDest()->setVisited(true);
            path.push_back(p.getDest()->getInfo());

            backtrack(graph, p.getDest()->getInfo(), path, weight + p.getWeight(), min_weight, count + 1, min_path);
            path.pop_back();
            p.getDest()->setVisited(false);
        }
    }
}

std::vector<Place> tspBacktrack(WorldGraph& graph) {
    std::vector<Place> min_path;
    double min_weight = INT_MAX;

    for (auto& a : graph.getVertexSet()) {
        a->setVisited(false);
    }

    std::vector<Place> path{ graph.get_place(0) };
    backtrack(graph, graph.get_place(0), path, 0, min_weight, 1, min_path); // Start from the first node

    return min_path;
}



WorldGraph PrimMST(WorldGraph& graph) // opa como vamos sempre começar pelo node 0 acho que ta chill nao por por onde e que o algoritmo começa ne?
{
    graph.set_all_unvisited(); // dar  set a todos os nodes a unvisited

    WorldGraph MST_graph; // novo grafo que vai ficar com a MST

    for(auto& graph_place : graph.getVertexSet()) // vai adicionar todos os vertexes ao novo MST graph
    {
        MST_graph.add_place(graph_place->getInfo());
    }

    Vertex<Place> * start_place = graph.findVertex(graph.get_place(0)); // vai buscar o vertex do place com id==0
    start_place->setVisited(true); // dar visit ao start place para ele nao voltar a ser visitado


    while(!graph.are_all_visited())
    {
        Connection min_connection = graph.get_min_edge();

        MST_graph.add_connection(min_connection,0);

        graph.findVertex(graph.get_place(min_connection.get_id_B()))->setVisited(true);
    }

    return MST_graph;
}

std::vector<int> preorderWalk(WorldGraph& graph, Vertex<Place> * place)
{
    std::vector<int> traversalOrder;

    if(!place)
    {
        return traversalOrder;
    }

    place->setVisited(true);
    traversalOrder.push_back(place->getInfo().get_id());

    for(auto next_place : place->getAdj())
    {
        if(!next_place.getDest()->isVisited())
        {
            auto adjTraversal = preorderWalk(graph, next_place.getDest());
            traversalOrder.insert(traversalOrder.end(), adjTraversal.begin(), adjTraversal.end());
        }
    }

    return traversalOrder;

}

std::vector<int> tsp_triangular_aprox(WorldGraph& graph)
{
    vector<int> triangular_aprox;
    std::unordered_map<int,int> hamiltonian_path;

    WorldGraph MST_graph = PrimMST(graph);
    MST_graph.set_all_unvisited();

    Vertex<Place> * first_place = MST_graph.findVertex(MST_graph.get_place(0));

    std::vector<int> pre_order_walk = preorderWalk(MST_graph, first_place);


    for(auto place : MST_graph.getVertexSet())
    {
        hamiltonian_path[place->getInfo().get_id()] = 0;
    }

    for(auto place: pre_order_walk)
    {
        if(hamiltonian_path[place] == 0)
        {
            hamiltonian_path[place] = 1;
            triangular_aprox.push_back(place);
        }
    }

    triangular_aprox.push_back(0); // assim começa e acaba no mesmo sitio como pretendido
    return triangular_aprox;
}

double calculate_total_distance(WorldGraph& graph, const std::vector<int>& path)
{
    double total_distance = 0.0;

    for (size_t i = 0; i < path.size() - 1; ++i) {

        Place current_place = graph.get_place(path[i]);
        Place next_place = graph.get_place(path[i + 1]);

        Edge<Place> connection = graph.get_connection(current_place.get_id(), next_place.get_id());

        total_distance += connection.getWeight();
    }


    return total_distance;
}

// for later usage: (initial_temperature,  cooling_rate,  num_iterations)
// LARGE GRAPHS - (1000.0, 0.999, 10000)
// MEDIAN GRAPHS - (100.0, 0.995, 5000)
// LARGE GRAPHS - (10.0, 0.99, 3000)

std::vector<int> tsp_simulated_annealing(WorldGraph& graph, double initial_temperature, double cooling_rate, int num_iterations)
{
    graph.set_all_unvisited();

    std::vector<int> current_solution = tsp_triangular_aprox(graph);

    double current_distance = calculate_total_distance(graph, current_solution);

    std::vector<int> best_solution = current_solution;
    double best_distance = current_distance;

    double current_temperature = initial_temperature;

    for(auto i = 0; i < num_iterations; ++i)
    {
        std::vector<int> new_solution = current_solution;

        int index1 = std::rand() % (new_solution.size() - 2) + 1;
        int index2 = std::rand() % (new_solution.size() - 2) + 1;
        std::swap(new_solution[index1], new_solution[index2]);

        double new_distance = calculate_total_distance(graph, new_solution);
        double delta_distance = new_distance - current_distance;

        if (delta_distance < 0 || std::exp(-delta_distance / current_temperature) > static_cast<double>(std::rand()) / RAND_MAX)
        {
            current_solution = new_solution;
            current_distance = new_distance;
        }

        if (new_distance < best_distance)
        {
            best_solution = new_solution;
            best_distance = new_distance;
        }

        current_temperature *= cooling_rate;
    }

    return best_solution;
}

const double EARTH_RADIUS_KM = 6371.0;

double toRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

double haversine(Place place_A, Place place_B) {

    double  lat_A = toRadians(place_A.get_latitude());
    double lon_A= toRadians(place_A.get_longitude());
    double  lat_B = toRadians(place_B.get_latitude());
    double  lon_B = toRadians(place_B.get_longitude());


    double dlat = lat_B - lat_A;
    double dlon = lon_B - lon_A;
    double a = std::sin(dlat / 2) * std::sin(dlat / 2) + std::cos(lat_A) * std::cos(lat_B) * std::sin(dlon / 2) * std::sin(dlon / 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    double distance = EARTH_RADIUS_KM * c;

    return distance;
}

std::unordered_map<int,bool> set_not_visited(WorldGraph graph)
{
    std::unordered_map<int,bool> visited;

    for(auto k : graph.getVertexSet())
    {
        visited[k->getInfo().get_id()] = false;
    }

    return visited;
}

bool exists_path(WorldGraph graph,WorldGraph util_graph , int start_id)
{
    unordered_map<int, bool> visited = set_not_visited(graph);


    int n = graph.getNumVertex();
    if (start_id < 0 || start_id >= n) {
        std::cout << "Invalid start ID" << std::endl;
        return false;
    }

    std::queue<int> q;

    visited[start_id] = true;
    q.push(start_id);

    util_graph.add_place(graph.get_place(start_id));

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (auto neighbor : graph.findVertex(graph.get_place(current))->getAdj())
        {
            util_graph.add_place(neighbor.getDest()->getInfo());

            Connection new_con = Connection(current, neighbor.getDest()->getInfo().get_id(), neighbor.getWeight());
            util_graph.add_connection(new_con,0);

            if(neighbor.getDest()->getInfo().get_id() == start_id)
            {
                return true;
            }

            if(!visited[neighbor.getDest()->getInfo().get_id()])
            {
                visited[neighbor.getDest()->getInfo().get_id()] = true;
                q.push(neighbor.getDest()->getInfo().get_id());
            }
        }
    }

    return false;
}


std::vector<int> nearestNeighbor(WorldGraph graph, int start) {
    int numCities = graph.getNumVertex();
    std::unordered_map<int,bool> visited = set_not_visited(graph);
    std::vector<int> tour;


    int current = start;
    visited[current] = true;
    tour.push_back(current);

    for (int i = 0; i < numCities - 1; ++i) {
        int nearestCity = -1;
        double minDistance = std::numeric_limits<double>::max();

        // Find the nearest unvisited city
        for (int j = 0; j < numCities; ++j) {
            if (!visited[j]) {
                double dist = haversine(graph.get_place(current), graph.get_place(j));
                if (dist < minDistance) {
                    minDistance = dist;
                    nearestCity = j;
                }
            }
        }

        if (nearestCity == -1) {
            nearestCity = start;
        }

        current = nearestCity;
        visited[current] = true;
        tour.push_back(current);
    }

    // Return to the starting city to complete the tour
    tour.push_back(start);

    return tour;
}


std::vector<int> destroy(vector<int> current_sol,double rat)
{

    std::vector<int> partial_sol = current_sol;

    int numNodesToRemove = rat * current_sol.size();

    for (int i = 0; i < numNodesToRemove; ++i) {
        int indexToRemove = rand() % partial_sol.size();
        partial_sol.erase(partial_sol.begin() + indexToRemove);
    }

    return partial_sol;
}

std::vector<int> repair(WorldGraph graph, vector<int> partial_sol)
{
    int startNode = partial_sol.back();
    return nearestNeighbor(graph, startNode);
}




std::vector<int> tsp_realworld(WorldGraph& graph, int start_id, int num_iterations, double rat)
{
    std::vector<int> current_solution;

    // Create a utility graph (if needed) - check if this is necessary
    WorldGraph util_graph;

    // Check if a path exists from the starting node to itself
    if (exists_path(graph, util_graph, start_id))
    {
        // Construct an initial solution using the Nearest Neighbor algorithm
        current_solution = nearestNeighbor(graph, start_id);

        // Perform local search for improvement
        for (int i = 0; i < num_iterations; i++)
        {
            // Destroy the current solution to create a partial solution
            std::vector<int> partial_sol = destroy( current_solution,rat);

            // Repair the partial solution
            std::vector<int> repaired_sol = repair(graph, partial_sol);

            // Compare the total distances of the repaired solution and partial solution
            if (calculate_total_distance(graph, repaired_sol) < calculate_total_distance(graph, current_solution))
            {
                current_solution = repaired_sol;
            }
        }
    }
    else
    {
        // Output an error message if no path exists from the starting node to itself
        std::cout << "Error: No path exists from the starting node - " << start_id << " to itself." << std::endl;
    }

    return current_solution;
}

void printTspBacktrack(WorldGraph& graph) {
    vector<Place> result = tspBacktrack(graph);
    vector<int> ids;
    for (auto a : result) {
        std::cout<<a.get_id()<<" -> ";
        ids.push_back(a.get_id());
    }
    cout << "Total distance: "<< calculate_total_distance(graph, ids);


}






#endif // TAREFAS_H