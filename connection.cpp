//
// Created by Administrador on 15/05/2024.
//

/**
    *@file connection.cpp
    *@brief Implementation of Connection class methods
*/

#include "connection.h"

Connection::Connection(int id_A, int id_B, double distance)
{
    this->id_A = id_A;
    this->id_B = id_B;
    this->distance = distance;
}

int Connection::get_id_A()
{
    return this->id_A;
}

int Connection::get_id_B()
{
    return this->id_B;
}

double Connection::get_distance()
{
    return this->distance;
}