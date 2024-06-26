//
// Created by jogos on 5/15/2024.
//

/**
    *@file fileReaderToy.cpp
    *@brief Implementation of FileReaderToy class methods
*/

#include "FileReaderToy.h"

#include <connection.h>
#include <sstream>
#include <unordered_map>
#include <worldGraph.h>

void FileReaderToy::add_all_toy(const std::string &filename , WorldGraph &OurGraph)
{
	std::ifstream inputfile(filename);
	std::unordered_map<int, bool> added;

	if(inputfile.is_open()) {
		std::string line;
		std::getline(inputfile,line);

		while(std::getline(inputfile,line))
		{
			if (line.empty() || line.find_first_not_of(',') == std::string::npos)
            {
				continue;
			}

			while (!line.empty() && line.back() == ',')
            {
				line.pop_back();
			}

			std::istringstream iss(line);
			std::string idOrigem, idDestino, distance;

			if(std::getline(iss, idOrigem, ',') &&
			   std::getline(iss, idDestino, ',') &&
			   std::getline(iss, distance, ','))
			{
				if (!added[stoi(idOrigem)] )  // aqui no if envez de ter == False pus !
                {
					Place newPlace = Place(stoi(idOrigem));
					OurGraph.add_place(newPlace);
					added[stoi(idOrigem)] = true;
				}

				if (!added[stoi(idDestino)]) // aqui no if envez de ter == False pus !
                {
					Place newPlace = Place(stoi(idDestino));
					OurGraph.add_place(newPlace);
					added[stoi(idDestino)] = true;
				}

				Connection newConnection = Connection(stoi(idOrigem), stoi(idDestino), stoi(distance));
				OurGraph.add_connection(newConnection,0);
			}

			else
			{
				std::cout << "No file to open or wrong path selected for stations!" << std::endl;
			}

		}
		inputfile.close();
	}
}

void FileReaderToy::add_all_tourism(const std::string &filename , WorldGraph &OurGraph) {
	std::ifstream inputfile(filename);
	std::unordered_map<int, bool> added;

	if(inputfile.is_open())
    {
		std::string line;
		std::getline(inputfile,line);

		while(std::getline(inputfile,line))
		{
			if (line.empty() || line.find_first_not_of(',') == std::string::npos)
            {
				continue;
			}

			while (!line.empty() && line.back() == ',')
            {
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
				if (!added[stoi(idOrigem)])
                {
					Place newPlace = Place(stoi(idOrigem), labelOrigem);
					added[stoi(idOrigem)] = true;
				}

				if (!added[stoi(idDestino)])
                {
					Place newPlace = Place(stoi(idDestino), labelDestino);
					added[stoi(idDestino)] = true;
				}

				Connection newConnection = Connection(stoi(idOrigem), stoi(idDestino), stoi(distance));
				OurGraph.add_connection(newConnection,0);
			}

			else
			{
				std::cout << "No file to open or wrong path selected for stations!" << std::endl;
			}

		}
		inputfile.close();
	}
}


void FileReaderToy::add_all_places_coordinates(const std::string &filename , WorldGraph &OurGraph, int places) {
    std::ifstream inputfile(filename);

    if (inputfile.is_open()) {
        std::string line;
        std::getline(inputfile, line);

        while (std::getline(inputfile, line)) {
            if (line.empty() || line.find_first_not_of(',') == std::string::npos) {
                continue;
            }

            while (!line.empty() && line.back() == ',') {
                line.pop_back();
            }

            std::istringstream iss(line);
            std::string idOrigem, longitude, latitude;

            if (std::getline(iss, idOrigem, ',') &&
                std::getline(iss, longitude, ',') &&
                std::getline(iss, latitude, ',')) {
            	if (stoi(idOrigem) > places) {
            		break;
            	}
                Place new_place = Place(std::stoi(idOrigem), std::stod(longitude), std::stod(latitude));
                OurGraph.add_place(new_place);
            } else {
                std::cout << "No file to open or wrong path selected for stations!" << std::endl;
            }

        }
        inputfile.close();
    }
}

void FileReaderToy::add_all_connections_coordinates(const std::string &filename, WorldGraph &OurGraph, int status)
{
	std::ifstream inputfile(filename);

	if (!inputfile.is_open()) {
		std::cerr << "No file to open or wrong path selected for stations!" << std::endl;
		return;
	}

	std::string line;
	while (std::getline(inputfile, line)) {
		if (line.empty() || !std::isdigit(line[0])) {
			continue; // Skip empty lines or lines not starting with a digit
		}

		std::istringstream iss(line);
		std::string idOrigem, idChegada, distance;
		if (std::getline(iss, idOrigem, ',') &&
			std::getline(iss, idChegada, ',') &&
			std::getline(iss, distance, ',')) {

			int origId = std::stoi(idOrigem);
			int destId = std::stoi(idChegada);
			double dist = std::stod(distance);

			Connection new_connection(origId, destId, dist);
			OurGraph.add_connection(new_connection, status);
			}
	}

	inputfile.close();
}


