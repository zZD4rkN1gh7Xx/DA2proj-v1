//
// Created by Me:D on 15/05/2024.
//

#ifndef DAPROJ2_V2_PLACE_H
#define DAPROJ2_V2_PLACE_H

#include <iostream>
#include <string>

class Place
{
    private:
        int id;
        std::string name;
        long longitude;
        long latitude;

    public:

        Place();
        Place(int id);
        Place(int id, std::string name);
        Place(int id, long longitude, long latitude);
        int get_id();
        std::string get_name();
        long get_longitude();
        long get_latitude();

};


#endif //DAPROJ2_V2_PLACE_H
