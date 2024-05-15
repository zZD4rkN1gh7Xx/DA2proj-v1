//
// Created by Administrador on 15/05/2024.
//

#include "place.h"

Place::Place(int id, std::string name)
{
    this->id = id;
    this->name = name;
}

Place::Place(int id)
{
	this->id = id;
}

Place::Place(int id, long longitude, long latitude)
{
    this->id = id;
    this->longitude = longitude;
    this->latitude = latitude;
}

int Place::get_id()
{
    return  this->id;
}

std::string Place::get_name()
{
    return this->name;
}

long Place::get_longitude()
{
    return this->longitude;
}

long Place::get_latitude()
{
    return this->latitude;
}

