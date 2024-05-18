//
// Created by Me:D on 15/05/2024.
//

/**
    *@file place.h
    *@brief Implementation of Graph, Vertex and Edge classes
*/

#ifndef DAPROJ2_V2_PLACE_H
#define DAPROJ2_V2_PLACE_H

#include <iostream>
#include <string>

class Place
{
    private:
        int id;
        std::string name;
        double longitude;
        double latitude;

    public:

        Place();
        Place(int id);
        Place(int id, std::string name);
        Place(int id, double longitude, double latitude);
        int get_id();
        std::string get_name();
        double get_longitude();
        double get_latitude();
        bool operator==(const Place& other) const;

};


#endif //DAPROJ2_V2_PLACE_H
