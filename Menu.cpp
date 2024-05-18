//
// Created by jogos on 5/18/2024.
//

/**
    *@file menu.cpp
    *@brief Implementation of the Menu class methods
*/

#include "Menu.h"

#include "FileReaderToy.h"
#include <iostream>

#include "Tarefas.h"


Menu::Menu() {
    this->current_graph = WorldGraph();
}

void Menu::DisplayOptions() {
    std::string type;
    std::cout<< std::endl << "|" << " Travelling Salesperson Problem (page 1) " << "|" << std::endl << std::endl;
    std::cout<< "1 - Shipping (Toy)" << std::endl;
    std::cout<< "2 - Stadiums (Toy)" << std::endl;
    std::cout<< "3 - Tourism (Toy)" << std::endl;
    std::cout<< "4 - Fully Connected 25 edges" << std::endl;
    std::cout<< "5 - Fully Connected 50 edges" << std::endl;
    std::cout<< "6 - Fully Connected 75 edges" << std::endl;
    std::cout<< "7 - Fully Connected 100 edges" << std::endl;
    std::cout<< "8 - Fully Connected 200 edges" << std::endl;
    std::cout<< "9 - Fully Connected 300 edges" << std::endl;
    std::cout<< "0 - More Options" << std::endl;
}

void Menu::DisplayOptionsMore() {
    std::string type;
    std::cout<< std::endl << "|" << " Travelling Salesperson Problem (page 2) " << "|" << std::endl << std::endl;
    std::cout<< "1 - Fully Connected 400 edges" << std::endl;
    std::cout<< "2 - Fully Connected 500 edges" << std::endl;
    std::cout<< "3 - Fully Connected 600 edges" << std::endl;
    std::cout<< "4 - Fully Connected 700 edges" << std::endl;
    std::cout<< "5 - Fully Connected 800 edges" << std::endl;
    std::cout<< "6 - Fully Connected 900 edges" << std::endl;
    std::cout<< "7 - Real World Graph 1" << std::endl;
    std::cout<< "8 - Real World Graph 2" << std::endl;
    std::cout<< "9 - Real World Graph 3" << std::endl;
    std::cout<< "0 - Go Back" << std::endl;
}


void Menu::DisplayAlgorithm(WorldGraph graph)
{
    std::cout<< std::endl << "|" << " Travelling Salesperson Problem " << "|" << std::endl << std::endl;
    std::cout<< "1 - Backtracking Algorithm (4.1)" << std::endl;
    std::cout<< "2 - Triangular Approximation Heuristic (4.2)" << std::endl;
    std::cout<< "3 - Simulated Annealing Heuristic (recommended 10k iterations) (4.3)" << std::endl;
    std::cout<< "4 - Large Neighbour Search (4.4)" << std::endl;

    std::string ans;
    while(true) {
        std::cout << "Choose an option: ";
        std::cin>>ans;
        std::cout << std::endl;
        if (ans == "1") {
            printTspBacktrack(graph);
        }
        else if (ans == "2") {
            printTriangular(graph);
        }
        else if (ans == "3") {
            std::string temp, cooling, iterations;
            std::cout << "Input initial temperature: ";
            std::cin>>temp;
            std::cout << std::endl << "Input cooling rate: ";
            std::cin>>cooling;
            std::cout << std::endl << "Input number of iterations: ";
            std::cin>>iterations;
            std::cout << std::endl << std::endl;

            print_tsp_simulated_annealing(graph, stod(temp), stod(cooling), stoi(iterations));
        }

        else if (ans == "4") {
            std::string startId, iterations, ratio;
            std::cout << "Input starting node id: ";
            std::cin>>startId;
            std::cout << std::endl << "Input iterations (10 recommended): ";
            std::cin>>iterations;
            std::cout << std::endl << "Input ratio (between 0 and 1): ";
            std::cin>>ratio;
            std::cout << std::endl << std::endl;

            print_tsp_realworld(graph, stoi(startId), stoi(iterations), stod(ratio));
        }
        else {
            std::cout << "Invalid option, please try again." << std::endl;
            continue;
        }
        if(ToMain()) {
            DisplayOptions();
            MainMenu();
            break;
        }
        else
            break;
    }
}


void Menu::MainMenu() {
    std::string ans;
    while(true) {
        std::cout << "Choose an option: ";
        std::cin>>ans;
        std::cout <<std::endl;
        current_graph = WorldGraph();
        if (ans == "1") {
            LoadGraph("../files/Toy-Graphs/Toy-Graphs/shipping.csv");
        }
        else if (ans == "2") {
            LoadGraph("../files/Toy-Graphs/Toy-Graphs/stadiums.csv");
        }
        else if (ans == "3") {
            LoadGraph("../files/Toy-Graphs/Toy-Graphs/tourism.csv");
        }
        else if (ans == "4") {
            LoadFullGraph(25);
        }
        else if (ans == "5") {
            LoadFullGraph(50);
        }
        else if (ans == "6") {
            LoadFullGraph(75);
        }
        else if (ans == "7") {
            LoadFullGraph(100);
        }
        else if (ans == "8") {
            LoadFullGraph(200);
        }
        else if (ans == "9") {
            LoadFullGraph(300);
        }
        else if (ans == "0") {
            DisplayOptionsMore();
            Menu2();
        }
        else {
            std::cout << "Not a valid option, please try again" << std::endl << std::endl;
        }
        break;
    }

}

void Menu::Menu2() {
        std::string ans;
    bool ret;
    while(true) {
        std::cout << "Choose an option: ";
        std::cin>>ans;
        std::cout <<std::endl;
        current_graph = WorldGraph();
        if (ans == "1") {
            LoadFullGraph(400);
        }
        else if (ans == "2") {
            LoadFullGraph(500);
        }
        else if (ans == "3") {
            LoadFullGraph(600);
        }
        else if (ans == "4") {
            LoadFullGraph(700);
        }
        else if (ans == "5") {
            LoadFullGraph(800);
        }
        else if (ans == "6") {
            LoadFullGraph(900);
        }
        else if (ans == "7") {
            LoadRealGraph(1);
        }
        else if (ans == "8") {
            LoadRealGraph(2);
        }
        else if (ans == "9") {
            LoadRealGraph(3);
        }
        else if (ans == "0") {
            DisplayOptions();
            MainMenu();
        }
        else {
            std::cout << "Not a valid option, please try again" << std::endl << std::endl;
        }
        break;
    }
}

void Menu::LoadGraph(const std::string &filename) {
    FileReaderToy::add_all_toy(filename, current_graph);
    DisplayAlgorithm(current_graph);
}

void Menu::LoadFullGraph(int edges) {
    FileReaderToy::add_all_places_coordinates("../files/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", current_graph, (edges-1));
    std::string edges_file = "../files/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_" + std::to_string(edges) + ".csv";
    FileReaderToy::add_all_connections_coordinates(edges_file, current_graph, 0);
    DisplayAlgorithm(current_graph);
}

void Menu::LoadRealGraph(int graphNumber) {
    FileReaderToy::add_all_places_coordinates("../files/Real-world Graphs/graph" + std::to_string(graphNumber) + "/nodes.csv", current_graph, INT_MAX);
    std::string edges_file = "../files/Real-world Graphs/graph" + std::to_string(graphNumber) + "/edges.csv";
    FileReaderToy::add_all_connections_coordinates(edges_file, current_graph, 1);
    DisplayAlgorithm(current_graph);
}


bool Menu::ToMain() {
    std::string ans;
    std::cout << std::endl << "Want to return to the Main Menu? (any character for yes, type 0 for no)" << std::endl;
    std::cin >> ans;
    return ans != "0";
}

