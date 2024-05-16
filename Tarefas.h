#ifndef TAREFAS_H
#define TAREFAS_H

#include <cstdint>
#include <climits>
#include <vector>
#include "worldGraph.h"

void backtrack(WorldGraph& graph, Place place, std::vector<Place>& path, double weight, double& min_weight, int count, std::vector<Place>& min_path) {
    if (count == graph.getNumVertex() && place.get_id() == 0) {
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

            /*for (auto a : path) {
                cout << a.get_id() << " - ";
            }

            cout << endl;
*/
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

#endif // TAREFAS_H
