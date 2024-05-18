#ifndef TAREFAS_H
#define TAREFAS_H

#include <cstdint>
#include <climits>
#include <vector>
#include <queue>
#include <utility>
#include <unordered_map>
#include <complex>
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

        MST_graph.add_connection(min_connection);

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

    std::vector<int> current_solution = graph.random_path();

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






#endif // TAREFAS_H
