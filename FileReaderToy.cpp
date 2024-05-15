//
// Created by jogos on 5/15/2024.
//

#include "FileReaderToy.h"

#include <connection.h>
#include <sstream>
#include <unordered_map>
#include <worldGraph.h>

void FileReaderToy::add_all_toy(const std::string &filename , WorldGraph<int> &OurGraph) {
	std::ifstream inputfile(filename);
	std::unordered_map<int, bool> added;

	if(inputfile.is_open()) {
		std::string line;
		std::getline(inputfile,line);

		while(std::getline(inputfile,line))
		{
			if (line.empty() || line.find_first_not_of(',') == std::string::npos) {
				continue;
			}

			while (!line.empty() && line.back() == ',') {
				line.pop_back();
			}

			std::istringstream iss(line);
			std::string idOrigem, idDestino, distance;

			if(std::getline(iss, idOrigem, ',') &&
			   std::getline(iss, idDestino, ',') &&
			   std::getline(iss, distance, ','))
			{
				if (added[stoi(idOrigem)] == false) {
					Place newPlace = Place(stoi(idOrigem));
					added[stoi(idOrigem)] = true;
				}
				if (added[stoi(idDestino)] == false) {
					Place newPlace = Place(stoi(idDestino));
					added[stoi(idDestino)] = true;
				}
				Connection newConnection = Connection(stoi(idOrigem), stoi(idDestino), stoi(distance));
				OurGraph.add_connection(newConnection);
			}

			else
			{
				std::cout << "No file to open or wrong path selected for stations!" << std::endl;
			}

		}
		inputfile.close();
	}
}

void FileReaderToy::add_all_tourism(const std::string &filename , WorldGraph<int> &OurGraph) {
	std::ifstream inputfile(filename);
	std::unordered_map<int, bool> added;

	if(inputfile.is_open()) {
		std::string line;
		std::getline(inputfile,line);

		while(std::getline(inputfile,line))
		{
			if (line.empty() || line.find_first_not_of(',') == std::string::npos) {
				continue;
			}

			while (!line.empty() && line.back() == ',') {
				line.pop_back();
			}

			std::istringstream iss(line);
			std::string idOrigem, idDestino, distance, labelOrigem, labelDestino;

			if(std::getline(iss, idOrigem, ',') &&
			   std::getline(iss, idDestino, ',') &&
			   std::getline(iss, distance, ',') &&
			   std::getline(iss, labelOrigem, ',') &&
			   std::getline(iss, labelDestino, ','))
			{
				if (added[stoi(idOrigem)] == false) {
					Place newPlace = Place(stoi(idOrigem), labelOrigem);
					added[stoi(idOrigem)] = true;
				}
				if (added[stoi(idDestino)] == false) {
					Place newPlace = Place(stoi(idDestino), labelDestino);
					added[stoi(idDestino)] = true;
				}
				Connection newConnection = Connection(stoi(idOrigem), stoi(idDestino), stoi(distance));
				OurGraph.add_connection(newConnection);
			}

			else
			{
				std::cout << "No file to open or wrong path selected for stations!" << std::endl;
			}

		}
		inputfile.close();
	}
}

