//
// Created by Administrador on 15/05/2024.
//

/**
    *@file place.h
    *@brief Implementation of the Place class methods
*/

#include "place.h"

Place::Place() : id(-1) {
}

Place::Place(int id, std::string name)
{
    this->id = id;
    this->name = name;
}

Place::Place(int id)
{
	this->id = id;
}

Place::Place(int id, double longitude, double latitude)
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

double Place::get_longitude()
{
    return this->longitude;
}

double Place::get_latitude()
{
    return this->latitude;
}

bool Place::operator==(const Place& other) const
{
    return this->id == other.id;
}
